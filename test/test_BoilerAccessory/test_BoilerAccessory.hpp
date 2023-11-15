#ifndef BOILER_ACCESSORY_TEST_HPP
#define BOILER_ACCESSORY_TEST_HPP

#include <Arduino.h>
#include <gtest/gtest.h>

#include <RelayModule.hpp>
#include <ButtonModule.hpp>

#include "BoilerAccessory/BoilerAccessory.hpp"

// Test fixture for BoilerAccessory class
class BoilerAccessoryTest : public ::testing::Test
{
protected:
    uint32_t initialFreeHeap = 0; // Initial free heap size
    uint8_t buttonPin = 14;       // Pin for the button
    uint8_t relayPin = 27;        // Pin for the relay

    // Components used in the test
    ButtonModule *button;
    RelayModule *relay;
    BoilerAccessory *boilerAccessory;
    int timeToRun = 10; // Time in minutes to run the boiler

    // Set up function to run before each test case
    void SetUp() override
    {
        delay(10);                                                                // Delay for 10ms to allow ESP32 to boot
        initialFreeHeap = ESP.getFreeHeap();                                      // Record initial free heap size
        button = new ButtonModule(buttonPin);                                     // Create button instance
        relay = new RelayModule(relayPin);                                        // Create relay instance
        boilerAccessory = new BoilerAccessory(relay, button, timeToRun, nullptr); // Create BoilerAccessory instance
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete button; // Delete button instance
        delete relay;
        delete boilerAccessory; // Delete BoilerAccessory instance
        delay(10);              // Delay for 10ms to allow ESP32 to delete objects
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test case for checking initial position
TEST_F(BoilerAccessoryTest, InitialPositionIsZero)
{
    EXPECT_FALSE(boilerAccessory->isOn());
}

TEST_F(BoilerAccessoryTest, TurnOn)
{
    boilerAccessory->turnOn();
    EXPECT_TRUE(boilerAccessory->isOn());
}

TEST_F(BoilerAccessoryTest, TurnOff)
{
    boilerAccessory->turnOn();
    boilerAccessory->turnOff();
    EXPECT_FALSE(boilerAccessory->isOn());
}

TEST_F(BoilerAccessoryTest, SetBoilerState)
{
    boilerAccessory->setBoilerState(true);
    EXPECT_TRUE(boilerAccessory->isOn());
    boilerAccessory->setBoilerState(false);
    EXPECT_FALSE(boilerAccessory->isOn());
}

TEST_F(BoilerAccessoryTest, RemainingTime)
{
    boilerAccessory->turnOn();
    delay(1000);
    EXPECT_EQ(boilerAccessory->getRemainingTime(), (timeToRun * 60) - 1);
    delay(1000);
    EXPECT_EQ(boilerAccessory->getRemainingTime(), (timeToRun * 60) - 2);
    boilerAccessory->turnOff();
    EXPECT_EQ(boilerAccessory->getRemainingTime(), 0);
}

TEST_F(BoilerAccessoryTest, ButtonPress)
{
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    EXPECT_TRUE(boilerAccessory->isOn());

    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    EXPECT_FALSE(boilerAccessory->isOn());
}
#endif // BOILER_ACCESSORY_TEST_HPP