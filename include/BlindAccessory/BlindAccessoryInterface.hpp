#ifndef BLIND_ACCESSORY_INTERFACE_HPP
#define BLIND_ACCESSORY_INTERFACE_HPP

#include <stdint.h> // uint8_t

#include "BasicAccessory/BasicAccessoryInterface.hpp"

/**
 * @file BlindAccessoryInterface.hpp
 * @brief Defines the BlindAccessoryInterface class
 * @details Header file declaring the abstract interface for blind accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for blind accessories.
 *
 * This abstract class defines the interface for blind accessories,
 * offering methods to control the blind's position and retrieve its current position.
 */
class BlindAccessoryInterface : public virtual BasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for BlindAccessoryInterface.
     */
    virtual ~BlindAccessoryInterface() = default;

    /**
     * @brief Move the blind to a specific position.
     *
     * @param position The target position for the blind.
     */
    virtual void moveBlindTo(uint8_t position) = 0;

    /**
     * @brief Get the current position of the blind.
     *
     * @return The current position of the blind.
     */
    virtual uint8_t getCurrentPosition() const = 0;

    /**
     * @brief Get the target position of the blind.
     *
     * @return The target position of the blind.
     */
    virtual uint8_t getTargetPosition() const = 0;
};

#endif // BLIND_ACCESSORY_INTERFACE_HPP
