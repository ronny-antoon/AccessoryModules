#ifndef FAN_ACCESSORY_HPP
#define FAN_ACCESSORY_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "FanAccessoryInterface.hpp"
#include "OnOffBasicAccessory.hpp"

/**
 * @file FanAccessory.hpp
 * @brief Defines the FanAccessory class
 * @details Header file declaring the implementation of the FanAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the FanAccessory class.
 *
 * @details The FanAccessory class is responsible for managing fan accessories,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the fan module by button trigger, it will call the callback function to notify the app.
 */

class FanAccessory : public OnOffBasicAccessory, public FanAccessoryInterface
{
public:
    /**
     * @brief
     *
     * @param relayModule
     * @param buttonModule
     */
    FanAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief
     *
     */
    ~FanAccessory() override;
};

#endif // FAN_ACCESSORY_HPP