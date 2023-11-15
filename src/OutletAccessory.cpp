#include "OutletAccessory/OutletAccessory.hpp"

// OutletAccessory constructor, initializing OnOffBasicAccessory with relayModule and buttonModule.
OutletAccessory::OutletAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger)
    : OnOffBasicAccessory(relayModule, buttonModule), _logger(logger) // Initialization of OnOffBasicAccessory
{
    Log_Debug(_logger, "Outlet Accessory Created.");
    // Additional initialization specific to the OutletAccessory, if needed.
    // Note: You may add specific initialization steps for the outlet accessory here.
}

// OutletAccessory destructor, additional cleanup if needed.
OutletAccessory::~OutletAccessory()
{
    Log_Debug(_logger, "Outlet Accessory Deleted.");
    // Destructor implementation if needed.
    // Note: You may add specific cleanup steps for the outlet accessory here.
}
