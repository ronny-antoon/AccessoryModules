#include "OnOffGenericModule.hpp"

template <typename ModuleType>
OnOffGenericModule<ModuleType>::OnOffGenericModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
{
    _relayModule = relayModule;
    _buttonModule = buttonModule;
    _notifyAPP = nullptr;
    _pParameter = nullptr;

    if (_buttonModule)
    {
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                OnOffGenericModule *thisPointer = (OnOffGenericModule *)pParameter;
                thisPointer->setStatus(!thisPointer->getStatus());
                thisPointer->_notifyAPP(thisPointer->_pParameter);
            },
            this);
        _buttonModule->startListening();
    }
}

template <typename ModuleType>
OnOffGenericModule<ModuleType>::~OnOffGenericModule()
{
    if (_buttonModule)
        _buttonModule->stopListening();
}

template <typename ModuleType>
void OnOffGenericModule<ModuleType>::setStatus(bool status)
{
    if (status == true)
        _relayModule->turnOn();
    else
        _relayModule->turnOff();
}

template <typename ModuleType>
bool OnOffGenericModule<ModuleType>::getStatus() const
{
    return _relayModule->isOn();
}

template <typename ModuleType>
void OnOffGenericModule<ModuleType>::setNotifyCallback(void (*callback)(void *), void *_pParameter)
{
    _notifyAPP = callback;
    _pParameter = _pParameter;
}
