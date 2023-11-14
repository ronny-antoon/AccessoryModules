#include "OutletAccessory/OutletAccessory.hpp"

// OutletAccessory constructor, initializing OnOffBasicAccessory with relayModule and buttonModule.
OutletAccessory::OutletAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicAccessory(relayModule, buttonModule) // Initialization of OnOffBasicAccessory
{
    // Additional initialization specific to the OutletAccessory, if needed.
    // Note: You may add specific initialization steps for the outlet accessory here.
}

// OutletAccessory destructor, additional cleanup if needed.
OutletAccessory::~OutletAccessory()
{
    // Destructor implementation if needed.
    // Note: You may add specific cleanup steps for the outlet accessory here.
}
