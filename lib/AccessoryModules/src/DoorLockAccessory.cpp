#include "DoorLockAccessory/DoorLockAccessory.hpp"

/**
 * @brief Task to open the door after a delay.
 */
void DoorLockAccessory::openDoorTask()
{
    Log_Verbose(_logger, "Opening door after a delay.");
    vTaskDelay(pdMS_TO_TICKS(_timeToUnlock * 1000));
    closeDoor();
    if (_notifyAPP && _callbackParameter)
    {
        Log_Verbose(_logger, "Door opened, notifying the app.");
        _notifyAPP(_callbackParameter);
    }
}

/**
 * @brief DoorLockAccessory constructor.
 *
 * @param relayModule The relay module associated with the door lock accessory.
 * @param buttonModule The button module associated with the door lock accessory.
 * @param timeToUnlock Time to unlock the door in seconds. Range: 1-255.
 */
DoorLockAccessory::DoorLockAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint8_t timeToUnlock, MultiPrinterLoggerInterface *logger, uint16_t usStackDepth)
    : _relayModule(relayModule),
      _buttonModule(buttonModule),
      _notifyAPP(nullptr),
      _callbackParameter(nullptr),
      _timeToUnlock(timeToUnlock),
      _openDoorTask_handle(nullptr),
      _logger(logger)
{
    Log_Debug(_logger, "Door Lock Accessory Created with timeToUnlock: %d seconds.", _timeToUnlock);

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
                {
                    Log_Verbose(thisPointer->_logger, "Doorbell button pressed, opening the door.");
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
                }
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening(usStackDepth, "buttonDoorLock");
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
        Log_Verbose(_logger, "Deleting openDoorTask handle.");
        checkWaterMArkAndPrint(_logger, _openDoorTask_handle);
        xTASK_DELETE_TRACKED(&_openDoorTask_handle);
        _openDoorTask_handle = nullptr;
    }

    if (_buttonModule)
    {
        Log_Verbose(_logger, "Stopping button module listener.");
        _buttonModule->stopListening();
    }

    if (_relayModule)
    {
        Log_Verbose(_logger, "Turning off relay module.");
        _relayModule->setState(false);
    }
}

/**
 * @brief Set the callback function and its parameter for doorbell events.
 *
 * @param notifyAPP The callback function to notify the app.
 * @param pParameter The parameter for the callback function.
 */
void DoorLockAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    Log_Verbose(_logger, "Setting notify callback.");
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}

/**
 * @brief Open the door.
 */
void DoorLockAccessory::openDoor()
{
    Log_Verbose(_logger, "Opening the door.");
    if (_relayModule)
    {
        if (_openDoorTask_handle != nullptr)
        {
            Log_Verbose(_logger, "Deleting existing openDoorTask handle.");
            checkWaterMArkAndPrint(_logger, _openDoorTask_handle);
            xTASK_DELETE_TRACKED(&_openDoorTask_handle);
            _openDoorTask_handle = nullptr;
        }

        _relayModule->setState(true);
        xTASK_CREATE_TRACKED(
            [](void *thisPointer)
            {
                DoorLockAccessory *doorLock = static_cast<DoorLockAccessory *>(thisPointer);
                doorLock->openDoorTask();
                Log_Verbose(doorLock->_logger, "Deleting openDoorTask handle.");
                checkWaterMArkAndPrint(doorLock->_logger, doorLock->_openDoorTask_handle);
                doorLock->_openDoorTask_handle = nullptr;
                xTASK_DELETE_TRACKED(&(doorLock->_openDoorTask_handle));
            },
            "openDoorTask",
            3000,
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
    Log_Verbose(_logger, "Closing the door.");
    if (_relayModule)
        _relayModule->setState(false);
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
 * @param notify True to notify the app (The First Time), false otherwise.
 *
 * @note After open will notify the first time, and after close will notify the second time.
 */
void DoorLockAccessory::setLockState(bool toOpen, bool notify)
{
    if (toOpen)
        openDoor();
    else
        closeDoor();

    if (notify && _notifyAPP && _callbackParameter)
    {
        Log_Verbose(_logger, "Notifying the app about the door state.");
        _notifyAPP(_callbackParameter);
    }
}
