#include "OutletAccessory.hpp"

OutletAccessory::OutletAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicAccessory(relayModule, buttonModule) // Initialization of OnOffBasicAccessory
{
    // Additional initialization if needed.
}

OutletAccessory::~OutletAccessory()
{
    // Destructor implementation if needed.
}