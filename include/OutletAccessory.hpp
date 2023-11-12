#ifndef OUTLET_MODULE_HPP
#define OUTLET_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "OutletAccessoryInterface.hpp"
#include "OnOffBasicAccessory.hpp"

/**
 * @file OutletAccessory.hpp
 * @brief Defines the OutletAccessory class
 * @details Header file declaring the implementation of the OutletAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the OutletAccessory class.
 *
 * @details The OutletAccessory class is responsible for managing outlet accessories,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the outlet module by button trigger, it will call the callback function to notify the app.
 */
class OutletAccessory : public OnOffBasicAccessory, public OutletAccessoryInterface
{
public:
    /**
     * @brief OutletAccessory constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    OutletAccessory(RelayModuleInterface *relayAccessory, ButtonModuleInterface *buttonModule);

    /**
     * @brief  destructor for OutletAccessory.
     *
     * @note This destructor is responsible for stop listening to the button module.
     */
    ~OutletAccessory() override;
};

#endif // OUTLET_MODULE_HPP