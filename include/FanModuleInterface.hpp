#ifndef FAN_MODULE_INTERFACE_HPP
#define FAN_MODULE_INTERFACE_HPP

#include "OnOffBasicModuleInterface.hpp"

/**
 * @file FanModuleInterface.hpp
 * @brief Defines the FanModuleInterface class
 * @details Header file declaring the abstract interface for fan modules
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for fan modules.
 *
 * @details This abstract class serves as an interface for fan modules,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class FanModuleInterface : public virtual OnOffBasicModuleInterface
{
public:
    /**
     * @brief Virtual destructor for FanModuleInterface.
     */
    virtual ~FanModuleInterface() = default;
};

#endif // FAN_MODULE_INTERFACE_HPP