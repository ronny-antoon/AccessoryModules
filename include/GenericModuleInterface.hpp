#ifndef GENERIC_MODULE_INTERFACE_HPP
#define GENERIC_MODULE_INTERFACE_HPP

/**
 * @file GenericModuleInterface.hpp
 * @brief Defines the GenericModuleInterface class
 * @details Header file declaring the abstract interface for generic modules
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for generic modules.
 *
 * @details This abstract class serves as an interface for generic accessories modules,
 * force strongly typed modules to implement the notify callback method.
 */
template <typename ModuleType>
class GenericModuleInterface
{
public:
    /**
     * @brief Virtual destructor for GenericModuleInterface.
     */
    virtual ~GenericModuleInterface() = default;

    /**
     * @brief Sets the callback function for notifying events.
     *
     * @param callback The callback function, taking a void pointer parameter.
     * @param _pParameter The void pointer parameter for the callback function.
     */
    virtual void setNotifyCallback(void (*callback)(void *), void *_pParameter) = 0;
};

#endif // GENERIC_MODULE_INTERFACE_HPP
