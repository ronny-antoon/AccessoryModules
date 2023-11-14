#ifndef LIGHT_BULB_ACCESSORY_INTERFACE_HPP
#define LIGHT_BULB_ACCESSORY_INTERFACE_HPP

#include "BasicAccessory/OnOffBasicAccessoryInterface.hpp"

/**
 * @file LightBulbAccessoryInterface.hpp
 * @brief Declaration of the LightBulbAccessoryInterface class
 * @details This header file declares the abstract interface for light bulb accessories, extending the OnOffBasicAccessoryInterface.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for light bulb accessories.
 *
 * This abstract class extends the OnOffBasicAccessoryInterface and serves as an interface for light bulb accessories. It provides methods for updating the status and setting callback functions for status change events.
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
