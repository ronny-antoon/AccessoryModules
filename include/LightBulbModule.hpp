#ifndef LIGHT_BULB_MODULE_HPP
#define LIGHT_BULB_MODULE_HPP

/**
 * @file LightBulbModule.hpp
 * @brief Defines the LightBulbModule class
 * @details Header file declaring the implementation of the LightBulbModule class
 * @version 1.0.0
 * @date 2023/11/08
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "LightBulbModuleInterface.hpp"

/**
 * @brief Implementation of the LightBulbModule class.
 *
 * @details The LightBulbModule class is responsible for managing the light bulb module,
 * controlling the relay module by button module command or by the trigger update method from the app.
 * When the app wants to change the status of the light bulb, it will call the update method,
 * and the update method will call the callback function to notify the app.
 */
class LightBulbModule : public LightBulbModuleInterface
{
private:
    /**
     * @brief Relay module.
     *
     * @details This relay module is responsible for controlling the light bulb.
     */
    RelayModuleInterface *_relayModule;

    /**
     * @brief Button module.
     *
     * @details This button module is responsible for getting the status of the button.
     */
    ButtonModuleInterface *_buttonModule;

    void (*_notifyAPP)(void *); // Callback function to notify the app
    void *_pParameter;          // Parameter for the callback function to notify the app

public:
    /**
     * @brief LightBulbModule constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    LightBulbModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief LightBulbModule destructor.
     *
     * @details This destructor is responsible for deleting the relay module and button module.
     */
    ~LightBulbModule() override;

    /**
     * @brief Update method.
     *
     * @details This method is responsible for updating the status of the light bulb.
     *
     * @param status The status of the light bulb.
     *
     * @note This method don't call notify callback function, you should take care of it.
     *
     * @return If the update was successful(true) or not(false).
     */
    bool update(bool status) override;

    /**
     * @brief SetNotifyAppCallback method.
     *
     * @details This method is responsible for setting the callback function.
     *
     * @param callback The callback function to notify the app.
     */
    void setNotifyCallback(void (*callback)(void *), void *_pParameter) override;

    /**
     * @brief GetStatus method.
     *
     * @details This method is responsible for getting the status of the light bulb.
     *
     * @return The status of the light bulb.
     */
    bool getStatus() const override;
};

#endif // LIGHT_BULB_MODULE_HPP
