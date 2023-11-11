#include "SwitchModule.hpp"

SwitchModule::SwitchModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicModule(relayModule, buttonModule) // Initialization of OnOffBasicModule
{
    // Additional initialization if needed.
}

SwitchModule::~SwitchModule()
{
    // Destructor implementation if needed.
}