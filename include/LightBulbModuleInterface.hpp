#ifndef LIGHT_BULB_MODULE_INTERFACE_HPP
#define LIGHT_BULB_MODULE_INTERFACE_HPP

/**
 * @file LightBulbModuleInterface.hpp
 * @brief Defines the LightBulbModuleInterface class
 * @details Header file declaring the abstract interface for light bulb modules
 * @version 1.0.0
 * @date 2023/11/08
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for light bulb modules.
 *
 * @details This abstract class serves as an interface for light bulb modules,
 * providing methods for updating the status and setting callback functions
 * for status change events.
 */
class LightBulbModuleInterface
{
public:
    /**
     * @brief Virtual destructor for LightBulbModuleInterface.
     */
    virtual ~LightBulbModuleInterface() = default;

    /**
     * @brief Updates the status of the light bulb module.
     *
     * @param status The new status of the light bulb (true for on, false for off).
     *
     * @note This method don't call notify callback function, you should take care of it.
     *
     * @return If the update was successful(true) or not(false).
     */
    virtual bool update(bool status) = 0;

    /**
     * @brief Sets the callback function for status change events.
     *
     * @param callback The callback function, taking a boolean parameter for the status.
     * @param _pParameter The void pointer parameter for the callback function.
     */
    virtual void setNotifyCallback(void (*callback)(void *), void *_pParameter) = 0;

    /**
     * @brief Gets the current status of the light bulb module.
     *
     * @return The current status of the light bulb (true for on, false for off).
     */
    virtual bool getStatus() const = 0;
};

#endif // LIGHT_BULB_MODULE_INTERFACE_HPP
