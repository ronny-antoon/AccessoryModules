#ifndef ON_OFF_BASIC_MODULE_INTERFACE_HPP
#define ON_OFF_BASIC_MODULE_INTERFACE_HPP

#include "BasicModuleInterface.hpp"

/**
 * @file OnOffBasicModuleInterface.hpp
 * @brief Defines the OnOffBasicModuleInterface class
 * @details Header file declaring the abstract interface for on/off basic modules
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief
 *
 * @details
 */
class OnOffBasicModuleInterface : public BasicModuleInterface
{
public:
    /**
     * @brief Virtual destructor for OnOffBasicModuleInterface.
     */
    virtual ~OnOffBasicModuleInterface() = 0;

    /**
     * @brief Set the status of the on/off basic module.
     *
     * @param status The new status of the on/off basic module (true for on, false for off).
     *
     * @note This method don't call notify callback function, you should take care of it.
     */
    virtual void setStatus(bool status) = 0;

    /**
     * @brief Gets the current status of the on/off basic module.
     *
     * @return The current status of the on/off basic module (true for on, false for off).
     */
    virtual bool getStatus() const = 0;
};

#endif // ON_OFF_BASIC_MODULE_INTERFACE_HPP
