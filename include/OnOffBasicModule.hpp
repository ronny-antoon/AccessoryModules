#ifndef ON_OFF_BASIC_MODULE_HPP
#define ON_OFF_BASIC_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "OnOffBasicModuleInterface.hpp"

/**
 * @file OnOffBasicModule.hpp
 * @brief Defines the OnOffBasicModule class
 * @details Header file declaring the implementation of the OnOffBasicModule class
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the OnOffBasicModule class.
 *
 * @details The OnOffBasicModule class is responsible for managing on/off basic modules,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the on/off basic module by button trigger, it will call the callback function to notify the app.
 */
class OnOffBasicModule : public OnOffBasicModuleInterface
{
private:
    RelayModuleInterface *_relayModule;
    ButtonModuleInterface *_buttonModule;
    void (*_notifyAPP)(void *); // Callback function to notify the app
    void *_pParameter;          // Parameter for the callback function to notify the app

public:
    /**
     * @brief OnOffBasicModule constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    OnOffBasicModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief Virtual destructor for OnOffBasicModule.
     *
     * @note This destructor is responsible for stop listening to the button module.
     */
    ~OnOffBasicModule() override;

    /**
     * @brief Set the status of the on/off basic module.
     *
     * @param status The new status of the on/off basic module (true for on, false for off).
     *
     * @note This method don't call notify callback function; you should take care of it.
     */
    void setStatus(bool status) override;

    /**
     * @brief Gets the current status of the on/off basic module.
     *
     * @return The current status of the on/off basic module (true for on, false for off).
     */
    bool getStatus() const override;

    /**
     * @brief Sets the callback function for notifying events.
     *
     * @param callback The callback function, taking a void pointer parameter.
     * @param _pParameter The void pointer parameter for the callback function.
     */
    void setNotifyCallback(void (*callback)(void *), void *_pParameter) override;
};

#endif // ON_OFF_BASIC_MODULE_HPP
