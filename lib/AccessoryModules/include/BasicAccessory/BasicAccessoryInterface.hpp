#ifndef BASIC_ACCESSORY_INTERFACE_HPP
#define BASIC_ACCESSORY_INTERFACE_HPP

/**
 * @file BasicAccessoryInterface.hpp
 * @brief Defines the BasicAccessoryInterface class
 * @details Header file declaring the implementation of the BasicAccessoryInterface class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for basic accessories.
 *
 * @details This abstract class serves as an interface for basic accessories,
 * providing methods for setting callback functions for status change events.
 * The callback function will be called when the status of the basic accessory changes by the accessory itself.
 */
class BasicAccessoryInterface
{
private:
public:
    /**
     * @brief Virtual destructor for BasicAccessoryInterface.
     */
    virtual ~BasicAccessoryInterface() = default;

    /**
     * @brief Sets the callback function for notifying events.
     *
     * @param notifyCallback The callback function, taking a void pointer parameter.
     * @param callbackParameter The void pointer parameter for the callback function.
     */
    virtual void setNotifyCallback(void (*notifyCallback)(void *), void *callbackParameter) = 0;
};

#endif // BASIC_ACCESSORY_INTERFACE_HPP
