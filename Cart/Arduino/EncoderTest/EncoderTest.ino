volatile int aCount = 0;
volatile int bCount = 0;
bool isAForward = true;
bool isBForward = false;

#define ENCODER_A 2
#define ENCODER_B 3

// Interrupt Service Routine for a change to encoder pin A
void encoderACB ()
{
  if (isAForward) {
    aCount++;
  }
  else {
    aCount--;
  }
}

// Interrupt Service Routine for a change to encoder pin A
void encoderBCB ()
{
  if (isBForward) {
    bCount++;
  }
  else {
    bCount--;
  }
}


void setup ()
{
  digitalWrite (ENCODER_A, HIGH);     // enable pull-ups
  digitalWrite (ENCODER_B, HIGH);
  attachInterrupt (0, encoderACB, RISING);   // interrupt 0 is pin 2, interrupt 1 is pin 3
  attachInterrupt (1, encoderBCB, RISING);
  Serial.begin (115200);
}  // end of setup

void loop ()
{
    Serial.print(aCount);
    Serial.print("\t");
    Serial.println(bCount);
    delay(50);

}
