#include "LightBulbAccessory.hpp"

LightBulbAccessory::LightBulbAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicAccessory(relayModule, buttonModule) // Initialization of OnOffBasicAccessory
{
    // Additional initialization if needed.
}

LightBulbAccessory::~LightBulbAccessory()
{
    // Destructor implementation if needed.
}
