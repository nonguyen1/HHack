#include <Wire.h>
#define SLAVE_ADDRESS 0x04


#define MOTOR_A_CONTROL_1 5
#define MOTOR_A_CONTROL_2 6
#define MOTOR_B_CONTROL_1 7
#define MOTOR_B_CONTROL_2 8
#define MOTOR_A_PWM 10
#define MOTOR_B_PWM 9

// TODO: change it
#define MOTOR_SPEED_FAST 100
#define MOTOR_SPEED_MEDIUM 65
#define MOTOR_SPEED_SLOW 40


#define ENCODER_A 2
#define ENCODER_B 3

// Control Parameter
#define ENTOUR_ERROR_MULTIPLIER 0.1
#define ENTOUR_ERROR_CORRECTION_TOLERANCE_PERCENTAGE 5

#define TURN_NINTY_DISTANCE 16
#define FORWARD_BLOCK_DISTANCE 16

volatile int aCurrentPos = 0;
volatile int bCurrentPos = 0;
volatile bool isAForward = true;
volatile bool isBForward = false;

char direct = 'N'; // N: No command, F: Forward, B: Backward, L: Left, R: Right
int distance = 0; // Distance to travel

void setup() {
  Serial.begin(115200);
  // I2C
  Wire.begin(SLAVE_ADDRESS); // Init I2C
  // Attach cb
  Wire.onReceive(receiveData);


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
  attachInterrupt (0, encoderAISR, RISING);   // interrupt 0 is pin 2, interrupt 1 is pin 3
  attachInterrupt (1, encoderBISR, RISING);
}

int roughSpeed(int aTargetPos, int bTargetPos);
void setMotorDirectionSpeed(int deltaA, int deltaB, int speedA, int speedB);


