#ifndef BUTTON_ACCESSORY_HPP
#define BUTTON_ACCESSORY_HPP

#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>

#include "ButtonAccessoryInterface.hpp"

/**
 * @file ButtonAccessory.hpp
 * @brief Defines the ButtonAccessory class
 * @details Header file declaring the implementation of the ButtonAccessory class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the ButtonAccessory class.
 *
 * This class is responsible for managing button accessories,
 * interacting with a ButtonModuleInterface to handle press events.
 */
class ButtonAccessory : public ButtonAccessoryInterface
{
private:
    MultiPrinterLoggerInterface *_logger; ///< The logger to use for logging.

    ButtonModuleInterface *_buttonModule; ///< The button module associated with this accessory.

    void (*_notifyAPP)(void *); ///< Callback function to notify the app
    void *_callbackParameter;   ///< Parameter for the callback function to notify the app
    PressType _lastPressEvent;  ///< Variable to store the last press event that occurred.

public:
    /**
     * @brief ButtonAccessory constructor.
     *
     * @param buttonModule The button module to be associated with this accessory.
     * @param logger The logger to use for logging. Default: nullptr.
     */
    ButtonAccessory(ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger = nullptr);

    /**
     * @brief Virtual destructor for ButtonAccessory.
     */
    ~ButtonAccessory() override;

    /**
     * @brief Gets the last press event that occurred.
     *
     * @return The last press event that occurred.
     */
    PressType getLastPressEvent() const override;

    /**
     * @brief Sets the callback function for notifying press events.
     *
     * @param callback The callback function to be called when a press event occurs.
     * @param callbackParameter The parameter to be passed to the callback function.
     *
     * @note The callback function should be of the form: void callback(void *pParameter)
     * @note Use getLastPressEvent() to get the last press event that occurred.
     */
    void setNotifyCallback(void (*callback)(void *), void *callbackParameter) override;
};

#endif // BUTTON_ACCESSORY_HPP
