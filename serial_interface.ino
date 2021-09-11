void beginSerial()
{
    Serial.begin(115200);
}

void serialLoop()
{
    if (Serial.available())
    {
        String received = Serial.readStringUntil('\n');
        String command;
        String argument;

        int separator_index = received.indexOf(' ');

        if (separator_index == -1) //No arg commands
        {
            command = received;
             if (command == "ECHO")
            {
                Serial.println("ECHO");
            }
            else
            {
                sendInvalidCommandError();
            }
        }
        else /// Multi arg commands - this will separate commands and arguments
        {
            command = received.substring(0, separator_index);
            argument = received.substring(separator_index + 1, received.length());

            if (command == "AX")
            {
                //Parse AX argument
                int separator_index2 = argument.indexOf(' ');
                int axis = argument.substring(0, separator_index2 + 1).toInt();
                int angle = argument.substring(separator_index2 + 1, argument.length()).toInt();

                switch (axis)
                {
                case 0:
                    moveAxis0Arm(angle);
                    Serial.println("AX 0 " + String(getAxis0Angle()));
                    break;
                case 1:
                    moveAxis1Arm(angle);
                    Serial.println("AX 1 " + String(getAxis1Angle()));
                    break;
                case 2:
                    moveAxis2Arm(angle);
                    Serial.println("AX 2 " + String(getAxis2Angle()));
                    break;

                default:
                    sendInvalidOptionError();
                    break;
                }
            }

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