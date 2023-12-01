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
    uint8_t buttonPin = 14;       // Pin assigned to the button
    uint8_t relayPin = 27;        // Pin assigned to the relay

    // Components used in the test
    ButtonModule *button;
    RelayModule *relay;
    BoilerAccessory *boilerAccessory;
    int timeToRun = 10; // Time in minutes to run the boiler

    // Set up function to run before each test case
    void SetUp() override
    {
        delay(10);                                                                // Introduce a delay of 10ms to allow ESP32 to complete booting
        initialFreeHeap = ESP.getFreeHeap();                                      // Record the initial free heap size
        button = new ButtonModule(buttonPin);                                     // Create an instance of the ButtonModule
        relay = new RelayModule(relayPin);                                        // Create an instance of the RelayModule
        boilerAccessory = new BoilerAccessory(relay, button, timeToRun, nullptr); // Create an instance of the BoilerAccessory
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete button; // Delete the button instance
        delete relay;
        delete boilerAccessory; // Delete the BoilerAccessory instance
        delay(10);              // Introduce a delay of 10ms to allow ESP32 to release resources
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test case for checking the initial position
TEST_F(BoilerAccessoryTest, InitialStateIsOff)
{
    // Ensure that the boiler is initially turned off
    EXPECT_FALSE(boilerAccessory->isOn());
}

// Test case for turning on the boiler
TEST_F(BoilerAccessoryTest, TurnOn)
{
    // Perform the action to turn on the boiler
    boilerAccessory->turnOn();

    // Verify that the boiler is now turned on
    EXPECT_TRUE(boilerAccessory->isOn());
}

// Test case for turning off the boiler
TEST_F(BoilerAccessoryTest, TurnOff)
{
    // Turn on the boiler before turning it off
    boilerAccessory->turnOn();

    // Perform the action to turn off the boiler
    boilerAccessory->turnOff();

    // Verify that the boiler is now turned off
    EXPECT_FALSE(boilerAccessory->isOn());
}

// Test case for setting the boiler state
TEST_F(BoilerAccessoryTest, SetBoilerState)
{
    // Set the boiler state to ON
    boilerAccessory->setBoilerState(true);

    // Verify that the boiler is now turned on
    EXPECT_TRUE(boilerAccessory->isOn());

    // Set the boiler state to OFF
    boilerAccessory->setBoilerState(false);

    // Verify that the boiler is now turned off
    EXPECT_FALSE(boilerAccessory->isOn());
}

// Test case for checking the remaining time when the boiler is running
TEST_F(BoilerAccessoryTest, RemainingTime)
{
    // Turn on the boiler
    boilerAccessory->turnOn();

    // Delay for 1 second and check the remaining time
    delay(1000);
    EXPECT_EQ(boilerAccessory->getRemainingTime(), (timeToRun * 60) - 1);

    // Delay for another 1 second and check the remaining time
    delay(1000);
    EXPECT_EQ(boilerAccessory->getRemainingTime(), (timeToRun * 60) - 2);

    // Turn off the boiler and check that the remaining time is 0
    boilerAccessory->turnOff();
    EXPECT_EQ(boilerAccessory->getRemainingTime(), 0);
}

// Test case for simulating a button press to control the boiler
TEST_F(BoilerAccessoryTest, ButtonPress)
{
    // Simulate a button press to turn on the boiler
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    // Verify that the boiler is turned on
    EXPECT_TRUE(boilerAccessory->isOn());

    // Simulate another button press to turn off the boiler
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    // Verify that the boiler is turned off
    EXPECT_FALSE(boilerAccessory->isOn());
}

// // test max alloc free heap
// TEST_F(BoilerAccessoryTest, MaxAllocFreeHeap)
// {
//     void (*mockCallback)(void *) = [](void *pParameter) {
//     };
//     boilerAccessory->setNotifyCallback(mockCallback, boilerAccessory);
//     boilerAccessory->isOn();
//     boilerAccessory->getRemainingTime();

//     // simulate a button press
//     pinMode(buttonPin, OUTPUT);
//     digitalWrite(buttonPin, HIGH);
//     delay(100);
//     digitalWrite(buttonPin, LOW);
//     delay(100);

//     int maxAllocFreeHeap = ESP.getMaxAllocHeap();
//     for (int i = 0; i < 20; i++)
//     {
//         boilerAccessory->turnOn();
//         boilerAccessory->isOn();
//         boilerAccessory->getRemainingTime();
//         boilerAccessory->turnOff();
//         boilerAccessory->isOn();
//         boilerAccessory->getRemainingTime();
//         boilerAccessory->turnOn();
//         boilerAccessory->setBoilerState(true);
//         boilerAccessory->setBoilerState(false);

//         // simulate a button press
//         pinMode(buttonPin, OUTPUT);
//         digitalWrite(buttonPin, HIGH);
//         delay(100);
//         digitalWrite(buttonPin, LOW);
//         delay(100);
//     }
//     EXPECT_EQ(ESP.getMaxAllocHeap(), maxAllocFreeHeap);
// };

#endif // BOILER_ACCESSORY_TEST_HPP
