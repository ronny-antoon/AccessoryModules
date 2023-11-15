#include "FanAccessory/FanAccessory.hpp"

// FanAccessory constructor, initializing OnOffBasicAccessory with relayModule and buttonModule.
FanAccessory::FanAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger)
    : OnOffBasicAccessory(relayModule, buttonModule), _logger(logger) // Initialization of OnOffBasicAccessory
{
    Log_Debug(_logger, "Fan Accessory Created.");
    // Additional initialization specific to the FanAccessory, if needed.
    // Note: You may add specific initialization steps for the fan accessory here.
}

// FanAccessory destructor, additional cleanup if needed.
FanAccessory::~FanAccessory()
{
    Log_Debug(_logger, "Fan Accessory Deleted.");
    // Destructor implementation if needed.
    // Note: You may add specific cleanup steps for the fan accessory here.
}
