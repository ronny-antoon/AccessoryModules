#include <Arduino.h>
#include <gtest/gtest.h>

void setup()
{
    Serial.begin(115200);
    ::testing::InitGoogleTest();
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
