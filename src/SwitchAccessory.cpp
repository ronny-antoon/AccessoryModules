#include "SwitchAccessory.hpp"

// SwitchAccessory constructor, initializing OnOffBasicAccessory with relayModule and buttonModule.
SwitchAccessory::SwitchAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicAccessory(relayModule, buttonModule) // Initialization of OnOffBasicAccessory
{
    // Additional initialization specific to the SwitchAccessory, if needed.
    // Note: You may add specific initialization steps for the switch accessory here.
}

// SwitchAccessory destructor, additional cleanup if needed.
SwitchAccessory::~SwitchAccessory()
{
    // Destructor implementation if needed.
    // Note: You may add specific cleanup steps for the switch accessory here.
}
