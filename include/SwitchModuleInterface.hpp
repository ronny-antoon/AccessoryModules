#ifndef SWITCH_MODULE_INTERFACE_HPP
#define SWITCH_MODULE_INTERFACE_HPP

#include "OnOffBasicModuleInterface.hpp"

/**
 * @file SwitchModuleInterface.hpp
 * @brief Defines the SwitchModuleInterface class
 * @details Header file declaring the abstract interface for switch modules
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for switch modules.
 *
 * @details This abstract class serves as an interface for switch modules,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class SwitchModuleInterface : public virtual OnOffBasicModuleInterface
{
public:
    /**
     * @brief Virtual destructor for SwitchModuleInterface.
     */
    virtual ~SwitchModuleInterface() = default;
};

#endif // SWITCH_MODULE_INTERFACE_HPP