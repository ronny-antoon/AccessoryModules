#ifndef SWITCH_MODULE_INTERFACE_HPP
#define SWITCH_MODULE_INTERFACE_HPP

#include "OnOffBasicAccessoryInterface.hpp"

/**
 * @file SwitchAccessoryInterface.hpp
 * @brief Defines the SwitchAccessoryInterface class
 * @details Header file declaring the abstract interface for switch accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for switch accessories.
 *
 * @details This abstract class serves as an interface for switch accessories,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class SwitchAccessoryInterface : public virtual OnOffBasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for SwitchAccessoryInterface.
     */
    virtual ~SwitchAccessoryInterface() = default;
};

#endif // SWITCH_MODULE_INTERFACE_HPP