#include "BasicAccessory/OnOffBasicAccessory.hpp"

// Constructor initializes member variables and sets up the button module listener.
OnOffBasicAccessory::OnOffBasicAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger)
    : _relayModule(relayModule),
      _buttonModule(buttonModule),
      _notifyAPP(nullptr),
      _callbackParameter(nullptr),
      _logger(logger)
{
    Log_Info(_logger, "OnOffBasicAccessory Created.");

    // Check if a button module is provided.
    if (_buttonModule)
    {
        // Set up a listener for single press events.
        _buttonModule->onSinglePress(
            [](void *buttonCallBackParameter)
            {
                // Callback function to toggle the status and notify the app.
                OnOffBasicAccessory *thisPointer = static_cast<OnOffBasicAccessory *>(buttonCallBackParameter);
                thisPointer->setStatus(!thisPointer->getStatus(), true);
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening();
    }
}

// Destructor stops listening to button events if a button module is provided.
OnOffBasicAccessory::~OnOffBasicAccessory()
{
    Log_Debug(_logger, "OnOffBasicAccessory Deleted.");

    if (_buttonModule)
    {
        Log_Debug(_logger, "Stopping button module listener.");
        _buttonModule->stopListening();
    }
}

// Set the status of the accessory based on the provided value.
void OnOffBasicAccessory::setStatus(bool status, bool notify)
{
    Log_Debug(_logger, "Setting status: %s", status ? "ON" : "OFF");

    // Turn on or off the relay module based on the status.
    if (status)
        _relayModule->setState(true);
    else
        _relayModule->setState(false);

    if (notify && _notifyAPP && _callbackParameter)
    {
        Log_Debug(_logger, "Notifying status change.");
        _notifyAPP(_callbackParameter);
    }
}

// Get the current status of the accessory.
bool OnOffBasicAccessory::getStatus() const
{
    return _relayModule->isOn();
}

// Set the callback function for notifying status change events.
void OnOffBasicAccessory::setNotifyCallback(void (*callback)(void *), void *callbackParameter)
{
    Log_Debug(_logger, "Setting notify callback.");
    _notifyAPP = callback;
    _callbackParameter = callbackParameter;
}
