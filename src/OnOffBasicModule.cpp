#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "OnOffBasicModule.hpp"

OnOffBasicModule::OnOffBasicModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
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
                OnOffBasicModule *thisPointer = (OnOffBasicModule *)pParameter;
                thisPointer->setStatus(!thisPointer->getStatus());
                thisPointer->_notifyAPP(thisPointer->_pParameter);
            },
            this);
        _buttonModule->startListening();
    }
}

OnOffBasicModule::~OnOffBasicModule()
{
    if (_buttonModule)
        _buttonModule->stopListening();
}

void OnOffBasicModule::setStatus(bool status)
{
    if (status == true)
        _relayModule->turnOn();
    else
        _relayModule->turnOff();
}

bool OnOffBasicModule::getStatus() const
{
    return _relayModule->isOn();
}

void OnOffBasicModule::setNotifyCallback(void (*callback)(void *), void *_pParameter)
{
    _notifyAPP = callback;
    _pParameter = _pParameter;
}
