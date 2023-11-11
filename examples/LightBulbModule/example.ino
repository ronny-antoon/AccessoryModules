#include <Arduino.h>
#include "LightBulbModule.hpp"
#include "ButtonModule.hpp"
#include "RelayModule.hpp"

void setup()
{
    Serial.begin(115200);

    RelayModule *relayModule = new RelayModule(2);
    ButtonModule *buttonModule = new ButtonModule(5);

    LightBulbModule *lightBulbModule = new LightBulbModule(relayModule, buttonModule);

    lightBulbModule->setNotifyCallback(
        [](void *pParameter)
        {
            RelayModuleInterface *relayModule = (RelayModuleInterface *)pParameter;
            relayModule->isOn();
            Serial.println(relayModule->isOn() ? "The relay is on" : "The relay is off");
        },
        relayModule);
}

void loop()
{
    delay(5000);
}