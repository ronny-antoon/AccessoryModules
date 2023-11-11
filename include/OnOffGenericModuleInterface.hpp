#ifndef ON_OFF_GENERIC_MODULE_INTERFACE_HPP
#define ON_OFF_GENERIC_MODULE_INTERFACE_HPP

#include "GenericModuleInterface.hpp"

/**
 * @file OnOffGenericModuleInterface.hpp
 * @brief Defines the OnOffGenericModuleInterface class
 * @details Header file declaring the abstract interface for on/off generic modules
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for on/off generic modules.
 *
 * @details This abstract class serves as an interface for on/off generic modules,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
template <typename ModuleType>
class OnOffGenericModuleInterface : public GenericModuleInterface<ModuleType>
{
public:
    /**
     * @brief Virtual destructor for OnOffGenericModuleInterface.
     */
    virtual ~OnOffGenericModuleInterface() = default;

    /**
     * @brief Set the status of the on/off generic module.
     *
     * @param status The new status of the on/off generic module (true for on, false for off).
     *
     * @note This method don't call notify callback function, you should take care of it.
     */
    virtual void setStatus(bool status) = 0;

    /**
     * @brief Gets the current status of the on/off generic module.
     *
     * @return The current status of the on/off generic module (true for on, false for off).
     */
    virtual bool getStatus() const = 0;
};

#endif // ON_OFF_GENERIC_MODULE_INTERFACE_HPP
