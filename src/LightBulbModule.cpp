#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "LightBulbModule.hpp"
#include "OnOffBasicModule.hpp"

LightBulbModule::LightBulbModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule) : OnOffBasicModule(relayModule, buttonModule)
{
    
}

LightBulbModule::~LightBulbModule()
{
}
