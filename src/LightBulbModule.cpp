#include "LightBulbModule.hpp"

LightBulbModule::LightBulbModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule) : OnOffGenericModule<LightBulbModuleInterface>(relayModule, buttonModule)
{
}
