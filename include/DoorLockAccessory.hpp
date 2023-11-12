#ifndef DOOR_LOCK_ACCESSORY_HPP
#define DOOR_LOCK_ACCESSORY_HPP

#include <freertos/FreeRTOS.h> // TaskHandle_t
#include <freertos/task.h>     // TaskHandle_t

#ifndef INCLUDE_uxTaskGetStackHighWaterMark
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#endif // INCLUDE_uxTaskGetStackHighWaterMark
#ifndef INCLUDE_vTaskDelete
#define INCLUDE_vTaskDelete 1
#endif // INCLUDE_vTaskDelete

#include "DoorLockAccessoryInterface.hpp"
#include "RelayModuleInterface.hpp"
#include "ButtonModuleInterface.hpp"

/**
 * @file DoorLockAccessory.hpp
 * @brief Defines the DoorLockAccessory class
 * @details Header file declaring the implementation of the DoorLockAccessory class
 * @brief Ronny Antoon
 * @brief MetaHouse LTD.
 */

/**
 * @brief Implementation of the DoorLockAccessory class.
 *
 * This class is responsible for managing door lock accessories,
 * interacting with a RelayModuleInterface to lock and unlock the door,
 */
class DoorLockAccessory : public DoorLockAccessoryInterface
{
private:
    RelayModuleInterface *_relayModule;   ///< The relay module associated with this door lock accessory.
    ButtonModuleInterface *_buttonModule; ///< The button module associated with this door lock accessory.

    void (*_notifyAPP)(void *); ///< Callback function to notify the app.
    void *_callbackParameter;   ///< Parameter for the callback function to notify the app.

    uint8_t _timeToUnlock;             ///< Time to unlock the door in seconds. range: 1-255
    void openDoorTask();               ///< Task to open the door.
    TaskHandle_t openDoorTask_handle; ///< Task handle for the open door task.

public:
    /**
     * @brief DoorLockAccessory constructor.
     *
     * @param relayModule The relay module associated with the door lock accessory.
     * @param buttonModule The button module associated with the door lock accessory.
     */
    DoorLockAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint8_t timeToUnlock = 5);

    /**
     * @brief Virtual destructor for DoorLockAccessory.
     */
    ~DoorLockAccessory() override;

    /**
     * @brief Sets the callback function for notifying events.
     *
     * @param callback The callback function, taking a void pointer parameter.
     * @param callbackParameter The void pointer parameter for the callback function.
     */
    void setNotifyCallback(void (*callback)(void *), void *callbackParameter) override;

    /**
     * @brief Open the door.
     */
    void openDoor() override;

    /**
     * @brief Close the door.
     */
    void closeDoor() override;

    /**
     * @brief Check if the door is open.
     *
     * @return True if the door is open, false otherwise.
     */
    bool isDoorOpen() const override;

    /**
     * @brief Set the lock state of the door.
     *
     * @param toOpen True to set the door to an open state, false to set it to a closed state.
     */
    void setLockState(bool toOpen) override;
};

#endif // DOOR_LOCK_ACCESSORY_HPP