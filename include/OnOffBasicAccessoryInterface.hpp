#ifndef ON_OFF_BASIC_MODULE_INTERFACE_HPP
#define ON_OFF_BASIC_MODULE_INTERFACE_HPP

#include "BasicAccessoryInterface.hpp"

/**
 * @file OnOffBasicAccessoryInterface.hpp
 * @brief Defines the OnOffBasicAccessoryInterface class
 * @details Header file declaring the abstract interface for on/off basic accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief
 *
 * @details
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
     * @note This method don't call notify callback function, you should take care of it.
     */
    virtual void setStatus(bool status) = 0;

    /**
     * @brief Gets the current status of the on/off basic accessory.
     *
     * @return The current status of the on/off basic accessory (true for on, false for off).
     */
    virtual bool getStatus() const = 0;
};

#endif // ON_OFF_BASIC_MODULE_INTERFACE_HPP
