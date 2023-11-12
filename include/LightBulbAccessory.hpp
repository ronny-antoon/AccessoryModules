#ifndef LIGHT_BULB_MODULE_HPP
#define LIGHT_BULB_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "LightBulbAccessoryInterface.hpp"
#include "OnOffBasicAccessory.hpp"

/**
 * @file LightBulbAccessory.hpp
 * @brief Defines the LightBulbAccessory class
 * @details Header file declaring the implementation of the LightBulbAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the LightBulbAccessory class.
 *
 * @details The LightBulbAccessory class is responsible for managing light bulb accessories,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the light bulb module by button trigger, it will call the callback function to notify the app.
 */
class LightBulbAccessory : public OnOffBasicAccessory, public LightBulbAccessoryInterface
{
public:
    /**
     * @brief LightBulbAccessory constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    LightBulbAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief  destructor for LightBulbAccessory.
     *
     * @note This destructor is responsible for stop listening to the button module.
     */
    ~LightBulbAccessory() override;
};

#endif // LIGHT_BULB_MODULE_HPP