#ifndef SWITCH_MODULE_HPP
#define SWITCH_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "SwitchAccessoryInterface.hpp"
#include "OnOffBasicAccessory.hpp"

/**
 * @file SwitchAccessory.hpp
 * @brief Defines the SwitchAccessory class
 * @details Header file declaring the implementation of the SwitchAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the SwitchAccessory class.
 *
 * @details The SwitchAccessory class is responsible for managing switch accessories,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the switch module by button trigger, it will call the callback function to notify the app.
 */
class SwitchAccessory : public OnOffBasicAccessory, public SwitchAccessoryInterface
{
public:
    /**
     * @brief
     *
     * @param relayModule
     * @param buttonModule
     */
    SwitchAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief
     *
     */
    ~SwitchAccessory() override;
};

#endif // SWITCH_MODULE_HPP