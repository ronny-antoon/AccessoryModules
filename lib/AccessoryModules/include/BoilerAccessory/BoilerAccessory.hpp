#ifndef BOILER_ACCESSORY_HPP
#define BOILER_ACCESSORY_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>
#include <TaskTracker.hpp>

#include "BoilerAccessoryInterface.hpp"

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
    MultiPrinterLoggerInterface *_logger; ///< The logger to use for logging.

    RelayModuleInterface *_relayModule;   ///< The relay module associated with this boiler accessory.
    ButtonModuleInterface *_buttonModule; ///< The button module associated with this boiler accessory.

    void (*_notifyAPP)(void *); ///< Callback function to notify the app.
    void *_callbackParameter;   ///< Parameter for the callback function to notify the app.

    uint16_t _remainingTime;         ///< Remaining time for the boiler to be on, in seconds.
    uint8_t _timeToRun;              ///< Time to turn on the boiler, in minutes. Range: 1-255.
    void turnOnTask();               ///< Task to turn on the boiler.
    TaskHandle_t _turnOnTask_handle; ///< Task handle for the turn-on task.

public:
    /**
     * @brief BoilerAccessory constructor.
     *
     * @param relayModule The relay module associated with the boiler accessory.
     * @param buttonModule The button module associated with the boiler accessory.
     * @param timeToRun The time to turn on the boiler, in minutes. Range: 1-255. Default: 30 minutes.
     * @param logger The logger to use for logging. Default: nullptr.
     */
    BoilerAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint8_t timeToRun = 30, MultiPrinterLoggerInterface *logger = nullptr, uint16_t usStackDepth = 3000);

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

    /**
     * @brief Set the duration time for the boiler to be on.
     *
     * @param duration The remaining time in minutes.
     */
    void setDuration(uint8_t duration) override;

    /**
     * @brief Get the duration time for the boiler to be on.
     *
     * @return The remaining time in minutes.
     */
    uint8_t getDuration() const override;
};

#endif // BOILER_ACCESSORY_HPP
