#include "conf.h"

float directKinematicsX(int ax1_angle, int ax2_angle)
{
    float ax1_rad = ((ax1_angle + AX1_ANGLE_OFFSET) * 71) / 4068;
    float ax2_rad = ((ax2_angle + AX2_ANGLE_OFFSET) * 71) / 4068;

    float x = -AX1_ARM_LENGTH * cos(ax1_rad) + AX2_ARM_LENGTH * cos(ax2_rad);
    return x + X_OFFSET;
}

float directKinematicsY(int ax1_angle, int ax2_angle)
{
    float ax1_rad = ((ax1_angle + AX1_ANGLE_OFFSET) * 71) / 4068;
    float ax2_rad = ((ax2_angle + AX2_ANGLE_OFFSET) * 71) / 4068;

    float y = AX1_ARM_LENGTH * sin(ax1_rad) - AX2_ARM_LENGTH * sin(ax2_rad);
    return y + Y_OFFSET;
}

float inverseKinematicsAX1(float x, float y)
{
    float ax1_rad = -acos((pow(x, 2) + pow(y, 2) + pow(AX1_ARM_LENGTH, 2) - pow(AX2_ARM_LENGTH, 2)) / (2 * AX1_ARM_LENGTH * sqrt(pow(x, 2) + pow(y, 2)))) - atan(y / x);
    float ax1 = (ax1_rad * 4068) / 71;

    return ax1 + 180 - AX1_ANGLE_OFFSET;
}

float inverseKinematicsAX2(float x, float y)
{
    float ax2_rad = acos((pow(x, 2) + pow(y, 2) + pow(AX2_ARM_LENGTH, 2) - pow(AX1_ARM_LENGTH, 2)) / (2 * AX2_ARM_LENGTH * sqrt(pow(x, 2) + pow(y, 2)))) - atan(y / x);
    float ax2 = (ax2_rad * 4068) / 71;

    return ax2 - AX2_ANGLE_OFFSET;
}

/*

radians = (degrees * 71) / 4068

degrees = (radians * 4068) / 71

*/