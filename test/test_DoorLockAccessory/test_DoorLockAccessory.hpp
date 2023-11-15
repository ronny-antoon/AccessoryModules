#ifndef DOORLOCK_ACCESSORY_TEST_HPP
#define DOORLOCK_ACCESSORY_TEST_HPP

#include <Arduino.h>
#include <gtest/gtest.h>

#include <RelayModule.hpp>
#include <ButtonModule.hpp>

#include "DoorLockAccessory/DoorLockAccessory.hpp"

class DoorLockAccessoryTest : public ::testing::Test
{
protected:
    uint32_t initialFreeHeap = 0; // Initial free heap size
    uint8_t relayPin = 14;        // Pin assigned to the relay
    uint8_t buttonPin = 22;       // Pin assigned to the button

    // Components used in the test
    RelayModule *relay;
    ButtonModule *button;
    DoorLockAccessory *doorLockAccessory;

    // Set up function to run before each test case
    void SetUp() override
    {
        delay(10);                                                // Introduce a delay of 10ms to allow ESP32 to complete booting
        initialFreeHeap = ESP.getFreeHeap();                      // Record the initial free heap size
        relay = new RelayModule(relayPin);                        // Create an instance of the RelayModule
        button = new ButtonModule(buttonPin);                     // Create an instance of the ButtonModule
        doorLockAccessory = new DoorLockAccessory(relay, button); // Create an instance of the DoorLockAccessory
    }

    // Tear down function to run after each test case
    void TearDown() override
    {
        delete relay;             // Delete the relay instance
        delete button;            // Delete the button instance
        delete doorLockAccessory; // Delete the DoorLockAccessory instance
        delay(10);                // Introduce a delay of 10ms to allow ESP32 to release resources
        if (ESP.getFreeHeap() != initialFreeHeap)
            FAIL() << "Memory leak of " << initialFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }
};

// Test Notification Callback
TEST_F(DoorLockAccessoryTest, NotificationCallback)
{
    // Mock callback function, that recive a void pointer(should be pointer to char), check if it "A", then change it to "B"
    void (*mockCallback)(void *) = [](void *pParameter)
    {
        char *_pChar = static_cast<char *>(pParameter);
        if (*_pChar == 'A')
            *_pChar = 'B';
    };

    // create a new pointer char variable, and set it to 'A'.
    char *pChar = new char('A');

    // Set the callback function
    doorLockAccessory->setNotifyCallback(mockCallback, pChar);

    // Simulate a single press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);

    // Check if the callback function was called
    EXPECT_EQ(*pChar, 'B');

    // Delete the pointer char variable
    delete pChar;
};

// Test Open Door
TEST_F(DoorLockAccessoryTest, OpenDoor)
{
    // Simulate a single press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    // Check if the door is open
    EXPECT_TRUE(doorLockAccessory->isDoorOpen());
};

// Test Close Door
TEST_F(DoorLockAccessoryTest, CloseDoor)
{
    // Simulate a single press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    // Check if the door is open
    EXPECT_TRUE(doorLockAccessory->isDoorOpen());

    doorLockAccessory->closeDoor();

    // Check if the door is closed
    EXPECT_FALSE(doorLockAccessory->isDoorOpen());
};

// Test Open Door Timeout
TEST_F(DoorLockAccessoryTest, OpenDoorTimeout)
{
    // Simulate a single press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    // Check if the door is open
    EXPECT_TRUE(doorLockAccessory->isDoorOpen());

    // wait for the door to close
    delay(6000);

    // Check if the door is closed
    EXPECT_FALSE(doorLockAccessory->isDoorOpen());

    // Simulate a single press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    // Check if the door is open
    EXPECT_TRUE(doorLockAccessory->isDoorOpen());

    // wait for the door to close
    delay(6000);

    // Check if the door is closed
    EXPECT_FALSE(doorLockAccessory->isDoorOpen());
};

//  Test Set Door Lock State
TEST_F(DoorLockAccessoryTest, SetDoorLockState)
{
    // Simulate a single press
    pinMode(buttonPin, OUTPUT);
    digitalWrite(buttonPin, HIGH);
    delay(100);
    digitalWrite(buttonPin, LOW);
    delay(100);

    // Check if the door is open
    EXPECT_TRUE(doorLockAccessory->isDoorOpen());

    doorLockAccessory->setLockState(false);

    // Check if the door is closed
    EXPECT_FALSE(doorLockAccessory->isDoorOpen());

    doorLockAccessory->setLockState(true);

    // Check if the door is open
    EXPECT_TRUE(doorLockAccessory->isDoorOpen());
};

#endif // DOORLOCK_ACCESSORY_TEST_HPP