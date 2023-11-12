#include "FanAccessory.hpp"

// FanAccessory constructor, initializing OnOffBasicAccessory with relayModule and buttonModule.
FanAccessory::FanAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicAccessory(relayModule, buttonModule) // Initialization of OnOffBasicAccessory
{
    // Additional initialization specific to the FanAccessory, if needed.
    // Note: You may add specific initialization steps for the fan accessory here.
}

// FanAccessory destructor, additional cleanup if needed.
FanAccessory::~FanAccessory()
{
    // Destructor implementation if needed.
    // Note: You may add specific cleanup steps for the fan accessory here.
}
