#ifndef BUTTON_ACCESSORY_INTERFACE_HPP
#define BUTTON_ACCESSORY_INTERFACE_HPP

#include <stdint.h> // uint8_t

#include "BasicAccessory/BasicAccessoryInterface.hpp"

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
 * providing methods for handling press events.
 */
class ButtonAccessoryInterface : public virtual BasicAccessoryInterface
{
public:
    /**
     * @brief Enumerated type for the type of press event that occurred.
     */
    enum PressType : uint8_t
    {
        SinglePress = 1, ///< Represents a single press event.
        DoublePress = 2, ///< Represents a double press event.
        LongPress = 3    ///< Represents a long press event.
    };

    /**
     * @brief Virtual destructor for ButtonAccessoryInterface.
     */
    virtual ~ButtonAccessoryInterface() = default;

    /**
     * @brief Gets the last press event that occurred.
     *
     * @return The last press event that occurred.
     */
    virtual PressType getLastPressEvent() const = 0;
};

#endif // BUTTON_ACCESSORY_INTERFACE_HPP
