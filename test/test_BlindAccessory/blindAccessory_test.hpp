#ifndef BLINDACCESSORY_TEST_HPP
#define BLINDACCESSORY_TEST_HPP

#include <Arduino.h>
#include <gtest/gtest.h>

#include <RelayModule.hpp>
#include <ButtonModule.hpp>

#include "BlindAccessory/BlindAccessory.hpp"

class BlindAccessoryTest : public ::testing::Test
{
protected:
    uint32_t startFreeHeap = 0;
    uint8_t buttonUpPin = 14;
    uint8_t buttonDownPin = 27;
    uint8_t motorUpPin = 23;
    uint8_t motorDownPin = 22;

    void SetUp() override
    {
        startFreeHeap = ESP.getFreeHeap();
        buttonUp = new ButtonModule(buttonUpPin);
        buttonDown = new ButtonModule(buttonDownPin);
        motorUp = new RelayModule(motorUpPin);
        motorDown = new RelayModule(motorDownPin);
        blindAccessory = new BlindAccessory(motorUp, motorDown, buttonUp, buttonDown, timeToOpen, timeToClose, nullptr);
    }

    void TearDown() override
    {
        delete buttonUp;
        delete buttonDown;
        delete motorUp;
        delete motorDown;
        delete blindAccessory;
        if (ESP.getFreeHeap() != startFreeHeap)
            FAIL() << "Memory leak of " << startFreeHeap - ESP.getFreeHeap() << " bytes"; // Fail the test if there is a memory leak
    }

    ButtonModule *buttonUp;
    ButtonModule *buttonDown;
    RelayModule *motorUp;
    RelayModule *motorDown;
    BlindAccessory *blindAccessory;
    int timeToOpen = 10;
    int timeToClose = 10;
};

TEST_F(BlindAccessoryTest, initialPositionIsZero)
{
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 0);
}

TEST_F(BlindAccessoryTest, currentPositionAfterHalfUp)
{
    blindAccessory->moveBlindTo(50);
    delay(((timeToOpen / 2) + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 50);
}

TEST_F(BlindAccessoryTest, currentPositionAfterHalfDown)
{
    blindAccessory->moveBlindTo(50);
    delay(((timeToOpen / 2) + 1) * 1000);
    blindAccessory->moveBlindTo(0);
    delay(((timeToOpen / 2) + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 0);
}

TEST_F(BlindAccessoryTest, currentPositionAfterFullUp)
{
    blindAccessory->moveBlindTo(100);
    delay((timeToOpen + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 100);
}

TEST_F(BlindAccessoryTest, moveTo50ThenFullUp)
{
    blindAccessory->moveBlindTo(50);
    delay(((timeToOpen / 2) + 1) * 1000);
    blindAccessory->moveBlindTo(100);
    delay((timeToOpen + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 100);
}

TEST_F(BlindAccessoryTest, moveTo50BeforEndMoveTo0)
{
    blindAccessory->moveBlindTo(50);
    delay(((timeToOpen / 2) - 1) * 1000);
    blindAccessory->moveBlindTo(0);
    delay((timeToOpen + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 0);
}

TEST_F(BlindAccessoryTest, pressUpButton)
{
    pinMode(buttonUpPin, OUTPUT);
    digitalWrite(buttonUpPin, HIGH);
    delay(150);
    digitalWrite(buttonUpPin, LOW);
    delay(150);
    EXPECT_EQ(blindAccessory->getTargetPosition(), 100);

    delay(((timeToOpen) + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 100);
}
TEST_F(BlindAccessoryTest, pressDownButton)
{
    pinMode(buttonDownPin, OUTPUT);
    digitalWrite(buttonDownPin, HIGH);
    delay(150);
    digitalWrite(buttonDownPin, LOW);
    delay(150);
    EXPECT_EQ(blindAccessory->getTargetPosition(), 0);

    delay(((timeToOpen) + 1) * 1000);
    EXPECT_EQ(blindAccessory->getCurrentPosition(), 0);
}

TEST_F(BlindAccessoryTest, startMoveThenPressAnyButoonToStop)
{
    blindAccessory->moveBlindTo(50);
    delay(150);
    EXPECT_EQ(blindAccessory->getTargetPosition(), 50);

    delay(1000);
    pinMode(buttonUpPin, OUTPUT);
    digitalWrite(buttonUpPin, HIGH);
    delay(150);
    digitalWrite(buttonUpPin, LOW);
    delay(150);

    EXPECT_EQ(blindAccessory->getCurrentPosition(), blindAccessory->getTargetPosition());
}

#endif // BLINDACCESSORY_TEST_HPP