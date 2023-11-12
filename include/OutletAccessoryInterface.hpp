#ifndef OUTLET_MODULE_INTERFACE_HPP
#define OUTLET_MODULE_INTERFACE_HPP

#include "OnOffBasicAccessoryInterface.hpp"

/**
 * @file OutletAccessoryInterface.hpp
 * @brief Defines the OutletAccessoryInterface class
 * @details Header file declaring the abstract interface for outlet accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for outlet accessories.
 *
 * @details This abstract class serves as an interface for outlet accessories,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class OutletAccessoryInterface : public virtual OnOffBasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for OutletAccessoryInterface.
     */
    virtual ~OutletAccessoryInterface() = default;
};

#endif // OUTLET_MODULE_INTERFACE_HPP