#include "SwitchAccessory.hpp"

SwitchAccessory::SwitchAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicAccessory(relayModule, buttonModule) // Initialization of OnOffBasicAccessory
{
    // Additional initialization if needed.
}

SwitchAccessory::~SwitchAccessory()
{
    // Destructor implementation if needed.
}