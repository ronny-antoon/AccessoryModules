#include "ButtonAccessory.hpp"

ButtonAccessory::ButtonAccessory(ButtonModuleInterface *buttonModule)
{
    _buttonModule = buttonModule;
    _notifyAPP = nullptr;
    _callbackParameter = nullptr;
    _lastPressEvent = PressType::SinglePress;

    if (_buttonModule)
    {
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = (ButtonAccessory *)pParameter;
                thisPointer->_lastPressEvent = PressType::SinglePress;
                thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);
        _buttonModule->onDoublePress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = (ButtonAccessory *)pParameter;
                thisPointer->_lastPressEvent = PressType::DoublePress;
                thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);
        _buttonModule->onLongPress(
            [](void *pParameter)
            {
                ButtonAccessory *thisPointer = (ButtonAccessory *)pParameter;
                thisPointer->_lastPressEvent = PressType::LongPress;
                thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);
        _buttonModule->startListening();
    }
}

ButtonAccessory::~ButtonAccessory()
{
    if (_buttonModule)
        _buttonModule->stopListening();
}

ButtonAccessory::PressType ButtonAccessory::getLastPressEvent() const
{
    return _lastPressEvent;
}

void ButtonAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}