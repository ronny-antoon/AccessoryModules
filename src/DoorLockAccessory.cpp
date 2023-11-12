#include "DoorLockAccessory.hpp"

void DoorLockAccessory::openDoorTask()
{
    vTaskDelay(pdMS_TO_TICKS(_timeToUnlock * 1000));
    closeDoor();
    _notifyAPP(_callbackParameter);
}

// Constructor initializes member variables and sets up the button module listener.
DoorLockAccessory::DoorLockAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint8_t timeToUnlock)
    : _relayModule(relayModule),
      _buttonModule(buttonModule),
      _notifyAPP(nullptr),
      _callbackParameter(nullptr),
      _timeToUnlock(timeToUnlock),
      openDoorTask_handle(nullptr)
{
    // Check if a button module is provided.
    if (_buttonModule)
    {
        // Set up a listener for single press events.
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                DoorLockAccessory *thisPointer = static_cast<DoorLockAccessory *>(pParameter);
                thisPointer->openDoor();
                thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening();
    }
}

// Destructor stops listening to button events.
DoorLockAccessory::~DoorLockAccessory()
{
    if (_buttonModule)
        _buttonModule->stopListening();
    if (openDoorTask_handle != nullptr)
    {
        vTaskDelete(openDoorTask_handle);
        openDoorTask_handle = nullptr;
    }
}

// Set the callback function and its parameter for doorbell events.
void DoorLockAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}

// Open the door.
void DoorLockAccessory::openDoor()
{
    if (_relayModule)
    {
        if (openDoorTask_handle != nullptr)
        {
            vTaskDelete(openDoorTask_handle);
            openDoorTask_handle = nullptr;
        }
        _relayModule->turnOn();
        xTaskCreate(
            [](void *thisPointer)
            {
                ((DoorLockAccessory *)thisPointer)->openDoorTask();
                ((DoorLockAccessory *)thisPointer)->openDoorTask_handle = nullptr;
                vTaskDelete(nullptr);
            },
            "openDoorTask",
            10000,
            this,
            1,
            &openDoorTask_handle);
    }
}

// Close the door.
void DoorLockAccessory::closeDoor()
{
    if (_relayModule)
        _relayModule->turnOff();
}

// Check if the door is open.
bool DoorLockAccessory::isDoorOpen() const
{
    if (_relayModule)
        return _relayModule->isOn();
    else
        return false;
}

// Set the lock state of the door.
void DoorLockAccessory::setLockState(bool toOpen)
{
    if (toOpen)
        openDoor();
    else
        closeDoor();
}