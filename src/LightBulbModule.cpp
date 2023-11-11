#include "LightBulbModule.hpp"

LightBulbModule::LightBulbModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicModule(relayModule, buttonModule) // Initialization of OnOffBasicModule
{
    // Additional initialization if needed.
}

LightBulbModule::~LightBulbModule()
{
    // Destructor implementation if needed.
}
