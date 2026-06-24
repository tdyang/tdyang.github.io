#pragma once

#include <Arduino.h>
#include <Romi32U4Motors.h>

class Chassis
{
protected:
    // Kinematic parameters -- TODO: These are grossly wrong!!!
    float wheel_track = 14.5; //cm
    float wheel_diam = 7; //cm
    float interval_time = 0.02; //seconds
    float ticks_per_rotation = 1440; // from the datasheet
    float cmPerEncoderTick = 3.1416 * wheel_diam / ticks_per_rotation;
    float robotRadius = wheel_track / 2.0;
    double robotVerticalAngle = 0;
    float ODRtime = 1.0 / 416.0;
    float filterAngle = 0;
    float prevBias = 0;
    float gyroBias = 0;
    float predictedAngle = 0;

public:
    uint8_t readyToPID = 0;
    float currentAngle = 0;

    Chassis(void);

    void init(void);
    bool loop(void);
    void update(void);
    bool checkForNewIMUData();
    float updatePitch();
    void Anglereset();
    bool checkForNewGyroData();

    void setMotorEfforts(int16_t left, int16_t right) 
        {leftMotor.setMotorEffort(left); rightMotor.setMotorEffort(right);}

    void setMotorTargetSpeeds(float leftTicksPerInterval, float rightTicksPerInterval);
    void setWheelTargetSpeeds(float leftCmPerSec, float rightCmPerSec);

    bool turnRobot();

    float estimatedPitchAngle = 0;
};

extern Chassis chassis;
