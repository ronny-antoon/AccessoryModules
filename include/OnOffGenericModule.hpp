#ifndef ON_OFF_GENERIC_MODULE_HPP
#define ON_OFF_GENERIC_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>

#include "OnOffGenericModuleInterface.hpp"

/**
 * @file OnOffGenericModule.hpp
 * @brief Defines the OnOffGenericModule class template
 * @details Header file declaring the implementation of the OnOffGenericModule class template
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the OnOffGenericModule class template.
 *
 * @details The OnOffGenericModule class template is responsible for managing on/off generic modules,
 * controlling the relay module by button module command or by the trigger setStatus method from the app.
 * When changing the status of the on/off generic module by button trigger, it will call the callback function to notify the app.
 */
template <typename ModuleType>
class OnOffGenericModule : public OnOffGenericModuleInterface<ModuleType>
{
private:
    RelayModuleInterface *_relayModule;
    ButtonModuleInterface *_buttonModule;
    void (*_notifyAPP)(void *); // Callback function to notify the app
    void *_pParameter;          // Parameter for the callback function to notify the app

public:
    /**
     * @brief OnOffGenericModule constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    OnOffGenericModule(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule);

    /**
     * @brief Virtual destructor for OnOffGenericModule.
     *
     * @note This destructor is responsible for stop listening to the button module.
     */
    ~OnOffGenericModule();

    /**
     * @brief Set the status of the on/off generic module.
     *
     * @param status The new status of the on/off generic module (true for on, false for off).
     *
     * @note This method don't call notify callback function; you should take care of it.
     */
    void setStatus(bool status) override;

    /**
     * @brief Gets the current status of the on/off generic module.
     *
     * @return The current status of the on/off generic module (true for on, false for off).
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

#endif // ON_OFF_GENERIC_MODULE_HPP
