#ifndef SWITCH_MODULE_HPP
#define SWITCH_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>

#include "SwitchAccessoryInterface.hpp"
#include "BasicAccessory/OnOffBasicAccessory.hpp"

/**
 * @file SwitchAccessory.hpp
 * @brief Declaration of the SwitchAccessory class
 * @details This header file declares the implementation of the SwitchAccessory class, which manages switch accessories by controlling the relay module through button module commands or the app's setStatus method. It also handles notifications to the app when the status changes.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the SwitchAccessory class.
 *
 * The SwitchAccessory class is responsible for managing switch accessories, controlling the relay module through button module commands, or the trigger setStatus method from the app. When changing the status of the switch module through a button trigger, it will call the callback function to notify the app.
 */
class SwitchAccessory : public OnOffBasicAccessory, public SwitchAccessoryInterface
{

public:
    /**
     * @brief SwitchAccessory constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     * @param logger The logger to use for logging. Default: nullptr.
     */
    SwitchAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger = nullptr, uint16_t usStackDepth = 3000);

    /**
     * @brief SwitchAccessory destructor.
     */
    ~SwitchAccessory() override;
};

#endif // SWITCH_MODULE_HPP
