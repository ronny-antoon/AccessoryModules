#include "FanModule.hpp"

FanModule::FanModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule)
    : OnOffBasicModule(relayModule, buttonModule) // Initialization of OnOffBasicModule
{
    // Additional initialization if needed.
}

FanModule::~FanModule()
{
    // Destructor implementation if needed.
}