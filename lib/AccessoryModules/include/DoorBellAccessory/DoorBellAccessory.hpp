#ifndef DOOR_BELL_ACCESSORY_HPP
#define DOOR_BELL_ACCESSORY_HPP

#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>

#include "DoorBellAccessoryInterface.hpp"

/**
 * @file DoorBellAccessory.hpp
 * @brief Defines the DoorBellAccessory class
 * @details Header file declaring the implementation of the DoorBellAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the DoorBellAccessory class.
 *
 * This class is responsible for managing doorbell accessories,
 * interacting with a ButtonModuleInterface to handle doorbell events.
 */
class DoorBellAccessory : public DoorBellAccessoryInterface
{
private:
    MultiPrinterLoggerInterface *_logger; ///< The logger to use for logging.

    ButtonModuleInterface *_buttonModule; ///< The button module associated with this doorbell accessory.

    void (*_notifyAPP)(void *); ///< Callback function to notify the app.
    void *_callbackParameter;   ///< Parameter for the callback function to notify the app.

public:
    /**
     * @brief DoorBellAccessory constructor.
     *
     * @param buttonModule The button module associated with the doorbell accessory.
     * @param logger The logger to use for logging. Default: nullptr.
     */
    DoorBellAccessory(ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger = nullptr);

    /**
     * @brief Virtual destructor for DoorBellAccessory.
     */
    ~DoorBellAccessory() override;

    /**
     * @brief Sets the callback function for notifying events.
     *
     * @param callback The callback function, taking a void pointer parameter.
     * @param callbackParameter The void pointer parameter for the callback function.
     */
    void setNotifyCallback(void (*callback)(void *), void *callbackParameter) override;
};

#endif // DOOR_BELL_ACCESSORY_HPP
