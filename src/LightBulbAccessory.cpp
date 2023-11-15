#include "LightBulbAccessory/LightBulbAccessory.hpp"

// LightBulbAccessory constructor, initializing OnOffBasicAccessory with relayModule and buttonModule.
LightBulbAccessory::LightBulbAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger)
    : OnOffBasicAccessory(relayModule, buttonModule), _logger(logger) // Initialization of OnOffBasicAccessory
{
    Log_Debug(_logger, "Light Bulb Accessory Created.");
    // Additional initialization specific to the LightBulbAccessory, if needed.
    // Note: You may add specific initialization steps for the light bulb accessory here.
}

// LightBulbAccessory destructor, additional cleanup if needed.
LightBulbAccessory::~LightBulbAccessory()
{
    Log_Debug(_logger, "Light Bulb Accessory Deleted.");
    // Destructor implementation if needed.
    // Note: You may add specific cleanup steps for the light bulb accessory here.
}
