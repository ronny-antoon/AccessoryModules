#include "BoilerAccessory/BoilerAccessory.hpp"

/**
 * @brief Task to turn on the boiler for a specified duration.
 */
void BoilerAccessory::turnOnTask()
{
    _remainingTime = _timeToRun * 60; // Convert minutes to seconds
    for (uint16_t i = 0; i < _timeToRun * 60; i++)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        _remainingTime--;
        if (_notifyAPP && _callbackParameter)
            _notifyAPP(_callbackParameter);
    }
    _remainingTime = 0;
    if (_relayModule)
        _relayModule->turnOff();
    if (_notifyAPP && _callbackParameter)
        _notifyAPP(_callbackParameter);
}

/**
 * @brief BoilerAccessory constructor.
 *
 * @param relayModule The relay module associated with the boiler accessory.
 * @param buttonModule The button module associated with the boiler accessory.
 * @param timeToRun The time to turn on the boiler, in minutes. Range: 1-255. Default: 5 minutes.
 */
BoilerAccessory::BoilerAccessory(RelayModuleInterface *relayModule, ButtonModuleInterface *buttonModule, uint8_t timeToRun, MultiPrinterLoggerInterface *logger)
    : _relayModule(relayModule),
      _buttonModule(buttonModule),
      _notifyAPP(nullptr),
      _callbackParameter(nullptr),
      _remainingTime(0),
      _timeToRun(timeToRun),
      _turnOnTask_handle(nullptr),
      _logger(logger)
{
    Log_Debug(_logger, "Boiler Accessory Created.");

    // Check if a button module is provided.
    if (_buttonModule)
    {
        // Set up a listener for single press events.
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                BoilerAccessory *thisPointer = static_cast<BoilerAccessory *>(pParameter);
                thisPointer->setBoilerState(!thisPointer->isOn());

                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening();
    }
}

/**
 * @brief Virtual destructor for BoilerAccessory.
 */
BoilerAccessory::~BoilerAccessory()
{
    Log_Debug(_logger, "Boiler Accessory Deleted.");

    if (_turnOnTask_handle != nullptr)
    {
        vTaskDelete(_turnOnTask_handle);
        _turnOnTask_handle = nullptr;
    }

    if (_buttonModule)
        _buttonModule->stopListening();

    if (_relayModule)
        _relayModule->turnOff();
}

/**
 * @brief Turn on the boiler.
 */
void BoilerAccessory::turnOn()
{
    Log_Debug(_logger, "Boiler Accessory Turned On.");

    if (_relayModule)
    {
        if (_relayModule->isOn())
            return;
        if (_turnOnTask_handle != nullptr)
        {
            vTaskDelete(_turnOnTask_handle);
            _turnOnTask_handle = nullptr;
        }
        _relayModule->turnOn();
        xTaskCreate(
            [](void *pParameter)
            {
                BoilerAccessory *thisPointer = static_cast<BoilerAccessory *>(pParameter);
                thisPointer->turnOnTask();
                thisPointer->_turnOnTask_handle = nullptr;
                vTaskDelete(nullptr);
            },
            "turnOnTask",
            10000,
            this,
            1,
            &_turnOnTask_handle);
    }
}

/**
 * @brief Turn off the boiler.
 */
void BoilerAccessory::turnOff()
{
    Log_Debug(_logger, "Boiler Accessory Turned Off.");

    if (_relayModule)
    {
        if (_turnOnTask_handle != nullptr)
        {
            vTaskDelete(_turnOnTask_handle);
            _turnOnTask_handle = nullptr;
        }
        _remainingTime = 0;
        if (_relayModule->isOn())
            _relayModule->turnOff();
    }
}

/**
 * @brief Check if the boiler is on.
 *
 * @return True if the boiler is on, false otherwise.
 */
bool BoilerAccessory::isOn() const
{
    if (_relayModule)
        return _relayModule->isOn();
    else
        return false;
}

/**
 * @brief Set the boiler state.
 *
 * @param toOn True to turn the boiler on, false to turn it off.
 */
void BoilerAccessory::setBoilerState(bool toOn)
{
    if (toOn)
        turnOn();
    else
        turnOff();
}

/**
 * @brief Get the remaining time for the boiler to be on.
 *
 * @return Remaining time in seconds.
 */
uint16_t BoilerAccessory::getRemainingTime() const
{
    return _remainingTime;
}

/**
 * @brief Set the callback function and its parameter for boiler events.
 *
 * @param notifyAPP The callback function to be called when a boiler event occurs.
 * @param pParameter The parameter to be passed to the callback function.
 */
void BoilerAccessory::setNotifyCallback(void (*notifyAPP)(void *), void *pParameter)
{
    _notifyAPP = notifyAPP;
    _callbackParameter = pParameter;
}
