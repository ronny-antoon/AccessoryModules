#include "FanAccessory.hpp"

FanAccessory::FanAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicAccessory(relayModule, buttonModule) // Initialization of OnOffBasicAccessory
{
    // Additional initialization if needed.
}

FanAccessory::~FanAccessory()
{
    // Destructor implementation if needed.
}