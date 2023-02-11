#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <iostream>

using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Return;
using BackendId = std::string;

// Interface to test
class ISpeedSensor
{
  public:
    virtual uint32_t getSpeed() const = 0;
    virtual bool turnOn() = 0;
    virtual bool turnOff() = 0;
};

// Mock class, replace the concrete implementation
class MockSpeed : public ISpeedSensor
{
  public:
    MOCK_METHOD(uint32_t, getSpeed, (), (const override));
    MOCK_METHOD(bool, turnOn, (), (override));
    MOCK_METHOD(bool, turnOff, (), (override));
};

class Car
{
  public:
    // Function to test, if spee
    bool SendSpeedingTicket(ISpeedSensor& arg)
    {
      bool lRetStatus = false;
      constexpr uint32_t MAX_ALLOWED_SPEED = 130;

      if(arg.turnOn())
      {
        uint32_t lSpeed = arg.getSpeed();
        if(lSpeed > MAX_ALLOWED_SPEED)
        {
          lRetStatus = true;
        }
        arg.turnOff();
      }

      return lRetStatus;
    }
};


TEST(CarTest, testingTheSpeedSensor_NormalSpeed)
{
  MockSpeed mockSpeedSensor{};
  EXPECT_CALL(mockSpeedSensor, turnOn).Times(Exactly(1)).WillOnce(Return(true));  // Method tunrOn is called exactly once and return true
  EXPECT_CALL(mockSpeedSensor, getSpeed).WillOnce(Return(100));                   // Method getSpeed is called and returns 100
  EXPECT_CALL(mockSpeedSensor, turnOff).Times(Exactly(1));                        // Method turnOff is called exactly once
  Car c{};
  EXPECT_EQ(c.SendSpeedingTicket(mockSpeedSensor), false);
}

TEST(CarTest, testingTheSpeedSensor_Overspeeding)
{
  MockSpeed mockSpeedSensor{};
  EXPECT_CALL(mockSpeedSensor, turnOn).Times(Exactly(1)).WillOnce(Return(true));
  EXPECT_CALL(mockSpeedSensor, getSpeed).WillOnce(Return(131));
  EXPECT_CALL(mockSpeedSensor, turnOff).Times(Exactly(1));
  Car c{};
  EXPECT_EQ(c.SendSpeedingTicket(mockSpeedSensor), true);
}

TEST(CarTest, testingTheSpeedSensor_CrazyManDriving)
{
  MockSpeed mockSpeedSensor{};
  EXPECT_CALL(mockSpeedSensor, turnOn).Times(Exactly(1)).WillOnce(Return(true));
  EXPECT_CALL(mockSpeedSensor, getSpeed).WillOnce(Return(287));
  EXPECT_CALL(mockSpeedSensor, turnOff).Times(Exactly(1));
  Car c{};
  EXPECT_EQ(c.SendSpeedingTicket(mockSpeedSensor), true);
}

TEST(CarTest, testingTheSpeedSensor_BrokenSensor)
{
  MockSpeed mockSpeedSensor{};
  EXPECT_CALL(mockSpeedSensor, turnOn).Times(Exactly(1)).WillOnce(Return(false));
  EXPECT_CALL(mockSpeedSensor, getSpeed).Times(0);
  EXPECT_CALL(mockSpeedSensor, turnOff).Times(0);
  Car c{};
  EXPECT_EQ(c.SendSpeedingTicket(mockSpeedSensor), false);
}