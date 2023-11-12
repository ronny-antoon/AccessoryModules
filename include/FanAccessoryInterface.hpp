#ifndef FAN_MODULE_INTERFACE_HPP
#define FAN_MODULE_INTERFACE_HPP

#include "OnOffBasicAccessoryInterface.hpp"

/**
 * @file FanAccessoryInterface.hpp
 * @brief Defines the FanAccessoryInterface class
 * @details Header file declaring the abstract interface for fan accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for fan accessories.
 *
 * @details This abstract class serves as an interface for fan accessories,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class FanAccessoryInterface : public virtual OnOffBasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for FanAccessoryInterface.
     */
    virtual ~FanAccessoryInterface() = default;
};

#endif // FAN_MODULE_INTERFACE_HPP