// #ifdef GLOBAL_TEST_ENVIRONMENT

// #include <Arduino.h>
// #include <gtest/gtest.h>

// void setup()
// {
//     Serial.begin(115200);
//     ::testing::InitGoogleTest();
// }

// void loop()
// {
//     if (RUN_ALL_TESTS())
//         ;

//     delay(1000);

//     Serial.println("-----------------------------------Finished all tests!-----------------------------------");

//     delay(10000);
// }

// #endif // GLOBAL_TEST_ENVIRONMENT

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