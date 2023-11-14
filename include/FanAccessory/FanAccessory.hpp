#ifndef FAN_ACCESSORY_HPP
#define FAN_ACCESSORY_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "FanAccessoryInterface.hpp"
#include "BasicAccessory/OnOffBasicAccessory.hpp"

/**
 * @file FanAccessory.hpp
 * @brief Declaration of the FanAccessory class
 * @details This header file declares the implementation of the FanAccessory class, which manages fan accessories by controlling the relay module through button module commands or the app's setStatus method. It also handles notifications to the app when the status changes.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the FanAccessory class.
 *
 * The FanAccessory class is responsible for managing fan accessories, controlling the relay module through button module commands, or the trigger setStatus method from the app. When changing the status of the fan module through a button trigger, it will call the callback function to notify the app.
 */
class FanAccessory : public OnOffBasicAccessory, public FanAccessoryInterface
{
public:
    /**
     * @brief FanAccessory constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    FanAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief FanAccessory destructor.
     */
    ~FanAccessory() override;
};

#endif // FAN_ACCESSORY_HPP
