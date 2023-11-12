#include "LightBulbAccessory.hpp"

// LightBulbAccessory constructor, initializing OnOffBasicAccessory with relayModule and buttonModule.
LightBulbAccessory::LightBulbAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicAccessory(relayModule, buttonModule) // Initialization of OnOffBasicAccessory
{
    // Additional initialization specific to the LightBulbAccessory, if needed.
    // Note: You may add specific initialization steps for the light bulb accessory here.
}

// LightBulbAccessory destructor, additional cleanup if needed.
LightBulbAccessory::~LightBulbAccessory()
{
    // Destructor implementation if needed.
    // Note: You may add specific cleanup steps for the light bulb accessory here.
}
