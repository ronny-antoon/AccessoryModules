#ifndef SWITCH_MODULE_INTERFACE_HPP
#define SWITCH_MODULE_INTERFACE_HPP

#include "OnOffBasicAccessoryInterface.hpp"

/**
 * @file SwitchAccessoryInterface.hpp
 * @brief Declaration of the SwitchAccessoryInterface class
 * @details This header file declares the abstract interface for switch accessories, extending the OnOffBasicAccessoryInterface.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for switch accessories.
 *
 * This abstract class extends the OnOffBasicAccessoryInterface and serves as an interface for switch accessories. It provides methods for updating the status and setting callback functions for status change events.
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
