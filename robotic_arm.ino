int potpin1 = A0;
int potpin2 = A1;

int val = 90;
void setup()
{
    beginSerial();
    beginArms();
}

void loop()
{
    serialLoop();
}
