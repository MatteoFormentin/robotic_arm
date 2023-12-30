#include "conf.h"

void beginSerial()
{
    Serial.begin(115200);
    Serial.println("-------- EEZYBOT ARM MK2 ---------");
    Serial.println("     Firmware Version " + String(FIRMWARE_VERSION));
    Serial.println("     HW: Carlo Franciscone");
    Serial.println("     SW: Matteo Formentin");
    Serial.println("----------------------------------");
}

void serialLoop()
{
    if (Serial.available())
    {
        String received = Serial.readStringUntil('\n');
        String command;
        String argument;

        int separator_index = received.indexOf(' '); // If there is a separator, then the commands has an argoument

        /*------ NO ARG COMMANDS ------*/
        if (separator_index == -1) //No arg commands
        {
            command = received;

            /*------ PING TEST ------*/
            if (command == "ECHO")
            {
                Serial.println("ECHO OK");
            }
            /*------ AXIS RESET ------*/
            else if (command == "RESET")
            {
                resetAxis();
                Serial.println("RESET OK");
            }

            /*------ DEBUG ONLY - REMOVE ------*/
            else if (command == "TEST1")
            {
                moveAxis0(0);
                moveAxis1(180);
                moveAxis2(180);
                moveClaw(180);
                delay(3000);
                moveClaw(0);
                delay(500);
                moveAxis1(90);
                moveAxis2(0);
                delay(1000);
                moveAxis0(180);
                delay(1000);
                moveAxis1(180);
                moveAxis2(180);
                delay(1000);
                moveClaw(180);
                delay(1000);
                moveAxis0(90);
                moveAxis1(90);
                moveAxis2(0);
                resetAxis();
            }

            /*------ RUN TEST ROUTINE ------*/
            else if (command == "TEST")
            {
                Serial.println("TEST START");
                testAxis();
                Serial.println("TEST DONE");
            }
            /*------ GET AXIS ANGLE ------*/
            else if (command == "AX")
            {
                Serial.println("AX 0 " + String(getAxis0Angle()) + " AX 1 " + String(getAxis1Angle()) + " AX 2 " + String(getAxis2Angle()));
            }
            /*------ GET CLAW POSITION (DIRECT KINEMATICS) ------*/
            else if (command == "POS")
            {
                Serial.println("X " + String(getClawPoseX()) + " Y " + String(getClawPoseY()));
            }
            /*------ INVALID COMMAND ------*/
            else
            {
                sendInvalidCommandError();
            }
        }

        /*------ ARG COMMANDS ------*/
        else
        {
            /// This will separate commands and arguments, each commands must handle argouments parsing (also multiple argouments)
            command = received.substring(0, separator_index);
            argument = received.substring(separator_index + 1, received.length());

            /*------ AX COMMAND - ANGLE POSITION OF SPECIFIED AXIS ------*/
            if (command == "AX")
            {
                //If no AX second value (angle) - return current angle of specified axis
                int separator_index2 = argument.indexOf(' ');
                if (separator_index2 == -1)
                {
                    /*------ GET SELECTED AXIS ANGLE ------*/
                    int axis = argument.toInt(); //Parse argument
                    switch (axis)
                    {
                    /*------ GET AXIS 0 ANGLE ------*/
                    case 0:
                        Serial.println("AX 0 " + String(getAxis0Angle()));
                        break;
                    /*------ GET AXIS 1 ANGLE ------*/
                    case 1:
                        Serial.println("AX 1 " + String(getAxis1Angle()));
                        break;
                    /*------ GET AXIS 2 ANGLE ------*/
                    case 2:
                        Serial.println("AX 2 " + String(getAxis2Angle()));
                        break;
                    /*------ GET AXIS 3 (CLAW) ANGLE ------*/
                    case 3:
                        Serial.println("AX 3 MOVED");
                        break;
                    /*------ INVALID AXIS SELECTION ------*/
                    default:
                        sendInvalidOptionError();
                        break;
                    }
                }
                else
                {
                    //Parse AX second argument
                    int axis = argument.substring(0, separator_index2 + 1).toInt();
                    int angle = argument.substring(separator_index2 + 1, argument.length()).toInt();

                    switch (axis)
                    {
                    /*------ MOVE AXIS 0 TO AN ANGLE ------*/
                    case 0:
                        moveAxis0(angle);
                        Serial.println("AX 0 " + String(getAxis0Angle()));
                        break;
                    /*------ MOVE AXIS 1 TO AN ANGLE ------*/
                    case 1:
                        moveAxis1(angle);
                        Serial.println("AX 1 " + String(getAxis1Angle()));
                        break;
                    /*------ MOVE AXIS 2 TO AN ANGLE ------*/
                    case 2:
                        moveAxis2(angle);
                        Serial.println("AX 2 " + String(getAxis2Angle()));
                        break;
                    /*------ MOVE AXIS 3 (CLAW) TO AN ANGLE ------*/
                    case 3:
                        moveClaw(angle);
                        Serial.println("AX 3 MOVED");
                        break;
                    /*------ INVALID AXIS SELECTION ------*/
                    default:
                        sendInvalidOptionError();
                        break;
                    }
                }
            }
            /*------ POS COMMAND - CLAW POSITION (INVERSE KINEMATICS) ------*/
            else if (command == "POS")
            {
                int separator_index2 = argument.indexOf(' ');
                //If only X pos is provided invalid
                if (separator_index2 == -1)
                {
                    sendInvalidOptionError();
                }
                else
                {
                    float x = argument.substring(0, separator_index2 + 1).toFloat();
                    float y = argument.substring(separator_index2 + 1, argument.length()).toFloat();

                    int ax1 = inverseKinematicsAX1(x, y);
                    int ax2 = inverseKinematicsAX2(x, y);
                    moveAxis1(ax1);
                    moveAxis2(ax2);

                    Serial.println("X " + String(getClawPoseX()) + " Y " + String(getClawPoseY()));
                }
            }
            /*------ INVALID COMMAND ------*/
            else
            {
                sendInvalidCommandError();
            }
        }
    }
}

void sendInvalidCommandError()
{
    Serial.println("INVCOMM");
}

void sendInvalidOptionError()
{
    Serial.println("INVOPT");
}