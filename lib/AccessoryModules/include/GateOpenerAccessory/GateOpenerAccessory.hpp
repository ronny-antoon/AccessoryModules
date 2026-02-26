#ifndef GATE_OPENER_ACCESSORY_HPP
#define GATE_OPENER_ACCESSORY_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>

#include <TaskTracker.hpp>

#include "GateOpenerAccessoryInterface.hpp"

/**
 * @file GateOpenerAccessory.hpp
 * @brief Defines the GateOpenerAccessory class
 * @details Header file declaring the implementation of the GateOpenerAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the GateOpenerAccessory class.
 *
 * This class is responsible for managing gate opener accessories,
 * interacting with a RelayModuleInterface to activate the dry contact for opening/closing the gate,
 * without monitoring the gate state.
 */

class GateOpenerAccessory : public GateOpenerAccessoryInterface
{
private:
    MultiPrinterLoggerInterface *_logger; ///< The logger to use for logging.

    RelayModuleInterface *_relayModule;   ///< The relay module associated with this gate opener accessory.
    ButtonModuleInterface *_buttonModule; ///< The button module associated with this gate opener accessory.

    void (*_notifyAPP)(void *); ///< Callback function to notify the app.
    void *_callbackParameter;   ///< Parameter for the callback function to notify the app.

    uint16_t _timeToActivate;                    ///< Time to hold the dry contact for opening/closing the gate in milliseconds. Range: 1-65535.
    void activateDryContactTask();               ///< Task to activate the dry contact for opening/closing the gate.
    TaskHandle_t _activateDryContactTask_handle; ///< Task handle for the activate dry contact task.

public:
    /**
     *  @brief GateOpenerAccessory constructor.
     *
     * @param relayModule The relay module associated with the gate opener accessory.
     * @param buttonModule The button module associated with the gate opener accessory.
     * @param timeToActivate Time to hold the dry contact for opening/closing the gate
     * in milliseconds. Range: 1-65535.
     * @param logger The logger to use for logging. Default: nullptr.
     */
    GateOpenerAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint16_t timeToActivate = 400, MultiPrinterLoggerInterface *logger = nullptr, uint16_t usStackDepth = 3000);

    /**
     * @brief Virtual destructor for GateOpenerAccessory.
     */
    ~GateOpenerAccessory() override;

    /**
     * @brief Sets the callback function for notifying events.
     *
     * @param callback The callback function, taking a void pointer parameter.
     * @param callbackParameter The void pointer parameter for the callback function.
     */
    void setNotifyCallback(void (*callback)(void *), void *callbackParameter) override;

    /**
     * @brief Activate the dry contact to open/close the gate.
     */
    void activateDryContact() override;

    // /**
    //  * @brief Set the state of the gate.
    //  *
    //  * @param toOpen True to set the gate to an open state, false
    //  * to set it to a closed state.
    //  * @param notfy True to notify the app, false otherwise.
    //  */
    // void setGateState(bool toOpen, bool notfy) override;
};

#endif // GATE_OPENER_ACCESSORY_HPP