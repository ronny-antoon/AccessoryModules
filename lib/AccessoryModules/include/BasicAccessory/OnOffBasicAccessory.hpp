#ifndef ON_OFF_BASIC_MODULE_HPP
#define ON_OFF_BASIC_MODULE_HPP

#include <RelayModuleInterface.hpp>
#include <ButtonModuleInterface.hpp>
#include <MultiPrinterLoggerInterface.hpp>

#include "OnOffBasicAccessoryInterface.hpp"

/**
 * @file OnOffBasicAccessory.hpp
 * @brief Declaration of the OnOffBasicAccessory class
 * @details This header file declares the implementation of the OnOffBasicAccessory class, which manages on/off basic accessories by controlling the relay module through button module commands or the app's setStatus method. It also handles notifications to the app when the status changes.
 * @author Ronny Antoon
 * @copyright MetaHouse LTD.
 */

/**
 * @brief Implementation of the OnOffBasicAccessory class.
 *
 * The OnOffBasicAccessory class is responsible for managing on/off basic accessories, controlling the relay module through button module commands, or the trigger setStatus method from the app. When changing the status of the on/off basic module through a button trigger, it will call the callback function to notify the app.
 */
class OnOffBasicAccessory : public virtual OnOffBasicAccessoryInterface
{
private:
    RelayModuleInterface *_relayModule;
    ButtonModuleInterface *_buttonModule;
    void (*_notifyAPP)(void *); // Callback function to notify the app
    void *_callbackParameter;   // Parameter for the callback function to notify the app

protected:
    MultiPrinterLoggerInterface *_logger;

public:
    /**
     * @brief OnOffBasicAccessory constructor.
     *
     * @param relayModule The relay module.
     * @param buttonModule The button module.
     */
    OnOffBasicAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, MultiPrinterLoggerInterface *logger = nullptr);

    /**
     * @brief Virtual destructor for OnOffBasicAccessory.
     *
     * @note This destructor is responsible for stopping listening to the button module.
     */
    ~OnOffBasicAccessory() override;

    /**
     * @brief Set the status of the on/off basic module.
     *
     * @param status The new status of the on/off basic module (true for on, false for off).
     * @param notfy Whether to notify the app of the status change.
     *
     * @note This method does not call the notify callback function; you should handle it separately.
     */
    void setStatus(bool status, bool notfy) override;

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
     * @param callbackParameter The void pointer parameter for the callback function.
     */
    void setNotifyCallback(void (*callback)(void *), void *callbackParameter) override;
};

#endif // ON_OFF_BASIC_MODULE_HPP
