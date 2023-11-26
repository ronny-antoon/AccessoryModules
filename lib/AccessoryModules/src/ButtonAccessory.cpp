#include "ButtonAccessory/ButtonAccessory.hpp"

ButtonAccessory::ButtonAccessory(ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger) : _buttonModule(buttonModule),
                                                                                                             _notifyAPP(nullptr),
                                                                                                             _callbackParameter(nullptr),
                                                                                                             _lastPressEvent(PressType::SinglePress),
                                                                                                             _logger(logger)
{
    Log_Info(_logger, "ButtonAccessory constructor called.");

    // Set up event listeners based on button actions
    if (_buttonModule)
    {
        // Listener for single press event
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
                thisPointer->_lastPressEvent = PressType::SinglePress;

                Log_Info(thisPointer->_logger, "Single press event detected.");

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

                Log_Info(thisPointer->_logger, "Double press event detected.");

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

                Log_Info(thisPointer->_logger, "Long press event detected.");

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
    Log_Info(_logger, "ButtonAccessory destructor called.");

    // Stop listening for button events
    if (_buttonModule)
    {
        Log_Debug(_logger, "Stopping button module listener.");
        _buttonModule->stopListening();
    }
}

ButtonAccessory::PressType ButtonAccessory::getLastPressEvent() const
{
    // Return the last press event that occurred
    return _lastPressEvent;
}

void ButtonAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    // Set the callback function and its parameter for press events
    Log_Debug(_logger, "Setting notify callback.");
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}
