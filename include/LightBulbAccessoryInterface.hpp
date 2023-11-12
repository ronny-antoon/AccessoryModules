#ifndef LIGHT_BULB_ACCESSORY_INTERFACE_HPP
#define LIGHT_BULB_ACCESSORY_INTERFACE_HPP

#include "OnOffBasicAccessoryInterface.hpp"

/**
 * @file LightBulbAccessoryInterface.hpp
 * @brief Defines the LightBulbAccessoryInterface class
 * @details Header file declaring the abstract interface for light bulb accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for light bulb accessories.
 *
 * @details This abstract class serves as an interface for light bulb accessories,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class LightBulbAccessoryInterface : public virtual OnOffBasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for LightBulbAccessoryInterface.
     */
    virtual ~LightBulbAccessoryInterface() = default;
};

#endif // LIGHT_BULB_ACCESSORY_INTERFACE_HPP