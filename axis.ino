#include "conf.h"
#include <Servo.h>

Servo axis0_servo;
Servo axis1_servo;
Servo axis2_servo;
Servo claw_servo;

typedef struct coordinates{
    float x;
    float y;
} coordinates;

coordinates claw_pose;

int axis0_angle, axis1_angle, axis2_angle;

void beginAxis()
{
    axis0_servo.attach(AX0_PIN);
    axis1_servo.attach(AX1_PIN);
    axis2_servo.attach(AX2_PIN);
    claw_servo.attach(CLAW_PIN);

    axis0_angle = AX0_ZERO;
    axis1_angle = AX1_ZERO;
    axis2_angle = AX2_ZERO;

    resetAxis();
}

void resetAxis(){
    moveAxis0(AX0_ZERO);
    moveAxis1(AX1_ZERO);
    moveAxis2(AX2_ZERO);
    moveClaw(90);
}

void testAxis(){
    moveAxis0(AX0_MAX);
    delay(2000);
    moveAxis0(AX0_MIN);
    delay(2000);
    moveAxis0(AX0_ZERO);
    delay(2000);
    moveAxis1(AX1_MAX);
    moveAxis2(AX1_MAX);
    delay(2000);
    moveAxis1(AX1_MIN);
    moveAxis2(AX1_MIN);
    delay(2000);

    claw_servo.write(0);
    delay(1000);
    claw_servo.write(180);
    delay(1000);
    claw_servo.write(0);
    delay(1000);
    claw_servo.write(180);
    delay(1000);

    resetAxis();
}

void moveAxis0(int angle)
{
    if (angle < AX0_MIN)
    {
        angle = AX0_MIN;
    }
    if (angle > AX0_MAX)
    {
        angle = AX0_MAX;
    }

    axis0_servo.write(angle);
    axis0_angle = angle;
}

void moveAxis1(int angle)
{
    if (angle < AX1_MIN)
    {
        angle = AX1_MIN;
    }
    if (angle > AX1_MAX)
    {
        angle = AX1_MAX;
    }

    // Axis 2 is vincolated to have is angle less (+ offset) than Axis 1
    if (angle - axis2_angle < AX1_AX2_OFFSET)
    {
        axis2_angle = angle - AX1_AX2_OFFSET;
    }
    axis2_servo.write(90 - axis2_angle);

    axis1_servo.write(angle);
    axis1_angle = angle;

    claw_pose.x = directKinematicsX(axis1_angle, axis2_angle);
    claw_pose.y = directKinematicsY(axis1_angle, axis2_angle);
}

void moveAxis2(int angle)
{
    if (angle < AX2_MIN)
    {
        angle = AX2_MIN;
    }
    if (angle > AX2_MAX)
    {
        angle = AX2_MAX;
    }

    // Axis 2 is vincolated to have is angle less (+ offset) than Axis 1
    if (axis1_angle - angle < AX1_AX2_OFFSET)
    {
        angle = axis1_angle - AX1_AX2_OFFSET;
    }
    axis2_servo.write(90 - angle);
    axis2_angle = angle;

    claw_pose.x = directKinematicsX(axis1_angle, axis2_angle);
    claw_pose.y = directKinematicsY(axis1_angle, axis2_angle);
}

void moveClaw(int angle)
{
    claw_servo.write(angle);
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

float getClawPoseX(){
    return claw_pose.x;
}

float getClawPoseY()
{
    return claw_pose.y;
}