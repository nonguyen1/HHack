#define MOTOR_A_CONTROL_1 5
#define MOTOR_A_CONTROL_2 6
#define MOTOR_B_CONTROL_1 7
#define MOTOR_B_CONTROL_2 8
#define MOTOR_A_PWM 10
#define MOTOR_B_PWM 9

// TODO: change it
#define MOTOR_SPEED_FAST 255
#define MOTOR_SPEED_MEDIUM 150
#define MOTOR_SPEED_SLOW 50


#define ENCODER_A 2
#define ENCODER_B 3

volatile int aCount = 0;
volatile int bCount = 0;
volatile bool isAForward = true;
volatile bool isBForward = true;


void setup() {
  Serial.begin(115200);
  // Motor Driver TB6612FNG
  pinMode(MOTOR_A_CONTROL_1, OUTPUT);
  pinMode(MOTOR_A_CONTROL_2, OUTPUT);
  pinMode(MOTOR_B_CONTROL_1, OUTPUT);
  pinMode(MOTOR_B_CONTROL_2, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);

  // Encoder
  digitalWrite (ENCODER_A, HIGH);     // enable pull-ups
  digitalWrite (ENCODER_B, HIGH);
  attachInterrupt (0, encoderACB, RISING);   // interrupt 0 is pin 2, interrupt 1 is pin 3
  attachInterrupt (1, encoderBCB, RISING);
}

void loop() {
  motorSpeed(100, 100);
  backward();
  delay(2000);
  shortBreak();
  //    motorSpeed(MOTOR_SPEED_MEDIUM, MOTOR_SPEED_MEDIUM);
  //    testDrive();
  //  //  motorSpeed(MOTOR_SPEED_FAST, MOTOR_SPEED_FAST);
  //  //  testDrive();
  while (1);
}

void testDrive() {
  forward();
  delay(500);
  backward();
  delay(500);
  left();
  delay(500);
  right();
  delay(500);
  shortBreak();
}

/** Set motor speed
    @param  left motor speed
    @param  right motor speed
*/
void motorSpeed(int left, int right) {
  analogWrite(MOTOR_A_PWM, min(left, 255));
  analogWrite(MOTOR_B_PWM, min(right, 255));
}

// Set motor driver to go forward
void forward() {
  isAForward = true;
  isBForward = true;
  digitalWrite(MOTOR_A_CONTROL_1, HIGH);
  digitalWrite(MOTOR_A_CONTROL_2, LOW);
  digitalWrite(MOTOR_B_CONTROL_1, HIGH);
  digitalWrite(MOTOR_B_CONTROL_2, LOW);
}

// Set motor driver to go backward
void backward() {
  isAForward = false;
  isBForward = false;
  digitalWrite(MOTOR_A_CONTROL_1, LOW);
  digitalWrite(MOTOR_A_CONTROL_2, HIGH);
  digitalWrite(MOTOR_B_CONTROL_1, LOW);
  digitalWrite(MOTOR_B_CONTROL_2, HIGH);
}

// Set motor driver to go left
void left() {
  isAForward = false;
  isBForward = true;
  digitalWrite(MOTOR_A_CONTROL_1, HIGH);
  digitalWrite(MOTOR_A_CONTROL_2, LOW);
  digitalWrite(MOTOR_B_CONTROL_1, LOW);
  digitalWrite(MOTOR_B_CONTROL_2, HIGH);
}

// Set motor driver to go right
void right() {
  isAForward = true;
  isBForward = false;
  digitalWrite(MOTOR_A_CONTROL_1, LOW);
  digitalWrite(MOTOR_A_CONTROL_2, HIGH);
  digitalWrite(MOTOR_B_CONTROL_1, HIGH);
  digitalWrite(MOTOR_B_CONTROL_2, LOW);
}

// Set motor driver to short break mode
void shortBreak() {
  isAForward = true;
  isBForward = true;
  digitalWrite(MOTOR_A_CONTROL_1, HIGH);
  digitalWrite(MOTOR_A_CONTROL_2, HIGH);
  digitalWrite(MOTOR_B_CONTROL_1, HIGH);
  digitalWrite(MOTOR_B_CONTROL_2, HIGH);
}


// Interrupt Service Routine for a change to encoder pin A
void encoderACB ()
{
  if (isAForward) {
    aCount++;
  }
  else {
    aCount--;
  }
  Serial.print(aCount);
  Serial.print("\t");
  Serial.println(bCount);
}

// Interrupt Service Routine for a change to encoder pin B
void encoderBCB ()
{
  if (isBForward) {
    bCount++;
  }
  else {
    bCount--;
  }
  Serial.print(aCount);
  Serial.print("\t");
  Serial.println(bCount);
}
