#include "BlindAccessory/BlindAccessory.hpp"

// Constructor for BlindAccessory
BlindAccessory::BlindAccessory(RelayModuleInterface *motorUp, RelayModuleInterface *motorDown,
                               ButtonModuleInterface *buttonUp, ButtonModuleInterface *buttonDown,
                               uint8_t timeToOpen, uint8_t timeToClose) : _motorUp(motorUp),
                                                                          _motorDown(motorDown),
                                                                          _buttonUp(buttonUp),
                                                                          _buttonDown(buttonDown),
                                                                          _notifyAPP(nullptr),
                                                                          _callbackParameter(nullptr),
                                                                          _blindPosition(0),
                                                                          _timeToOpen(timeToOpen),
                                                                          _timeToClose(timeToClose),
                                                                          _checkInterval(50),
                                                                          _moveBlindToTask_handle(nullptr),
                                                                          _targetPostion(0)
{
    // Registering callback for moving the blind up on single press of the up button
    if (_buttonUp)
    {
        _buttonUp->onSinglePress(
            [](void *pParameter)
            {
                BlindAccessory *thisPointer = (BlindAccessory *)pParameter;
                if (thisPointer->_blindPosition != thisPointer->_targetPostion)
                    thisPointer->moveBlindTo(thisPointer->_blindPosition);
                else
                    thisPointer->moveBlindTo(100);
                thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);
        _buttonUp->startListening();
    }

    // Registering callback for moving the blind down on single press of the down button
    if (_buttonDown)
    {
        _buttonDown->onSinglePress(
            [](void *pParameter)
            {
                BlindAccessory *thisPointer = (BlindAccessory *)pParameter;
                if (thisPointer->_blindPosition != thisPointer->_targetPostion)
                    thisPointer->moveBlindTo(thisPointer->_blindPosition);
                else
                    thisPointer->moveBlindTo(0);
                thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);
        _buttonDown->startListening();
    }
}

// Destructor for BlindAccessory
BlindAccessory::~BlindAccessory()
{
    // Deleting the task handle if it exists
    if (_moveBlindToTask_handle)
    {
        vTaskDelete(_moveBlindToTask_handle);
        _moveBlindToTask_handle = nullptr;
    }

    // Deleting relay and button modules if they exist
    if (_motorUp)
        delete _motorUp;

    if (_motorDown)
        delete _motorDown;

    if (_buttonUp)
        delete _buttonUp;

    if (_buttonDown)
        delete _buttonDown;
}

// Move the blind to a specific position
void BlindAccessory::moveBlindTo(uint8_t position)
{
    // Ensure position is within valid range
    if (position > 100)
        position = 100;
    else if (position < 0)
        position = 0;

    // Delete existing task handle if it exists
    if (_moveBlindToTask_handle)
    {
        vTaskDelete(_moveBlindToTask_handle);
        _moveBlindToTask_handle = nullptr;
    }

    // Set the target position and create a task to move the blind to the target position
    _targetPostion = position;
    xTaskCreate(
        [](void *pParameter)
        {
            BlindAccessory *thisPointer = (BlindAccessory *)pParameter;
            thisPointer->moveBlindToTargetTask();
            thisPointer->_moveBlindToTask_handle = nullptr;
            vTaskDelete(nullptr);
        },
        "moveBlindToTask", 10000, this, 1, &_moveBlindToTask_handle);
}

// Get the current position of the blind
uint8_t BlindAccessory::getCurrentPosition() const
{
    return _blindPosition;
}

// Get the target position of the blind
uint8_t BlindAccessory::getTargetPosition() const
{
    return _targetPostion;
}

// Set the callback function and its parameter for blind events
void BlindAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}

// Start moving the blind up
void BlindAccessory::startMoveUp()
{
    if (_motorDown)
        _motorDown->turnOff();
    if (_motorUp)
        _motorUp->turnOn();
}

// Start moving the blind down
void BlindAccessory::startMoveDown()
{
    if (_motorUp)
        _motorUp->turnOff();
    if (_motorDown)
        _motorDown->turnOn();
}

// Stop moving the blind
void BlindAccessory::stopMove()
{
    if (_motorUp)
        _motorUp->turnOff();
    if (_motorDown)
        _motorDown->turnOff();
}

// Task to move the blind to a specific position
void BlindAccessory::moveBlindToTargetTask()
{
    double currentPosition = _blindPosition;

    // Ensure target position is within valid range
    if (_targetPostion < 0)
        _targetPostion = 0;
    else if (_targetPostion > 100)
        _targetPostion = 100;

    // Return if the blind is already at the target position
    if (_targetPostion == _blindPosition)
    {
        stopMove();
        return;
    }

    // Determine the direction of blind movement
    bool isMovingUp = _targetPostion > _blindPosition;

    // Start moving the blind in the determined direction
    if (isMovingUp)
        startMoveUp();
    else
        startMoveDown();

    // Continue moving the blind until the target position is reached
    while (!targetPositionReached(isMovingUp))
    {
        // Delay to check the position at regular intervals
        vTaskDelay(pdMS_TO_TICKS(_checkInterval));

        // Update the current position based on the movement direction
        currentPosition += isMovingUp ? (double)_checkInterval / (_timeToOpen * 1000) * 100 : -(double)_checkInterval / (_timeToClose * 1000) * 100;
        _blindPosition = (uint8_t)currentPosition;
    }

    // Stop moving the blind and update the position to the target position
    stopMove();
    _blindPosition = _targetPostion;

    // Notify the app about the blind event
    _notifyAPP(_callbackParameter);
}

// Check if the target position is reached during blind movement
bool BlindAccessory::targetPositionReached(bool movingUp)
{
    if (movingUp)
    {
        if (_blindPosition >= _targetPostion)
            return true;
    }
    else
    {
        if (_blindPosition <= _targetPostion)
            return true;
    }
    return false;
}
