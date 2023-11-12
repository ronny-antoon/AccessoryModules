#ifndef DOOR_LOCK_ACCESSORY_INTERFACE_HPP
#define DOOR_LOCK_ACCESSORY_INTERFACE_HPP

#include "BasicAccessoryInterface.hpp"

/**
 * @file DoorLockAccessoryInterface.hpp
 * @brief Defines the DoorLockAccessoryInterface class
 * @details Header file declaring the abstract interface for door lock accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for door lock accessories.
 *
 * This abstract class serves as an interface for door lock accessories,
 * providing methods for opening, closing, checking the door state, and setting the lock state.
 */
class DoorLockAccessoryInterface : public virtual BasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for DoorLockAccessoryInterface.
     */
    virtual ~DoorLockAccessoryInterface() = default;

    /**
     * @brief Open the door.
     */
    virtual void openDoor() = 0;

    /**
     * @brief Close the door.
     */
    virtual void closeDoor() = 0;

    /**
     * @brief Check if the door is open.
     *
     * @return True if the door is open, false otherwise.
     */
    virtual bool isDoorOpen() const = 0;

    /**
     * @brief Set the lock state of the door.
     *
     * @param toOpen True to set the door to an open state, false to set it to a closed state.
     */
    virtual void setLockState(bool toOpen) = 0;
};

#endif // DOOR_LOCK_ACCESSORY_INTERFACE_HPP