void loop() {
  movementHandle();
  //  moveTo(TURN_NINTY_POWER, -TURN_NINTY_POWER);
  //  setMotorSpeed(0, 0);
  //  while (1);
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

/* Set motor speed
    @param  left motor speed
    @param  right motor speed
*/
void setMotorSpeed(int aSpeed, int bSpeed) {
  //  Serial.print("Set Motor Speed ");
  //  Serial.print(aSpeed);
  //  Serial.print("\t");
  //  Serial.println(bSpeed);
  // Detect direction and setup
  if (aSpeed > 0 && bSpeed > 0)
    forward();
  else if (aSpeed <= 0 && bSpeed > 0)
    left();
  else if (aSpeed > 0 && bSpeed <= 0)
    right();
  else if (aSpeed == 0 && bSpeed == 0)
    shortBreak();
  else if (aSpeed < 0 && bSpeed < 0)
    backward();

  // Output PWM
  analogWrite(MOTOR_A_PWM, min(abs(aSpeed), 255));
  analogWrite(MOTOR_B_PWM, min(abs(bSpeed), 255));
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
void encoderAISR ()
{
  if (isAForward) {
    aCurrentPos++;
  }
  else {
    aCurrentPos--;
  }
  Serial.print("\nCurrent at ");
  Serial.print(aCurrentPos);
  Serial.print("\t");
  Serial.println(bCurrentPos);
}

// Interrupt Service Routine for a change to encoder pin B
void encoderBISR ()
{
  if (isBForward) {
    bCurrentPos++;
  }
  else {
    bCurrentPos--;
  }
  Serial.print("\n Current at ");
  Serial.print(aCurrentPos);
  Serial.print("\t");
  Serial.println(bCurrentPos);
}

// Searches for command from I2C, and respond to it
void movementHandle() {
  if (direct != 'N') {
    if (direct == 'F') {
      moveTo(distance, distance);
      setMotorSpeed(0, 0);
      direct = 'N';
    }
    else if (direct == 'B') {
      moveTo(-distance, -distance);
      setMotorSpeed(0, 0);
      direct = 'N';
    }
    else if (direct == 'L') {
      moveTo(-distance, distance);
      setMotorSpeed(0, 0);
      direct = 'N';
    }
    else if (direct == 'R') {
      moveTo(distance, -distance);
      setMotorSpeed(0, 0);
      direct = 'N';
    }
  }
}

void moveTo(int aTargetPos, int bTargetPos) {
  Serial.print("Moving to ");
  Serial.print(aTargetPos);
  Serial.print("\t");
  Serial.println(bTargetPos);

  int aStartingPos = aCurrentPos;
  int bStartingPos = bCurrentPos;
  int deltaA = aTargetPos - aCurrentPos;
  int deltaB = bTargetPos - bCurrentPos;
  Serial.print("dA = ");
  Serial.print(deltaA);
  Serial.print("\tdB = ");
  Serial.println(deltaB);
  // Set speed based off distance traveling
  int initialMotorSpeed = roughSpeed(aTargetPos, bTargetPos);

  // Start off
  Serial.println("Setting a initial speed");
  setMotorDirectionSpeed(deltaA, deltaB, initialMotorSpeed, initialMotorSpeed);

  // Maintain speed until close. Entour error correction control.
  //   Serial.println("Entour error correction started");
  //   int aFinishPercentage = 0;
  //   int bFinishPercentage = 0;
  //   int aCurrentSpeed = initialMotorSpeed;
  //   int bCurrentSpeed = initialMotorSpeed;
  //   int aLastSpeed = aCurrentSpeed;
  //   int bLastSpeed = bCurrentSpeed;
  //   while (abs(deltaA) + abs(deltaB) > 10) {
  //     deltaA = aTargetPos - aCurrentPos;
  //     deltaB = bTargetPos - bCurrentPos;
  //     int currentBaseSpeed = roughSpeed(aTargetPos, bTargetPos);
  //     // Update params
  //     aLastSpeed = min(aLastSpeed, currentBaseSpeed);  // Ensures last speed updated if current base speed is smaller
  //     bLastSpeed = min(bLastSpeed, currentBaseSpeed);
  //     aFinishPercentage = map(aCurrentPos, aStartingPos, aTargetPos, 0, 100);
  //     bFinishPercentage = map(bCurrentPos, bStartingPos, bTargetPos, 0, 100);
  //     Serial.print("EEC * delta:");
  //     Serial.print(deltaA); Serial.print("|"); Serial.print(deltaB); Serial.print("|*curr*");
  //     Serial.print(aCurrentPos); Serial.print("|"); Serial.print(bCurrentPos); Serial.print("|*Slast*");
  //     Serial.print(aLastSpeed); Serial.print("|"); Serial.print(bLastSpeed); Serial.print("|**");
  //     Serial.print("%"); Serial.print(aFinishPercentage); Serial.print("|"); Serial.println(bFinishPercentage);
  //     // Control
  //     if (abs(aFinishPercentage - bFinishPercentage) > ENTOUR_ERROR_CORRECTION_TOLERANCE_PERCENTAGE) { // Start entour error correction
  //       Serial.println("EEC needed");
  //       if (aFinishPercentage > bFinishPercentage) { // A running faster than b, slower a, faster b
  //         aCurrentSpeed = currentBaseSpeed - ENTOUR_ERROR_MULTIPLIER * currentBaseSpeed;
  //         bCurrentSpeed = currentBaseSpeed + ENTOUR_ERROR_MULTIPLIER * currentBaseSpeed;
  //       }
  //       else { // A running slower than b, faster a, slower b
  //         aCurrentSpeed = currentBaseSpeed + ENTOUR_ERROR_MULTIPLIER * currentBaseSpeed;
  //         bCurrentSpeed = currentBaseSpeed - ENTOUR_ERROR_MULTIPLIER * currentBaseSpeed;
  //       }
  // //      Serial.print("\taCurrentSpeed="); Serial.print(aCurrentSpeed); Serial.print("\tbCurrentSpeed="); Serial.print(bCurrentSpeed);
  //     }
  //     setMotorDirectionSpeed(deltaA, deltaB, aCurrentSpeed, bCurrentSpeed);
  //     aLastSpeed = aCurrentSpeed;
  //     bLastSpeed = bCurrentSpeed;
  //   }

  // Slow down speed when approaching target
  //   Serial.println("SLOW DOWN CONTROL HERE");
  while (true) {
    int deltaA = aTargetPos - aCurrentPos;
    int deltaB = bTargetPos - bCurrentPos;
    //    Serial.print("aTarget=");  Serial.print(aTargetPos); Serial.print("|"); Serial.print(bTargetPos);
    //    Serial.print("|*curr*"); Serial.print(aCurrentPos); Serial.print("|"); Serial.print(bCurrentPos);
    //    Serial.print("delta="); Serial.print(deltaA); Serial.print("|"); Serial.println(deltaB);
    int currentBaseSpeed = roughSpeed(aTargetPos, bTargetPos);
    setMotorDirectionSpeed(deltaA, deltaB, currentBaseSpeed, currentBaseSpeed);
    //    Serial.println(abs(deltaA));
    //    Serial.println(abs(deltaA) > 5);
    if (abs(deltaA) <= 5)
      break;
  }
  Serial.println("Out");
  setMotorSpeed(0, 0);

}

/*
   @brief Roughly estimates the speed level based off distance to destination

   @return  motorSpeed the speed for the motors
*/
int roughSpeed(int aTargetPos, int bTargetPos) {
  int deltaA = aTargetPos - aCurrentPos;
  int deltaB = bTargetPos - bCurrentPos;
  int motorSpeed = MOTOR_SPEED_FAST;
  if (abs(deltaA) < 5 || abs(deltaB) < 5) {
    motorSpeed = MOTOR_SPEED_SLOW;
  }
  else if (abs(deltaA) < 12 || abs(deltaB) < 12)
    motorSpeed = MOTOR_SPEED_MEDIUM;
  return motorSpeed;
}

/*  @brief Set both motor's speed and direction based on distance between now and target

    @param deltaA  A's location now - A's target location
    @param deltaB  B's location now - B's target location
    @param speedA  The speed (scalar) for motor A
    @param speedB  The speed (scalar) for motor B
*/
void setMotorDirectionSpeed(int deltaA, int deltaB, int speedA, int speedB) {
  if (deltaA > 0 && deltaB > 0)
    setMotorSpeed(speedA, speedB);
  else if (deltaA <= 0 && deltaB > 0)
    setMotorSpeed(-speedA, speedB);
  else if (deltaA > 0 && deltaB <= 0)
    setMotorSpeed(speedA, -speedB);
  else if (deltaA == 0 && deltaB == 0)
    setMotorSpeed(0, 0);
  else if (deltaA <= 0 && deltaB <= 0)
    setMotorSpeed(-speedA, speedB);
}

/*
   @brief I2C communication receive data event callback
*/
void receiveData(int byteCount) {
  static int dirRead;
  while (Wire.available()) {
    dirRead = Wire.read();
    distance = Wire.read();
  }
  direct = (char)dirRead;
  Serial.print("Received: ");
  Serial.print(dirRead);
  Serial.println(distance);

}
