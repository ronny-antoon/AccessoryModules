#include "BoilerAccessory/BoilerAccessory.hpp"

/**
 * @brief Task to turn on the boiler for a specified duration.
 */
void BoilerAccessory::turnOnTask()
{
    _remainingTime = _timeToRun * 60; // Convert minutes to seconds
    Log_Verbose(_logger, "Boiler turned on for %d minutes.", _timeToRun);

    for (uint16_t i = 0; i < _timeToRun * 60; i++)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        _remainingTime--;
        if (_notifyAPP && _callbackParameter)
            _notifyAPP(_callbackParameter);
    }

    _remainingTime = 0;
    if (_relayModule)
    {
        _relayModule->setState(false);
        Log_Verbose(_logger, "Boiler turned off.");
    }

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

    // Check if a button module is provided.
    if (_buttonModule)
    {
        // Set up a listener for single press events.
        _buttonModule->onSinglePress(
            [](void *pParameter)
            {
                BoilerAccessory *thisPointer = static_cast<BoilerAccessory *>(pParameter);

                Log_Verbose(thisPointer->_logger, "Button pressed. Toggling boiler state.");
                thisPointer->setBoilerState(!thisPointer->isOn());

                if (thisPointer->_notifyAPP && thisPointer->_callbackParameter)
                    thisPointer->_notifyAPP(thisPointer->_callbackParameter);
            },
            this);

        // Start listening for button events.
        _buttonModule->startListening();
    }

    Log_Debug(_logger, "BoilerAccessory created with timeToRun: %d.", _timeToRun);
}

/**
 * @brief Virtual destructor for BoilerAccessory.
 */
BoilerAccessory::~BoilerAccessory()
{

    if (_turnOnTask_handle != nullptr)
    {
        Log_Verbose(_logger, "Deleting turnOnTask handle.");
        vTaskDelete(_turnOnTask_handle);
        _turnOnTask_handle = nullptr;
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

    Log_Debug(_logger, "BoilerAccessory destructor called.");
}

/**
 * @brief Turn on the boiler.
 */
void BoilerAccessory::turnOn()
{

    if (_relayModule)
    {
        if (_relayModule->isOn())
        {
            Log_Warning(_logger, "Boiler is already on. Ignoring turnOn request.");
            return;
        }

        if (_turnOnTask_handle != nullptr)
        {
            Log_Verbose(_logger, "Deleting existing turnOnTask handle.");
            vTaskDelete(_turnOnTask_handle);
            _turnOnTask_handle = nullptr;
        }

        _relayModule->setState(true);
        Log_Verbose(_logger, "Boiler turned on.");

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

    if (_relayModule)
    {
        if (_turnOnTask_handle != nullptr)
        {
            Log_Verbose(_logger, "Deleting existing turnOnTask handle.");
            vTaskDelete(_turnOnTask_handle);
            _turnOnTask_handle = nullptr;
        }

        _remainingTime = 0;

        if (_relayModule->isOn())
        {
            _relayModule->setState(false);
            Log_Verbose(_logger, "Boiler turned off.");
        }
        else
        {
            Log_Warning(_logger, "Boiler is already off. Ignoring turnOff request.");
        }
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

/**
 * @brief Set the duration time for the boiler to be on.
 *
 * @param duration The remaining time in minutes.
 */
void BoilerAccessory::setDuration(uint8_t duration)
{
    if (duration > 0 && duration <= 255)
    {
        _timeToRun = duration;
        _remainingTime = _timeToRun * 60; // Convert minutes to seconds
    }
    else
        Log_Warning(_logger, "Invalid duration value. Ignoring setDuration request.");
}

/**
 * @brief Get the duration time for the boiler to be on.
 *
 * @return The remaining time in minutes.
 */
uint8_t BoilerAccessory::getDuration() const
{
    return _timeToRun;
}