#ifndef BUTTON_ACCESSORY_INTERFACE_HPP
#define BUTTON_ACCESSORY_INTERFACE_HPP

#include "BasicAccessoryInterface.hpp"

/**
 * @file ButtonAccessoryInterface.hpp
 * @brief Defines the ButtonAccessoryInterface class
 * @details Header file declaring the abstract interface for button accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for button accessories.
 *
 * This abstract class serves as an interface for button accessories,
 * providing methods for handling press events and starting the event listening process.
 */
class ButtonAccessoryInterface : public virtual BasicAccessoryInterface
{
public:
    /**
     * @brief Enumerated type for the type of press event that occurred.
     */
    enum PressType
    {
        SinglePress, ///< Represents a single press event.
        DoublePress, ///< Represents a double press event.
        LongPress    ///< Represents a long press event.
    };

    /**
     * @brief Virtual destructor for ButtonAccessoryInterface.
     */
    virtual ~ButtonAccessoryInterface() = default;

    /**
     * @brief Set the callback function for press events.
     *
     * @param pressEventCallback The callback function to be called when a press event occurs.
     * @param pressEventCallbackParameter The parameter to be passed to the callback function.
     *
     * @note The callback function should have the following signature:
     * @code {.cpp}
     * void callback(void *pParameter, PressType pressType);
     * @endcode
     */
    virtual void setOnPressEvent(void (*pressEventCallback)(void *, PressType), void *pressEventCallbackParameter) = 0;

    /**
     * @brief Start listening for press events.
     *
     * @note This method should be called after setting the callback function for press events.
     */
    virtual void startListening() = 0;
};

#endif // BUTTON_ACCESSORY_INTERFACE_HPP