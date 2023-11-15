#ifdef GLOBAL_TEST_ENVIRONMENT

#include <Arduino.h>
#include <gtest/gtest.h>

// #include "test_BlindAccessory/startMoveUp_test.hpp"

void setup()
{
    Serial.begin(115200);
    ::testing::InitGoogleTest();
}

void loop()
{
    if (RUN_ALL_TESTS())
        ;

    delay(1000);

    Serial.println("-----------------------------------Finished all tests!-----------------------------------");

    delay(100000);
}

#endif // GLOBAL_TEST_ENVIRONMENT