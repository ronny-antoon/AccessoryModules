#include "ButtonAccessory/ButtonAccessory.hpp"

ButtonAccessory::ButtonAccessory(ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger) : _buttonModule(buttonModule),
                                                                                                             _notifyAPP(nullptr),
                                                                                                             _callbackParameter(nullptr),
                                                                                                             _lastPressEvent(PressType::SinglePress),
                                                                                                             _logger(logger)
{
    Log_Debug(_logger, "Button Accessory Created.");

    // Set up event listeners based on button actions
    if (_buttonModule)
    {
        // Listener for single press event
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
                thisPointer->_lastPressEvent = PressType::SinglePress;
                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);

        // Listener for double press event
        _buttonModule->onDoublePress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
                thisPointer->_lastPressEvent = PressType::DoublePress;
                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);

        // Listener for long press event
        _buttonModule->onLongPress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
                thisPointer->_lastPressEvent = PressType::LongPress;
                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);

        // Start listening for button events
        _buttonModule->startListening();
    }
}

ButtonAccessory::~ButtonAccessory()
{
    Log_Debug(_logger, "Button Accessory Deleted.");

    // Stop listening for button events
    if (_buttonModule)
        _buttonModule->stopListening();
}

ButtonAccessory::PressType ButtonAccessory::getLastPressEvent() const
{
    // Return the last press event that occurred
    return _lastPressEvent;
}

void ButtonAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    // Set the callback function and its parameter for press events
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}
