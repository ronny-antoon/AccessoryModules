#ifndef OUTLET_MODULE_INTERFACE_HPP
#define OUTLET_MODULE_INTERFACE_HPP

#include "BasicAccessory/OnOffBasicAccessoryInterface.hpp"

/**
 * @file OutletAccessoryInterface.hpp
 * @brief Declaration of the OutletAccessoryInterface class
 * @details This header file declares the abstract interface for outlet accessories, extending the OnOffBasicAccessoryInterface.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for outlet accessories.
 *
 * This abstract class extends the OnOffBasicAccessoryInterface and serves as an interface for outlet accessories. It provides methods for updating the status and setting callback functions for status change events.
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
