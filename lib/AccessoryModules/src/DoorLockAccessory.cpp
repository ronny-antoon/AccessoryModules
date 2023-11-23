#include "DoorLockAccessory/DoorLockAccessory.hpp"

/**
 * @brief Task to open the door after a delay.
 */
void DoorLockAccessory::openDoorTask()
{
    vTaskDelay(pdMS_TO_TICKS(_timeToUnlock * 1000));
    closeDoor();
    if (_notifyAPP && _callbackParameter)
        _notifyAPP(_callbackParameter);
}

/**
 * @brief DoorLockAccessory constructor.
 *
 * @param relayModule The relay module associated with the door lock accessory.
 * @param buttonModule The button module associated with the door lock accessory.
 * @param timeToUnlock Time to unlock the door in seconds. Range: 1-255.
 */
DoorLockAccessory::DoorLockAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint8_t timeToUnlock, MultiPrinterLoggerInterface *logger)
    : _relayModule(relayModule),
      _buttonModule(buttonModule),
      _notifyAPP(nullptr),
      _callbackParameter(nullptr),
      _timeToUnlock(timeToUnlock),
      _openDoorTask_handle(nullptr),
      _logger(logger)
{
    Log_Debug(_logger, "Door Lock Accessory Created.");

    // Check if a button module is provided.
    if (_buttonModule)
    {
        // Set up a listener for single press events.
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                DoorLockAccessory *thisPointer = static_cast<DoorLockAccessory *>(pParameter);
                thisPointer->openDoor();
                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening();
    }
}

/**
 * @brief Virtual destructor for DoorLockAccessory.
 */
DoorLockAccessory::~DoorLockAccessory()
{
    Log_Debug(_logger, "Door Lock Accessory Deleted.");

    if (_openDoorTask_handle != nullptr)
    {
        vTaskDelete(_openDoorTask_handle);
        _openDoorTask_handle = nullptr;
    }

    if (_buttonModule)
        _buttonModule->stopListening();

    if (_relayModule)
        _relayModule->turnOff();
}

/**
 * @brief Set the callback function and its parameter for doorbell events.
 *
 * @param notifyAPP The callback function to notify the app.
 * @param pParameter The parameter for the callback function.
 */
void DoorLockAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}

/**
 * @brief Open the door.
 */
void DoorLockAccessory::openDoor()
{
    Log_Debug(_logger, "Door Lock Accessory Opened.");
    if (_relayModule)
    {
        if (_openDoorTask_handle != nullptr)
        {
            vTaskDelete(_openDoorTask_handle);
            _openDoorTask_handle = nullptr;
        }
        _relayModule->turnOn();
        xTaskCreate(
            [](void *thisPointer)
            {
                ((DoorLockAccessory *)thisPointer)->openDoorTask();
                ((DoorLockAccessory *)thisPointer)->_openDoorTask_handle = nullptr;
                vTaskDelete(nullptr);
            },
            "openDoorTask",
            10000,
            this,
            1,
            &_openDoorTask_handle);
    }
}

/**
 * @brief Close the door.
 */
void DoorLockAccessory::closeDoor()
{
    Log_Debug(_logger, "Door Lock Accessory Closed.");
    if (_relayModule)
        _relayModule->turnOff();
}

/**
 * @brief Check if the door is open.
 *
 * @return True if the door is open, false otherwise.
 */
bool DoorLockAccessory::isDoorOpen() const
{
    if (_relayModule)
        return _relayModule->isOn();
    else
        return false;
}

/**
 * @brief Set the lock state of the door.
 *
 * @param toOpen True to set the door to an open state, false to set it to a closed state.
 * @param notfy True to notify the app(The First Time), false otherwise.
 *
 * @note After open will notfy first time, and after close will notfy second time.
 */
void DoorLockAccessory::setLockState(bool toOpen, bool notfy)
{
    if (toOpen)
        openDoor();
    else
        closeDoor();
    if (notfy && _notifyAPP && _callbackParameter)
        _notifyAPP(_callbackParameter);
}
