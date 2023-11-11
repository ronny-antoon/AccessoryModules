#ifndef OUTLET_MODULE_INTERFACE_HPP
#define OUTLET_MODULE_INTERFACE_HPP

#include "OnOffBasicModuleInterface.hpp"

/**
 * @file OutletModuleInterface.hpp
 * @brief Defines the OutletModuleInterface class
 * @details Header file declaring the abstract interface for outlet modules
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for outlet modules.
 *
 * @details This abstract class serves as an interface for outlet modules,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class OutletModuleInterface : public virtual OnOffBasicModuleInterface
{
public:
    /**
     * @brief Virtual destructor for OutletModuleInterface.
     */
    virtual ~OutletModuleInterface() = default;
};

#endif // OUTLET_MODULE_INTERFACE_HPP