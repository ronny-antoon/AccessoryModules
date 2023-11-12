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

#include "ButtonModule.hpp"
#include "ButtonAccessory.hpp"

void setup()
{
    Serial.begin(115200);

    ButtonModule *buttonModule = new ButtonModule(5);
    ButtonAccessory *buttonAccessory = new ButtonAccessory(buttonModule);

    buttonAccessory->setNotifyCallback(
        [](void *pParameter)
        {
            ButtonAccessory *thisPointer = (ButtonAccessory *)pParameter;
            Serial.println(thisPointer->getLastPressEvent());
        },
        buttonAccessory);
}

void loop()
{
    delay(1000);
}