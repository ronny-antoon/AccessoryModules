#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "OnOffBasicAccessory.hpp"

OnOffBasicAccessory::OnOffBasicAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule) : _relayModule(relayModule),
                                                                                                             _buttonModule(buttonModule),
                                                                                                             _notifyAPP(nullptr),
                                                                                                             _pParameter(nullptr)
{
    if (_buttonModule)
    {
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                OnOffBasicAccessory *thisPointer = (OnOffBasicAccessory *)pParameter;
                thisPointer->setStatus(!thisPointer->getStatus());
                thisPointer->_notifyAPP(thisPointer->_pParameter);
            },
            this);
        _buttonModule->startListening();
    }
}

OnOffBasicAccessory::~OnOffBasicAccessory()
{
    if (_buttonModule)
        _buttonModule->stopListening();
}

void OnOffBasicAccessory::setStatus(bool status)
{
    if (status == true)
        _relayModule->turnOn();
    else
        _relayModule->turnOff();
}

bool OnOffBasicAccessory::getStatus() const
{
    return _relayModule->isOn();
}

void OnOffBasicAccessory::setNotifyCallback(void (*callback)(void *), void *pParameter)
{
    _notifyAPP = callback;
    _pParameter = pParameter;
}
