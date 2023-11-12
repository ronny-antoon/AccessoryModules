#include "ButtonAccessory.hpp"

// Constructor initializes member variables with default values.
ButtonAccessory::ButtonAccessory(ButtonModuleInterface *buttonModule)
    : _buttonModule(buttonModule),
      _pressEventCallback(nullptr),
      _pressEventCallbackParameter(nullptr)
{
}

// Destructor releases resources and stops listening to button events.
ButtonAccessory::~ButtonAccessory()
{
    if (_buttonModule)
    {
        stopListening();
        delete _buttonModule;
    }
}

// Set the callback function and its parameter for press events.
void ButtonAccessory::setOnPressEvent(void (*pressEventCallback)(void *, PressType), void *pressEventCallbackParameter)
{
    _pressEventCallback = pressEventCallback;
    _pressEventCallbackParameter = pressEventCallbackParameter;
}

// Start listening for button press events.
void ButtonAccessory::startListening()
{
    if (_buttonModule)
    {
        // Set up listeners for single, double, and long press events.
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
                thisPointer->_pressEventCallback(thisPointer->_pressEventCallbackParameter, SinglePress);
            },
            this);
        _buttonModule->onDoublePress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
                thisPointer->_pressEventCallback(thisPointer->_pressEventCallbackParameter, DoublePress);
            },
            this);
        _buttonModule->onLongPress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = static_cast<ButtonAccessory *>(pParameter);
                thisPointer->_pressEventCallback(thisPointer->_pressEventCallbackParameter, LongPress);
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening();
    }
}

// Stop listening for button events.
void ButtonAccessory::stopListening()
{
    if (_buttonModule)
        _buttonModule->stopListening();
}
