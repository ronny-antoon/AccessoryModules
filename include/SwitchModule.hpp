#ifndef SWITCH_MODULE_HPP
#define SWITCH_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "SwitchModuleInterface.hpp"
#include "OnOffBasicModule.hpp"

/**
 * @file SwitchModule.hpp
 * @brief Defines the SwitchModule class
 * @details Header file declaring the implementation of the SwitchModule class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the SwitchModule class.
 *
 * @details The SwitchModule class is responsible for managing switch modules,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the switch module by button trigger, it will call the callback function to notify the app.
 */
class SwitchModule : public OnOffBasicModule, public SwitchModuleInterface
{
public:
    /**
     * @brief
     *
     * @param relayModule
     * @param buttonModule
     */
    SwitchModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief
     *
     */
    ~SwitchModule() override;
};

#endif // SWITCH_MODULE_HPP