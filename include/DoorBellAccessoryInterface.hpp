#ifndef DOOR_BELL_ACCESSORY_INTERFACE_HPP
#define DOOR_BELL_ACCESSORY_INTERFACE_HPP

#include "BasicAccessoryInterface.hpp"

/**
 * @file DoorBellAccessoryInterface.hpp
 * @brief Defines the DoorBellAccessoryInterface class
 * @details Header file declaring the abstract interface for door bell accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for door bell accessories.
 *
 * This abstract class serves as an interface for door bell accessories,
 * providing methods for handling press events.
 */
class DoorBellAccessoryInterface : public virtual BasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for DoorBellAccessoryInterface.
     */
    virtual ~DoorBellAccessoryInterface() = default;
};

#endif // DOOR_BELL_ACCESSORY_INTERFACE_HPP