#include "OutletModule.hpp"

OutletModule::OutletModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicModule(relayModule, buttonModule) // Initialization of OnOffBasicModule
{
    // Additional initialization if needed.
}

OutletModule::~OutletModule()
{
    // Destructor implementation if needed.
}