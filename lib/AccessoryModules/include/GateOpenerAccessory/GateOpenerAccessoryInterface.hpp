#ifndef GATE_OPENER_ACCESSORY_INTERFACE_HPP
#define GATE_OPENER_ACCESSORY_INTERFACE_HPP

#include "BasicAccessory/BasicAccessoryInterface.hpp"
/**
 * @file GateOpenerAccessoryInterface.hpp
 * @brief Defines the GateOpenerAccessoryInterface class
 * @details Header file declaring the abstract interface for gate opener accessories
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Interface for gate opener accessories.
 *
 * This abstract class serves as an interface for gate opener accessories,
 * providing methods for dry contact operations, without monitoring the gate state.
 */
class GateOpenerAccessoryInterface : public virtual BasicAccessoryInterface
{
public:
    /**
     * @brief Virtual destructor for GateOpenerAccessoryInterface.
     */
    virtual ~GateOpenerAccessoryInterface() = default;

    /**
     * @brief Activate the dry contact to open/close the gate.
     *
     * @param notfy True to notify the app, false otherwise.
     */
    virtual void activateDryContact(bool notfy) = 0;
};

#endif // GATE_OPENER_ACCESSORY_INTERFACE_HPP