#include "DoorBellAccessory/DoorBellAccessory.hpp"

// Constructor initializes member variables and sets up the button module listener.
DoorBellAccessory::DoorBellAccessory(ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger)
    : _buttonModule(buttonModule),
      _notifyAPP(nullptr),
      _callbackParameter(nullptr),
      _logger(logger)
{
    Log_Debug(_logger, "Doorbell Accessory Created.");

    // Check if a button module is provided.
    if (_buttonModule)
    {
        // Set up a listener for single press events.
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                DoorBellAccessory *thisPointer = static_cast<DoorBellAccessory *>(pParameter);
                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening();
    }
}

// Destructor stops listening to button events.
DoorBellAccessory::~DoorBellAccessory()
{
    Log_Debug(_logger, "Doorbell Accessory Deleted.");

    if (_buttonModule)
        _buttonModule->stopListening();
}

// Set the callback function and its parameter for doorbell events.
void DoorBellAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}
