#ifndef OUTLET_MODULE_HPP
#define OUTLET_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>

#include "OutletAccessoryInterface.hpp"
#include "BasicAccessory/OnOffBasicAccessory.hpp"

/**
 * @file OutletAccessory.hpp
 * @brief Declaration of the OutletAccessory class
 * @details This header file declares the implementation of the OutletAccessory class, which manages outlet accessories by controlling the relay module through button module commands or the app's setStatus method. It also handles notifications to the app when the status changes.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the OutletAccessory class.
 *
 * The OutletAccessory class is responsible for managing outlet accessories, controlling the relay module through button module commands, or the trigger setStatus method from the app. When changing the status of the outlet module through a button trigger, it will call the callback function to notify the app.
 */
class OutletAccessory : public OnOffBasicAccessory, public OutletAccessoryInterface
{
private:
    MultiPrinterLoggerInterface *_logger; ///< The logger to use for logging.

public:
    /**
     * @brief OutletAccessory constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     * @param logger The logger to use for logging. Default: nullptr.
     */
    OutletAccessory(RelayModuleInterface *relayAccessory, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger = nullptr);

    /**
     * @brief OutletAccessory destructor.
     *
     * @note This destructor is responsible for stopping listening to the button module.
     */
    ~OutletAccessory() override;
};

#endif // OUTLET_MODULE_HPP
