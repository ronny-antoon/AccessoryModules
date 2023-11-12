#ifndef ON_OFF_BASIC_MODULE_INTERFACE_HPP
#define ON_OFF_BASIC_MODULE_INTERFACE_HPP

#include "BasicAccessoryInterface.hpp"

/**
 * @file OnOffBasicAccessoryInterface.hpp
 * @brief Declaration of the OnOffBasicAccessoryInterface class
 * @details This header file declares the abstract interface for on/off basic accessories, extending the BasicAccessoryInterface.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for on/off basic accessories.
 *
 * This class extends the BasicAccessoryInterface and defines methods specific to on/off basic accessories. It includes functionality to set and retrieve the status of the on/off basic accessory.
 */
class OnOffBasicAccessoryInterface : public BasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for OnOffBasicAccessoryInterface.
     */
    virtual ~OnOffBasicAccessoryInterface() = default;

    /**
     * @brief Set the status of the on/off basic accessory.
     *
     * @param status The new status of the on/off basic accessory (true for on, false for off).
     *
     * @note This method does not call the notify callback function; you should handle it separately.
     */
    virtual void setStatus(bool status, bool notfy) = 0;

    /**
     * @brief Gets the current status of the on/off basic accessory.
     *
     * @return The current status of the on/off basic accessory (true for on, false for off).
     */
    virtual bool getStatus() const = 0;
};

#endif // ON_OFF_BASIC_MODULE_INTERFACE_HPP
