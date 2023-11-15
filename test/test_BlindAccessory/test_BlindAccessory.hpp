#ifndef BLIND_ACCESSORY_TEST_HPP
#define BLIND_ACCESSORY_TEST_HPP

#include <Arduino.h>
#include <gtest/gtest.h>

#include <RelayModule.hpp>
#include <ButtonModule.hpp>

#include "BlindAccessory/BlindAccessory.hpp"

// Test fixture for BlindAccessory class
class BlindAccessoryTest : public ::testing::Test
{
protected:
    uint32_t initialFreeHeap = 0; // Initial free heap size
    uint8_t upButtonPin = 14;     // Pin for the up button
    uint8_t downButtonPin = 27;   // Pin for the down button
    uint8_t upMotorPin = 23;      // Pin for the up motor
    uint8_t downMotorPin = 22;    // Pin for the down motor

    // Components used in the test
    ButtonModule *upButton;
    ButtonModule *downButton;
    RelayModule *upMotor;
    RelayModule *downMotor;
    BlindAccessory *blindAccessory;
    int timeToOpen = 10;  // Time in seconds to fully open the blind
    int timeToClose = 10; // Time in seconds to fully close the blind

    // Set up function to run before each test case
    void SetUp() override
    {
        initialFreeHeap = ESP.getFreeHeap();                                                                             // Record initial free heap size
        upButton = new ButtonModule(upButtonPin);                                                                        // Create up button instance
        downButton = new ButtonModule(downButtonPin);                                                                    // Create down button instance
        upMotor = new RelayModule(upMotorPin);                                                                           // Create up motor instance
        downMotor = new RelayModule(downMotorPin);                                                                       // Create down motor instance
        blindAccessory = new BlindAccessory(upMotor, downMotor, upButton, downButton, timeToOpen, timeToClose, nullptr); // Create BlindAccessory instance
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete upButton;       // Delete up button instance
        delete downButton;     // Delete down button instance
        delete upMotor;        // Delete up motor instance
        delete downMotor;      // Delete down motor instance
        delete blindAccessory; // Delete BlindAccessory instance
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test case for checking initial position
TEST_F(BlindAccessoryTest, InitialPositionIsZero)
{
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 0);
}

// Test case for checking current position after moving halfway up
TEST_F(BlindAccessoryTest, CurrentPositionAfterHalfUp)
{
    blindAccessory->moveBlindTo(50);
    delay(((timeToOpen / 2) + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 50);
}

// Test case for checking current position after moving halfway down
TEST_F(BlindAccessoryTest, CurrentPositionAfterHalfDown)
{
    blindAccessory->moveBlindTo(50);
    delay(((timeToOpen / 2) + 1) * 1000);
    blindAccessory->moveBlindTo(0);
    delay(((timeToOpen / 2) + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 0);
}

// Test case for checking current position after moving fully up
TEST_F(BlindAccessoryTest, CurrentPositionAfterFullUp)
{
    blindAccessory->moveBlindTo(100);
    delay((timeToOpen + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 100);
}

// Test case for moving to 50 and then fully up
TEST_F(BlindAccessoryTest, MoveTo50ThenFullUp)
{
    blindAccessory->moveBlindTo(50);
    delay(((timeToOpen / 2) + 1) * 1000);
    blindAccessory->moveBlindTo(100);
    delay((timeToOpen + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 100);
}

// Test case for moving to 50 and before the end moving to 0
TEST_F(BlindAccessoryTest, MoveTo50BeforeEndMoveTo0)
{
    blindAccessory->moveBlindTo(50);
    delay(((timeToOpen / 2) - 1) * 1000);
    blindAccessory->moveBlindTo(0);
    delay((timeToOpen + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 0);
}

// Test case for pressing the up button
TEST_F(BlindAccessoryTest, PressUpButton)
{
    pinMode(upButtonPin, OUTPUT);
    digitalWrite(upButtonPin, HIGH);
    delay(150);
    digitalWrite(upButtonPin, LOW);
    delay(150);
    EXPECT_EQ(blindAccessory->getTargetPosition(), 100);

    delay(((timeToOpen) + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 100);
}

// Test case for pressing the down button
TEST_F(BlindAccessoryTest, PressDownButton)
{
    pinMode(downButtonPin, OUTPUT);
    digitalWrite(downButtonPin, HIGH);
    delay(150);
    digitalWrite(downButtonPin, LOW);
    delay(150);
    EXPECT_EQ(blindAccessory->getTargetPosition(), 0);

    delay(((timeToOpen) + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 0);
}

// Test case for starting to move and then pressing any button to stop
TEST_F(BlindAccessoryTest, StartMoveThenPressAnyButtonToStop)
{
    blindAccessory->moveBlindTo(50);
    delay(150);
    EXPECT_EQ(blindAccessory->getTargetPosition(), 50);

    delay(1000);
    pinMode(upButtonPin, OUTPUT);
    digitalWrite(upButtonPin, HIGH);
    delay(150);
    digitalWrite(upButtonPin, LOW);
    delay(150);

    EXPECT_EQ(blindAccessory->getCurrentPosition(), blindAccessory->getTargetPosition());
}

#endif // BLIND_ACCESSORY_TEST_HPP
