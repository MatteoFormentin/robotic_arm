#include "conf.h"
#include <Servo.h>

Servo axis0_servo;
Servo axis1_servo; 
Servo axis2_servo; 

int axis0_angle, axis1_angle, axis2_angle;

void beginArms()
{
    axis0_servo.attach(AX0_ARM_PIN);
    axis1_servo.attach(AX1_ARM_PIN);
    axis2_servo.attach(AX2_ARM_PIN);

    axis0_servo.write(AX0_ARM_ZERO);
    axis1_servo.write(AX1_ARM_ZERO);
    axis2_servo.write(90 - AX2_ARM_ZERO);

    axis0_angle = AX0_ARM_ZERO;
    axis1_angle = AX1_ARM_ZERO;
    axis2_angle = AX2_ARM_ZERO;
}

void moveAxis0Arm(int angle)
{
    if (angle < AX0_ARM_MIN)
    {
        angle = AX0_ARM_MIN;
    }
    if (angle > AX0_ARM_MAX)
    {
        angle = AX0_ARM_MAX;
    }

    axis0_servo.write(angle);
    axis0_angle = angle;
}

void moveAxis1Arm(int angle)
{
    if (angle < AX1_ARM_MIN)
    {
        angle = AX1_ARM_MIN;
    }
    if (angle > AX1_ARM_MAX)
    {
        angle = AX1_ARM_MAX;
    }

    axis1_servo.write(angle);
    axis1_angle = angle;
}

void moveAxis2Arm(int angle)
{
    if (angle < AX2_ARM_MIN)
    {
        angle = AX2_ARM_MIN;
    }
    if (angle > AX2_ARM_MAX)
    {
        angle = AX2_ARM_MAX;
    }

    // Axis 2 is vincolated to have is angle less (+ offset) than Axis 1
    axis2_servo.write(90 - angle);
    axis2_angle = angle;
}

int getAxis0Angle()
{
    return axis0_angle;
}

int getAxis1Angle()
{
    return axis1_angle;
}

int getAxis2Angle()
{
    return axis2_angle;
}