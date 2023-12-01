#include <Arduino.h>
#include <gtest/gtest.h>

#include "IncludeAll_test.hpp"

void setup()
{
    Serial.begin(115200);
    delay(1000);
    xTASK_LIST_PRINT();
    delay(1000);

    ::testing::InitGoogleTest();
}

void loop()
{
    if (RUN_ALL_TESTS())
        ;

    delay(1000);
    Serial.println("-----------------------------------Finished all tests!-----------------------------------");

    delay(10000);
}
