#ifndef BOILER_ACCESSORY_HPP
#define BOILER_ACCESSORY_HPP

#include <freertos/FreeRTOS.h> // TaskHandle_t
#include <freertos/task.h>     // TaskHandle_t

#ifndef INCLUDE_uxTaskGetStackHighWaterMark
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#endif // INCLUDE_uxTaskGetStackHighWaterMark
#ifndef INCLUDE_vTaskDelete
#define INCLUDE_vTaskDelete 1
#endif // INCLUDE_vTaskDelete

#include "BoilerAccessoryInterface.hpp"
#include "RelayModuleInterface.hpp"
#include "ButtonModuleInterface.hpp"

/**
 * @file BoilerAccessory.hpp
 * @brief Defines the BoilerAccessory class
 * @details Header file declaring the implementation of the BoilerAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the BoilerAccessory class.
 *
 * This class is responsible for managing boiler accessories,
 * interacting with a RelayModuleInterface to turn the boiler on and off.
 */
class BoilerAccessory : public BoilerAccessoryInterface
{
private:
    RelayModuleInterface *_relayModule;   ///< The relay module associated with this boiler accessory.
    ButtonModuleInterface *_buttonModule; ///< The button module associated with this boiler accessory.

    void (*_notifyAPP)(void *); ///< Callback function to notify the app.
    void *_callbackParameter;   ///< Parameter for the callback function to notify the app.

    uint16_t _remainingTime;         ///< Remaining time for the boiler to be on, in seconds.
    uint8_t _timeToTurnOn;           ///< Time to turn on the boiler, in minutes. Range: 1-255.
    void turnOnTask();               ///< Task to turn on the boiler.
    TaskHandle_t _turnOnTask_handle; ///< Task handle for the turn-on task.

public:
    /**
     * @brief BoilerAccessory constructor.
     *
     * @param relayModule The relay module associated with the boiler accessory.
     * @param buttonModule The button module associated with the boiler accessory.
     * @param timeToTurnOn The time to turn on the boiler, in minutes. Range: 1-255. Default: 5 minutes.
     */
    BoilerAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint8_t timeToTurnOn = 5);

    /**
     * @brief Virtual destructor for BoilerAccessory.
     */
    ~BoilerAccessory() override;

    /**
     * @brief Turn on the boiler.
     */
    void turnOn() override;

    /**
     * @brief Turn off the boiler.
     */
    void turnOff() override;

    /**
     * @brief Check if the boiler is on.
     *
     * @return True if the boiler is on, false otherwise.
     */
    bool isOn() const override;

    /**
     * @brief Set the boiler state.
     *
     * @param toOn True to turn the boiler on, false to turn it off.
     */
    void setBoilerState(bool toOn) override;

    /**
     * @brief Get the remaining time for the boiler to be on.
     *
     * @return Remaining time in seconds.
     */
    uint16_t getRemainingTime() const override;

    /**
     * @brief Set the callback function and its parameter for boiler events.
     *
     * @param notifyAPP The callback function to be called when a boiler event occurs.
     * @param callbackParameter The parameter to be passed to the callback function.
     */
    void setNotifyCallback(void (*notifyAPP)(void *), void *callbackParameter) override;
};

#endif // BOILER_ACCESSORY_HPP
