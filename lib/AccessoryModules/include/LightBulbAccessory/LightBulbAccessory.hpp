#ifndef LIGHT_BULB_MODULE_HPP
#define LIGHT_BULB_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>

#include "LightBulbAccessoryInterface.hpp"
#include "BasicAccessory/OnOffBasicAccessory.hpp"

/**
 * @file LightBulbAccessory.hpp
 * @brief Declaration of the LightBulbAccessory class
 * @details This header file declares the implementation of the LightBulbAccessory class, which manages light bulb accessories by controlling the relay module through button module commands or the app's setStatus method. It also handles notifications to the app when the status changes.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the LightBulbAccessory class.
 *
 * The LightBulbAccessory class is responsible for managing light bulb accessories, controlling the relay module through button module commands, or the trigger setStatus method from the app. When changing the status of the light bulb module through a button trigger, it will call the callback function to notify the app.
 */
class LightBulbAccessory : public OnOffBasicAccessory, public LightBulbAccessoryInterface
{

public:
    /**
     * @brief LightBulbAccessory constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     * @param logger The logger to use for logging. Default: nullptr.
     */
    LightBulbAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger = nullptr, uint16_t usStackDepth = 2500);

    /**
     * @brief LightBulbAccessory destructor.
     *
     * @note This destructor is responsible for stopping listening to the button module.
     */
    ~LightBulbAccessory() override;
};

#endif // LIGHT_BULB_MODULE_HPP
