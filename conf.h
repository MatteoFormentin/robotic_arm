#ifndef conf
#define conf

#define FIRMWARE_VERSION 1.0

/*--------- PINS ASSIGNEMENT ---------*/
#define AX0_PIN 7
#define AX1_PIN 8
#define AX2_PIN 9
#define CLAW_PIN 10

/*------ AXIS SERVO ANGLE LIMIT ------*/
#define AX0_MIN 0
#define AX0_MAX 180

#define AX1_MIN 45
#define AX1_MAX 155

#define AX2_MIN 0
#define AX2_MAX 60

#define AX1_AX2_OFFSET 40 //Axis 1 and 2 joint vincolated

/*------ AXIS SERVO ZERO POINT ------*/
#define AX0_ZERO 90
#define AX1_ZERO 90
#define AX2_ZERO 0

/*------ KINEMATICS PARAMETERS ------*/
#define AX1_ARM_LENGTH 13.5
#define AX2_ARM_LENGTH 15
#define AX1_ANGLE_OFFSET -8.5 //Axis 1 arm is curved
#define AX2_ANGLE_OFFSET 9.5  //Axis 2 arm top angle is different from base one

//Claw offset
#define X_OFFSET 0
#define Y_OFFSET 0

#endif