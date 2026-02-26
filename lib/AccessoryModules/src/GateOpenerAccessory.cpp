#include "GateOpenerAccessory/GateOpenerAccessory.hpp"

/**
 * @brief Task to activate the dry contact for opening/closing the gate.
 */
void GateOpenerAccessory::activateDryContactTask()
{
    Log_Verbose(_logger, "Activating dry contact for opening/closing the gate.");
    if (_relayModule)
    {
        vTaskDelay(pdMS_TO_TICKS(_timeToActivate));
        _relayModule->setState(false);
    }
}

/**
 * @brief GateOpenerAccessory constructor.
 *
 * @param relayModule The relay module associated with the gate opener accessory.
 * @param buttonModule The button module associated with the gate opener accessory.
 * @param timeToActivate Time to hold the dry contact for opening/closing the gate
 * in milliseconds. Range: 1-65535.
 */
GateOpenerAccessory::GateOpenerAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint16_t timeToActivate, MultiPrinterLoggerInterface *logger, uint16_t usStackDepth)
    : _relayModule(relayModule),
      _buttonModule(buttonModule),
      _notifyAPP(nullptr),
      _callbackParameter(nullptr),
      _timeToActivate(timeToActivate),
      _activateDryContactTask_handle(nullptr),
      _logger(logger)
{
    Log_Debug(_logger, "Gate Opener Accessory Created with timeToActivate: %d milliseconds.", _timeToActivate);
    // Check if a button module is provided.
    if (_buttonModule)
    {
        // Set up a listener for single press events.
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                GateOpenerAccessory *thisPointer = static_cast<GateOpenerAccessory *>(pParameter);
                Log_Verbose(thisPointer->_logger, "Gate opener button pressed, activating dry contact.");
                thisPointer->activateDryContact(true);
                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                {
                    Log_Verbose(thisPointer->_logger, "Notifying app about gate state change.");
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
                }
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening(usStackDepth, "buttonGateOpener");
    }
}

/**
 * @brief Virtual destructor for GateOpenerAccessory.
 */
GateOpenerAccessory::~GateOpenerAccessory()
{
    Log_Debug(_logger, "Gate Opener Accessory Deleted.");

    if (_activateDryContactTask_handle != nullptr)
    {
        Log_Verbose(_logger, "Deleting activateDryContactTask handle.");
        checkWaterMArkAndPrint(_logger, _activateDryContactTask_handle);
        xTASK_DELETE_TRACKED(&_activateDryContactTask_handle);
        _activateDryContactTask_handle = nullptr;
    }

    if (_buttonModule)
    {
        Log_Verbose(_logger, "Stopping button module listener.");
        _buttonModule->stopListening();
    }

    if (_relayModule)
    {
        Log_Verbose(_logger, "Turning off relay module.");
        _relayModule->setState(false);
    }
}

/**
 * @brief Sets the callback function for notifying events.
 *
 * @param callback The callback function, taking a void pointer parameter.
 * @param callbackParameter The void pointer parameter for the callback function.
 */
void GateOpenerAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    Log_Verbose(_logger, "Setting notify callback.");
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}

/**
 * @brief Activate the dry contact to open/close the gate.
 *
 * @param notfy True to notify the app, false otherwise.
 */
void GateOpenerAccessory::activateDryContact(bool notfy)
{
    Log_Verbose(_logger, "Activating dry contact to open/close the gate.");
    if (_relayModule)
        _relayModule->setState(true);

    if (_activateDryContactTask_handle == nullptr)
    {
        xTaskCreate(
            [](void *pParameter)
            {
                GateOpenerAccessory *thisPointer = static_cast<GateOpenerAccessory *>(pParameter);
                thisPointer->activateDryContactTask();
                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                {
                    Log_Verbose(thisPointer->_logger, "Notifying app about gate state change after stopping activate dry contact.");
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
                }
                Log_Verbose(thisPointer->_logger, "Deleting activateDryContactTask handle.");
                checkWaterMArkAndPrint(thisPointer->_logger, thisPointer->_activateDryContactTask_handle);
                thisPointer->_activateDryContactTask_handle = nullptr;
                xTASK_DELETE_TRACKED(&(thisPointer->_activateDryContactTask_handle));
            },
            "activateDryContactTask",
            3000,
            this,
            1,
            &_activateDryContactTask_handle);
    }
}