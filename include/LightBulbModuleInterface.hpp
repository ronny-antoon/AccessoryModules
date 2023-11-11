#ifndef LIGHT_BULB_MODULE_INTERFACE_HPP
#define LIGHT_BULB_MODULE_INTERFACE_HPP

#include "OnOffBasicModuleInterface.hpp"

/**
 * @file LightBulbModuleInterface.hpp
 * @brief Defines the LightBulbModuleInterface class
 * @details Header file declaring the abstract interface for light bulb modules
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for light bulb modules.
 *
 * @details This abstract class serves as an interface for light bulb modules,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class LightBulbModuleInterface : public OnOffBasicModuleInterface
{
public:
    /**
     * @brief Virtual destructor for LightBulbModuleInterface.
     */
    virtual ~LightBulbModuleInterface() = 0;
};

#endif // LIGHT_BULB_MODULE_INTERFACE_HPP