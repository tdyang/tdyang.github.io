#include <Arduino.h>
#include <Chassis.h>
#include <Romi32U4Motors.h>
#include <LSM6.h>

// We'll declare motors as global to make the ISRs happier, but we'll put them in Chassis.cpp
// to keep things organized

LeftMotor leftMotor;
RightMotor rightMotor;

LSM6 imu;
float robotSpeed = 0;
float ODRtime = 1.0 / 416.0;
float gyroBias = -0;
int i = 0;
float k = 0.3;
float robotTurnAngle = 0;
int turnAngle = 90;
float predictedTurn = 0;
float estimatedTurn = 0;
float filterTurn = 0;
float errorSum = 0;
float error = 0;


Chassis::Chassis(void) {}

void Chassis::init(void)
{  
    noInterrupts(); //disable interupts while we mess with the Timer4 registers
  
    //sets up timer 4
    TCCR4A = 0x00; //disable some functionality -- no need to worry about this
    TCCR4B = 0x0A; //sets the prescaler -- look in the handout for values
    TCCR4C = 0x04; //toggles pin 6 at the timer frequency
    TCCR4D = 0x00; //normal mode

    /**
     * Here we do a little trick to allow full 10-bit register access. 
     * We have 2 bytes in TC4H that we can use to add capacity to TOP. 
     * In the end, this sets TOP = 2 * 256 + 112 = 624
    */
    TC4H = 2; OCR4C = 112;

    TIMSK4 = 0x04; //enable overflow interrupt

    interrupts(); //re-enable interrupts

    // init the motors
    Romi32U4Motor::init();

    //pinMode(6, OUTPUT); //COMMENT THIS OUT TO SHUT UP THE PIEZO!!!
    pinMode(13, OUTPUT);
    Wire.begin();

    if (!imu.init())
    {
    // Failed to detect the LSM6.
    while(1)
    {
      Serial.println(F("Failed to detect the LSM6. Just smash that reset button."));
      delay(100);
    }
  }
}

bool Chassis::loop(void)
{
    bool retVal = false;
    if(readyToPID)
    {
        if(readyToPID > 1) Serial.println("Missed update in Chassis::loop()");

        update();
        readyToPID = 0;
        retVal = true;
    }

    /*if(checkForNewIMUData()) {
        updatePitch();
    }*/
    //imu.readGyro();
    //Serial.println(imu.g.z);

    return retVal;
}

void Chassis::update(void)
{
    //Serial.print(millis());
    //Serial.print("\t");
    leftMotor.update();
    rightMotor.update();
#ifdef __MOTOR_DEBUG__
    Serial.print('\n');
#endif
}

void Chassis::setMotorTargetSpeeds(float leftTicksPerInterval, float rightTicksPerInterval)
{
    leftMotor.setTargetSpeed(leftTicksPerInterval);
    rightMotor.setTargetSpeed(rightTicksPerInterval);
}

void Chassis::setWheelTargetSpeeds(float leftCmPerSec, float rightCmPerSec) {
    float leftTicksPerInterval = leftCmPerSec / cmPerEncoderTick * interval_time;
    float rightTicksPerInterval = rightCmPerSec / cmPerEncoderTick * interval_time;
    setMotorTargetSpeeds(leftTicksPerInterval, rightTicksPerInterval);
}

bool Chassis::checkForNewIMUData() {
    return (imu.getStatus() & 0x01);
}

bool Chassis::checkForNewGyroData() {
    return (imu.getStatus() & 0x02);
}

float Chassis::updatePitch() {
    float k = 0.3;
    predictedAngle = estimatedPitchAngle + ODRtime * 8.75 / 1000.0 * (imu.g.y - gyroBias);

    digitalWrite(13, HIGH);
    imu.readAcc();
    imu.readGyro();
    digitalWrite(13, LOW);

    robotVerticalAngle = (atan2((imu.a.x-259.8),(imu.a.z-784.6)))*(-360/(2*PI));
    filterAngle = (1 - k) * predictedAngle + k * robotVerticalAngle;
    estimatedPitchAngle = filterAngle;
    gyroBias = prevBias - (0.02/(ODRtime * (8.75/1000.0))) *(robotVerticalAngle - predictedAngle);
    prevBias = gyroBias;
    return filterAngle;
}
/*
 * ISR for timing. On overflow, it takes a 'snapshot' of the encoder counts and raises a flag to let
 * the main program it is time to execute the PID calculations.
 */
ISR(TIMER4_OVF_vect)
{
  //Capture a "snapshot" of the encoder counts for later processing
  leftMotor.calcEncoderDelta();
  rightMotor.calcEncoderDelta();

  chassis.readyToPID++;
}

bool Chassis::turnRobot() {
    //error = 90 - filterTurn;
    //errorSum = errorSum + error;
    //robotSpeed = 0.2*error + 0.0002*errorSum;
    robotSpeed = 8;
    imu.readGyro();
    chassis.setWheelTargetSpeeds(robotSpeed, -robotSpeed);

    Serial.print(filterTurn);
    Serial.print("\t");
    Serial.print(robotTurnAngle);
    Serial.print("\t");
    Serial.print(robotSpeed);
    Serial.print("\t");
    Serial.println(predictedTurn);

    float robotAngularSpeed = (robotSpeed/(2*PI*robotRadius)) * 360.0;
    robotTurnAngle = robotTurnAngle + robotAngularSpeed*ODRtime;
    predictedTurn = estimatedTurn + 0.5*ODRtime * (-8.75 / 1000.0) * (imu.g.z - gyroBias);
    filterTurn = ((1 - k) * predictedTurn + k * robotTurnAngle);
    estimatedTurn = filterTurn;
    robotTurnAngle = filterTurn;
    gyroBias = prevBias - (imu.g.z - robotAngularSpeed);
    prevBias = gyroBias;


    if(filterTurn >= 90) {
        robotSpeed = 0;
        chassis.setMotorEfforts(0,0);
        }
    return (filterTurn > 90);
}

void Chassis::Anglereset() {
    predictedTurn = 0;
    estimatedTurn = 0;
    filterTurn = 0;
    robotTurnAngle = 0;
    gyroBias = 0;
    prevBias = 0;
    //Serial.println(filterTurn);
}
