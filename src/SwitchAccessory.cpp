#include "SwitchAccessory/SwitchAccessory.hpp"

// SwitchAccessory constructor, initializing OnOffBasicAccessory with relayModule and buttonModule.
SwitchAccessory::SwitchAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger)
    : OnOffBasicAccessory(relayModule, buttonModule), _logger(logger) // Initialization of OnOffBasicAccessory
{
    Log_Debug(_logger, "Switch Accessory Created.");
    // Additional initialization specific to the SwitchAccessory, if needed.
    // Note: You may add specific initialization steps for the switch accessory here.
}

// SwitchAccessory destructor, additional cleanup if needed.
SwitchAccessory::~SwitchAccessory()
{
    Log_Debug(_logger, "Switch Accessory Deleted.");
    // Destructor implementation if needed.
    // Note: You may add specific cleanup steps for the switch accessory here.
}
