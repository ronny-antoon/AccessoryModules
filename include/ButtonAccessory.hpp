#ifndef BUTTON_ACCESSORY_HPP
#define BUTTON_ACCESSORY_HPP

#include "ButtonAccessoryInterface.hpp"
#include "ButtonModuleInterface.hpp"

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
    ButtonModuleInterface *_buttonModule; ///< The button module associated with this accessory.

    /**
     * @brief Stop listening for press events.
     */
    void stopListening();

    void (*_pressEventCallback)(void *, PressType); ///< Callback function for press events.
    void *_pressEventCallbackParameter;             ///< Parameter to be passed to the callback function.

public:
    /**
     * @brief ButtonAccessory constructor.
     *
     * @param buttonModule The button module to be associated with this accessory.
     */
    ButtonAccessory(ButtonModuleInterface *buttonModule);

    /**
     * @brief Virtual destructor for ButtonAccessory.
     */
    ~ButtonAccessory() override;

    /**
     * @brief Set the callback function for press events.
     *
     * @param pressEventCallback The callback function to be called when a press event occurs.
     * @param pressEventCallbackParameter The parameter to be passed to the callback function.
     */
    void setOnPressEvent(void (*pressEventCallback)(void *, PressType), void *pressEventCallbackParameter) override;

    /**
     * @brief Start listening for press events.
     *
     * @note This method should be called after setting the callback function for press events.
     */
    void startListening() override;
};

#endif // BUTTON_ACCESSORY_HPP