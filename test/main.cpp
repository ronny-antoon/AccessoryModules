#include <Arduino.h>
#include <gtest/gtest.h>

#include "BlindAccessory/BlindAccessory.hpp"
#include "ButtonModule.hpp"
#include "RelayModule.hpp"

void setup()
{
    Serial.begin(115200);
    ::testing::InitGoogleTest();

    ButtonModule *buttonUp = new ButtonModule(0);
    ButtonModule *buttonDown = new ButtonModule(1);
    RelayModule *motorUp = new RelayModule(2);
    RelayModule *motorDown = new RelayModule(3);

    BlindAccessory *blind = new BlindAccessory(motorUp, motorDown, buttonUp, buttonDown, 10, 10);
}

TEST(tetoooo, test1)
{
    EXPECT_EQ(1, 1);
}

void loop()
{
    if (RUN_ALL_TESTS())
        ;

    delay(1000);

    if (::testing::UnitTest::GetInstance()->failed_test_suite_count() > 0)
        Serial.println("-----------------------------------Some tests failed!-----------------------------------");
    else
        Serial.println("-----------------------------------Finished all tests!-----------------------------------");

    delay(10000);
}
