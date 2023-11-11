#ifndef LIGHT_BULB_MODULE_HPP
#define LIGHT_BULB_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "LightBulbModuleInterface.hpp"
#include "OnOffBasicModule.hpp"

/**
 * @file LightBulbModule.hpp
 * @brief Defines the LightBulbModule class
 * @details Header file declaring the implementation of the LightBulbModule class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the LightBulbModule class.
 *
 * @details The LightBulbModule class is responsible for managing light bulb modules,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the light bulb module by button trigger, it will call the callback function to notify the app.
 */
class LightBulbModule : public OnOffBasicModule, public LightBulbModuleInterface
{
public:
    /**
     * @brief LightBulbModule constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    LightBulbModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief  destructor for LightBulbModule.
     *
     * @note This destructor is responsible for stop listening to the button module.
     */
    ~LightBulbModule() override;
};

#endif // LIGHT_BULB_MODULE_HPP