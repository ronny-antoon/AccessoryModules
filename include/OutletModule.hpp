#ifndef OUTLET_MODULE_HPP
#define OUTLET_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "OutletModuleInterface.hpp"
#include "OnOffBasicModule.hpp"

/**
 * @file OutletModule.hpp
 * @brief Defines the OutletModule class
 * @details Header file declaring the implementation of the OutletModule class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the OutletModule class.
 *
 * @details The OutletModule class is responsible for managing outlet modules,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the outlet module by button trigger, it will call the callback function to notify the app.
 */
class OutletModule : public OnOffBasicModule, public OutletModuleInterface
{
public:
    /**
     * @brief OutletModule constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    OutletModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief  destructor for OutletModule.
     *
     * @note This destructor is responsible for stop listening to the button module.
     */
    ~OutletModule() override;
};

#endif // OUTLET_MODULE_HPP