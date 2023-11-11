#ifndef BASIC_MODULE_INTERFACE_HPP
#define BASIC_MODULE_INTERFACE_HPP

/**
 * @file BasicModuleInterface.hpp
 * @brief Defines the BasicModuleInterface class
 * @details Header file declaring the implementation of the BasicModuleInterface class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for basic modules.
 *
 * @details This abstract class serves as an interface for basic modules,
 * providing methods for setting callback functions for status change events.
 * The callback function will be called when the status of the basic module changes by the module itself.
 */
class BasicModuleInterface
{
public:
    /**
     * @brief Virtual destructor for BasicModuleInterface.
     */
    virtual ~BasicModuleInterface() = default;

    /**
     * @brief Sets the callback function for notifying events.
     *
     * @param callback The callback function, taking a void pointer parameter.
     * @param _pParameter The void pointer parameter for the callback function.
     */
    virtual void setNotifyCallback(void (*callback)(void *), void *pParameter) = 0;
};

#endif // BASIC_MODULE_INTERFACE_HPP
