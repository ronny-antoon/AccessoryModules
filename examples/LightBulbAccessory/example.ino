/**
 * @file example.ino
 * @brief Example of how to use the LightBulbAccessory class.
 */

#include <Arduino.h>
#include "LightBulbAccessory.hpp"
#include "ButtonModule.hpp"
#include "RelayModule.hpp"

void createLightAccessory(uint8_t buttonPin, uint8_t relayPin)
{
    RelayModule *relayModule = new RelayModule(relayPin);
    ButtonModule *buttonModule = new ButtonModule(buttonPin);

    LightBulbAccessory *lightBulbAccessory = new LightBulbAccessory(relayModule, buttonModule);

    lightBulbAccessory->setNotifyCallback(
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
        createLightAccessory(buttonPins[i], relayPins[i]);
    }
}

void loop()
{
    delay(5000);
}