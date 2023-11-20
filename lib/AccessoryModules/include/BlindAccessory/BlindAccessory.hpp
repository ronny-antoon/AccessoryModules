#ifndef BLIND_ACCESSORY_HPP
#define BLIND_ACCESSORY_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>

#include <freertos/FreeRTOS.h> // TaskHandle_t
#include <freertos/task.h>     // TaskHandle_t

#ifndef INCLUDE_uxTaskGetStackHighWaterMark
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#endif // INCLUDE_uxTaskGetStackHighWaterMark
#ifndef INCLUDE_vTaskDelete
#define INCLUDE_vTaskDelete 1
#endif // INCLUDE_vTaskDelete

#include "BlindAccessoryInterface.hpp"

/**
 * @file BlindAccessory.hpp
 * @brief Defines the BlindAccessory class
 * @details Header file declaring the implementation of the BlindAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the BlindAccessory class.
 *
 * This class manages blind accessories, interacting with RelayModuleInterface and ButtonModuleInterface for blind movement control.
 */
class BlindAccessory : public BlindAccessoryInterface
{
private:
    MultiPrinterLoggerInterface *_logger; ///< The logger to use for logging.

    RelayModuleInterface *_motorUp;     ///< The relay module associated with moving the blind up.
    RelayModuleInterface *_motorDown;   ///< The relay module associated with moving the blind down.
    ButtonModuleInterface *_buttonUp;   ///< The button module associated with moving the blind up.
    ButtonModuleInterface *_buttonDown; ///< The button module associated with moving the blind down.

    void (*_notifyAPP)(void *); ///< Callback function to notify the app.
    void *_callbackParameter;   ///< Parameter for the callback function to notify the app.

    uint8_t _blindPosition; ///< Current position of the blind. 0-100.
    uint8_t _timeToOpen;    ///< Time to fully open the blind, in seconds.
    uint8_t _timeToClose;   ///< Time to fully close the blind, in seconds.

    void startMoveUp();   ///< Start moving the blind up.
    void startMoveDown(); ///< Start moving the blind down.
    void stopMove();      ///< Stop moving the blind.

    uint8_t _targetPostion;                    ///< Target position for the blind. 0-100.
    void moveBlindToTargetTask();              ///< Task to move the blind to a specific position.
    TaskHandle_t _moveBlindToTask_handle;      ///< Task handle for the moveBlindToTask.
    uint8_t _checkInterval;                    ///< Interval to check the postion when the blind moving. in ms.
    bool targetPositionReached(bool movingUp); ///< Check if the blind has reached the target position.

public:
    /**
     * @brief BlindAccessory constructor.
     *
     * @param motorUp The relay module associated with moving the blind up.
     * @param motorDown The relay module associated with moving the blind down.
     * @param buttonUp The button module associated with moving the blind up.
     * @param buttonDown The button module associated with moving the blind down.
     * @param timeToOpen Time to fully open the blind, in seconds. Default: 30 seconds.
     * @param timeToClose Time to fully close the blind, in seconds. Default: 30 seconds.
     * @param _logger The logger to use for logging. Default: nullptr.
     */
    BlindAccessory(RelayModuleInterface *motorUp, RelayModuleInterface *motorDown, ButtonModuleInterface *buttonUp,
                   ButtonModuleInterface *buttonDown, uint8_t timeToOpen = 30, uint8_t timeToClose = 30, MultiPrinterLoggerInterface *_logger = nullptr);

    /**
     * @brief Virtual destructor for BlindAccessory.
     */
    ~BlindAccessory() override;

    /**
     * @brief Move the blind to a specific position.
     *
     * @param position The target position for the blind.
     */
    void moveBlindTo(uint8_t position) override;

    /**
     * @brief Get the current position of the blind.
     *
     * @return The current position of the blind.
     */
    uint8_t getCurrentPosition() const override;

    /**
     * @brief Get the target position of the blind.
     *
     * @return The target position of the blind.
     */
    uint8_t getTargetPosition() const override;

    /**
     * @brief Set the callback function and its parameter for blind events.
     *
     * @param notifyAPP The callback function to be called when a blind event occurs.
     * @param pParameter The parameter to be passed to the callback function.
     */
    void setNotifyCallback(void (*notifyAPP)(void *), void *pParameter) override;
};

#endif // BLIND_ACCESSORY_HPP
