#ifndef FAN_MODULE_INTERFACE_HPP
#define FAN_MODULE_INTERFACE_HPP

#include "BasicAccessory/OnOffBasicAccessoryInterface.hpp"

/**
 * @file FanAccessoryInterface.hpp
 * @brief Declaration of the FanAccessoryInterface class
 * @details This header file declares the abstract interface for fan accessories, extending the OnOffBasicAccessoryInterface.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for fan accessories.
 *
 * This abstract class extends the OnOffBasicAccessoryInterface and serves as an interface for fan accessories. It provides methods for updating the status and setting callback functions for status change events.
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
