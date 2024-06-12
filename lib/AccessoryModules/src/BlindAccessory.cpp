#include "BlindAccessory/BlindAccessory.hpp"

// Constructor for BlindAccessory
BlindAccessory::BlindAccessory(RelayModuleInterface *motorUp, RelayModuleInterface *motorDown,
                               ButtonModuleInterface *buttonUp, ButtonModuleInterface *buttonDown,
                               uint8_t timeToOpen, uint8_t timeToClose, MultiPrinterLoggerInterface *logger, uint16_t usStackDepth)
    : _motorUp(motorUp),
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
      _targetPostion(0),
      _logger(logger)
{
    Log_Debug(_logger, "Created with timeToOpen: %d, timeToClose: %d.", _timeToOpen, _timeToClose);

    // Registering callback for moving the blind up on single press of the up button
    if (_buttonUp)
    {
        _buttonUp->onSinglePress(
            [](void *pParameter)
            {
                BlindAccessory *thisPointer = (BlindAccessory *)pParameter;

                if (thisPointer->_blindPosition != thisPointer->_targetPostion)
                {
                    Log_Verbose(thisPointer->_logger, "Button Up pressed. Moving to current position.");
                    thisPointer->moveBlindTo(thisPointer->_blindPosition);
                }
                else
                {
                    Log_Verbose(thisPointer->_logger, "Button Up pressed. Moving to 100%% position.");
                    thisPointer->moveBlindTo(100);
                }

                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);
        _buttonUp->startListening(usStackDepth, "buttonUpBlind");
    }

    // Registering callback for moving the blind down on single press of the down button
    if (_buttonDown)
    {
        _buttonDown->onSinglePress(
            [](void *pParameter)
            {
                BlindAccessory *thisPointer = (BlindAccessory *)pParameter;

                if (thisPointer->_blindPosition != thisPointer->_targetPostion)
                {
                    Log_Verbose(thisPointer->_logger, "Button Down pressed. Moving to current position.");
                    thisPointer->moveBlindTo(thisPointer->_blindPosition);
                }
                else
                {
                    Log_Verbose(thisPointer->_logger, "Button Down pressed. Moving to 0%% position.");
                    thisPointer->moveBlindTo(0);
                }

                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);
        _buttonDown->startListening(usStackDepth, "buttonDownBlind");
    }
}

// Destructor for BlindAccessory
BlindAccessory::~BlindAccessory()
{
    Log_Debug(_logger, "Destructor.");

    // Deleting the task handle if it exists
    if (_moveBlindToTask_handle)
    {
        Log_Verbose(_logger, "Deleting moveBlindToTask handle.");
        checkWaterMArkAndPrint(_logger, _moveBlindToTask_handle);
        xTASK_DELETE_TRACKED(&_moveBlindToTask_handle);
        _moveBlindToTask_handle = nullptr;
    }

    // Stopping the button listeners
    if (_buttonUp)
        _buttonUp->stopListening();
    if (_buttonDown)
        _buttonDown->stopListening();

    // Turning off the motors
    if (_motorUp)
    {
        Log_Verbose(_logger, "Turning off motorUp.");
        _motorUp->setState(false);
    }
    if (_motorDown)
    {
        Log_Verbose(_logger, "Turning off motorDown.");
        _motorDown->setState(false);
    }
}

// Move the blind to a specific position
void BlindAccessory::moveBlindTo(uint8_t position)
{
    Log_Verbose(_logger, "Move to position: %d", position);

    // Ensure position is within valid range
    if (position > 100)
        position = 100;
    else if (position < 0)
        position = 0;

    // Delete existing task handle if it exists
    if (_moveBlindToTask_handle)
    {
        Log_Verbose(_logger, "Deleting existing moveBlindToTask handle");
        checkWaterMArkAndPrint(_logger, _moveBlindToTask_handle);
        xTASK_DELETE_TRACKED(&_moveBlindToTask_handle);
        _moveBlindToTask_handle = nullptr;

        // Stop the motor
        stopMove();

        // Update the blind position to the target position
        _targetPostion = _blindPosition;

        // Notify the app about the blind event
        if (_notifyAPP && _callbackParameter)
            _notifyAPP(_callbackParameter);

        return;
    }

    // Set the target position and create a task to move the blind to the target position
    _targetPostion = position;
    xTASK_CREATE_TRACKED(
        [](void *pParameter)
        {
            BlindAccessory *thisPointer = (BlindAccessory *)pParameter;
            thisPointer->moveBlindToTargetTask();
            Log_Verbose(thisPointer->_logger, "Deleting moveBlindToTask handle.");
            checkWaterMArkAndPrint(thisPointer->_logger, thisPointer->_moveBlindToTask_handle);
            thisPointer->_moveBlindToTask_handle = nullptr;
            xTASK_DELETE_TRACKED(&(thisPointer->_moveBlindToTask_handle));
        },
        "moveBlindToTask", 3000, this, 1, &_moveBlindToTask_handle);
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
    Log_Verbose(_logger, "Setting notify callback.");
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}

// Start moving the blind up
void BlindAccessory::startMoveUp()
{
    Log_Verbose(_logger, "Starting to move up. current time: %d", millis());
    if (_motorDown)
        _motorDown->setState(false);
    if (_motorUp)
        _motorUp->setState(true);
}

// Start moving the blind down
void BlindAccessory::startMoveDown()
{
    Log_Verbose(_logger, "Starting to move down. current time: %d", millis());
    if (_motorUp)
        _motorUp->setState(false);
    if (_motorDown)
        _motorDown->setState(true);
}

// Stop moving the blind
void BlindAccessory::stopMove()
{
    Log_Verbose(_logger, "Stopping the blind movement. current time: %d", millis());
    if (_motorUp)
        _motorUp->setState(false);
    if (_motorDown)
        _motorDown->setState(false);
}

// Task to move the blind to a specific position
void BlindAccessory::moveBlindToTargetTask()
{
    Log_Verbose(_logger, "MoveBlindToTargetTask started.");

    // Return if the blind is already at the target position
    if (_targetPostion == _blindPosition)
    {
        Log_Verbose(_logger, "Blind is already at the target position. Stopping the move.");
        stopMove();
        if (_notifyAPP && _callbackParameter)
            _notifyAPP(_callbackParameter);
        return;
    }

    // Start moving the blind in the determined direction
    bool isMovingUp = _targetPostion > _blindPosition;

    uint32_t checkInterval; // Time in ms to wait before checking the position again (1% of open/close time)
    if (isMovingUp)
    {
        checkInterval = 1000 * _timeToOpen / 100;
    }
    else
    {
        checkInterval = 1000 * _timeToClose / 100;
    }

    bool updated = false;
    Log_Info(_logger, "Moving blind from %d to %d.", _blindPosition, _targetPostion);
    if (isMovingUp)
    {
        startMoveUp();
    }
    else
    {
        startMoveDown();
    }

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = checkInterval / portTICK_PERIOD_MS;
    // Continue moving the blind until the target position is reached
    while (!targetPositionReached(isMovingUp))
    {
        // Delay to check the position at regular intervals
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        _blindPosition += isMovingUp ? 1 : -1;

        // Call update callback after 1% change in position
        if (!updated && _notifyAPP && _callbackParameter)
        {
            updated = true;
            _notifyAPP(_callbackParameter);
        }
    }

    // Stop the motor and report the final position
    stopMove();
    Log_Info(_logger, "Blind moved to %d.", _blindPosition);
    _targetPostion = _blindPosition;

    // Notify the app about the blind event
    if (_notifyAPP && _callbackParameter)
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

// Set the default position of the blind
void BlindAccessory::setDefaultPosition(uint8_t position)
{
    Log_Verbose(_logger, "Setting default position to: %d", position);
    _blindPosition = position;
    _targetPostion = position;
}