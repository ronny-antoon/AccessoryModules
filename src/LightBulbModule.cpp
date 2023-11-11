#include "LightBulbModule.hpp"

LightBulbModule::LightBulbModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
{
    _relayModule = relayModule;
    _buttonModule = buttonModule;
    _notifyAPP = nullptr;
    _pParameter = nullptr;

    _buttonModule->onSinglePress(
        [](void *pParameter)
        {
            LightBulbModule *thisPointer = (LightBulbModule *)pParameter;
            thisPointer->update(!thisPointer->getStatus());
            thisPointer->_notifyAPP(thisPointer->_pParameter);
        },
        this);
    _buttonModule->startListening();
}

LightBulbModule::~LightBulbModule()
{
    delete _relayModule;
    delete _buttonModule;
}

bool LightBulbModule::update(bool status)
{
    if (status == true)
        _relayModule->turnOn();
    else
        _relayModule->turnOff();

    return status == getStatus();
}

void LightBulbModule::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    _notifyAPP = notifyAPP;
    _pParameter = pParameter;
}

bool LightBulbModule::getStatus() const
{
    return _relayModule->isOn();
}