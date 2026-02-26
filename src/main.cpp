// #include <Arduino.h>
// #include <MultiPrinterLogger.hpp>
// #include <RelayModule.hpp>
// #include <ButtonModule.hpp>
// #include <BlindAccessory/BlindAccessory.hpp>

// void notifyCallback(void *notifyCallbackParameter)
// {
//     Serial.println("Notify Callback");

//     Serial.printf("Heap: %d\n", ESP.getFreeHeap());
//     Serial.printf("min heap: %d\n", ESP.getMinFreeHeap());
//     Serial.printf("High Water mark %d\n", uxTaskGetStackHighWaterMark(NULL));
// }

// BlindAccessory *blindAccessory;

// void setup()
// {
//     Serial.begin(115200);

//     MultiPrinterLogger *logger = new MultiPrinterLogger();
//     logger->addPrinter(&Serial);
//     logger->setLogLevel(MultiPrinterLoggerInterface::LogLevel::VERBOSE);
//     logger->setColorEnabled(true);

//     RelayModule *motorUp = new RelayModule(2, logger);
//     RelayModule *motorDown = new RelayModule(33, logger);
//     ButtonModule *buttonUp = new ButtonModule(5, logger);
//     ButtonModule *buttonDown = new ButtonModule(27, logger);

//     xTASK_LIST_PRINT();

//     Serial.printf("Heap: %d\n", ESP.getFreeHeap());

//     blindAccessory = new BlindAccessory(motorUp, motorDown, buttonUp, buttonDown, 20, 20, logger);

//     blindAccessory->setNotifyCallback(notifyCallback, blindAccessory);
// }

// void loop()
// {
//     delay(5000);

//     Serial.printf("Heap: %d\n", ESP.getFreeHeap());
//     xTASK_LIST_PRINT();
//     delay(20000);
// }

/**
 * @file example.ino
 * @brief Example of how to use the GateOpenerAccessory  class.
 */

#include <Arduino.h>
#include "GateOpenerAccessory/GateOpenerAccessory.hpp"
#include "ButtonModule.hpp"
#include "RelayModule.hpp"

void createGateOpenerAccessory(uint8_t buttonPin, uint8_t relayPin)
{
    RelayModule *relayModule = new RelayModule(relayPin);
    ButtonModule *buttonModule = new ButtonModule(buttonPin);

    GateOpenerAccessory *gateOpenerAccessory = new GateOpenerAccessory(relayModule, buttonModule);

    gateOpenerAccessory->setNotifyCallback(
        [](void *pParameter)
        {
            RelayModuleInterface *relayModule = (RelayModuleInterface *)pParameter;
            Serial.printf("The relay is %s\n", relayModule->isOn() ? "on" : "off");
        },
        relayModule);
}

void setup()
{
    Serial.begin(115200);

    int buttonPins[] = {14, 27, 26, 25, 33, 32, 35, 34};
    int relayPins[] = {23, 22, 21, 19, 18, 17, 16, 4};

    for (int i = 0; i < 8; i++)
    {
        createGateOpenerAccessory(buttonPins[i], relayPins[i]);
    }
}

void loop()
{
    delay(5000);
}