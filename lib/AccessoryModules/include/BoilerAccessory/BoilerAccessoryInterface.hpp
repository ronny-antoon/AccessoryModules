#ifndef BOILER_ACCESSORY_INTERFACE_HPP
#define BOILER_ACCESSORY_INTERFACE_HPP

#include "BasicAccessory/BasicAccessoryInterface.hpp"

/**
 * @file BoilerAccessoryInterface.hpp
 * @brief Defines the BoilerAccessoryInterface class
 * @details Header file declaring the abstract interface for boiler accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for boiler accessories.
 *
 * This abstract class serves as an interface for boiler accessories,
 * providing methods for turning the boiler on and off, checking its state, and setting the boiler state.
 */
class BoilerAccessoryInterface : public virtual BasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for BoilerAccessoryInterface.
     */
    virtual ~BoilerAccessoryInterface() = default;

    /**
     * @brief Turn on the boiler.
     */
    virtual void turnOn() = 0;

    /**
     * @brief Turn off the boiler.
     */
    virtual void turnOff() = 0;

    /**
     * @brief Check if the boiler is on.
     *
     * @return True if the boiler is on, false otherwise.
     */
    virtual bool isOn() const = 0;

    /**
     * @brief Set the boiler state.
     *
     * @param toOn True to turn the boiler on, false to turn it off.
     */
    virtual void setBoilerState(bool toOn) = 0;

    /**
     * @brief Get the remaining time for the boiler to be on.
     *
     * @return The remaining time in seconds.
     */
    virtual uint16_t getRemainingTime() const = 0;

    /**
     * @brief Set the duration time for the boiler to be on.
     *
     * @param duration The remaining time in minutes.
     */
    virtual void setDuration(uint8_t duration) = 0;

    /**
     * @brief Get the duration time for the boiler to be on.
     *
     * @return The remaining time in minutes.
     */
    virtual uint8_t getDuration() const = 0;
};

#endif // BOILER_ACCESSORY_INTERFACE_HPP
