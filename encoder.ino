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

void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_A_CONTROL_1, OUTPUT);
  pinMode(MOTOR_A_CONTROL_2, OUTPUT);
  pinMode(MOTOR_B_CONTROL_1, OUTPUT);
  pinMode(MOTOR_B_CONTROL_2, OUTPUT);
  pinMode(MOTOR_A_PWM, OUTPUT);
  pinMode(MOTOR_B_PWM, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  motorSpeed(MOTOR_SPEED_SLOW, MOTOR_SPEED_SLOW);
  testDrive();
  motorSpeed(MOTOR_SPEED_MEDIUM, MOTOR_SPEED_MEDIUM);
  testDrive();
  motorSpeed(MOTOR_SPEED_FAST, MOTOR_SPEED_FAST);
  testDrive();
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
  digitalWrite(MOTOR_A_CONTROL_1, HIGH);
  digitalWrite(MOTOR_A_CONTROL_2, LOW);
  digitalWrite(MOTOR_B_CONTROL_1, HIGH);
  digitalWrite(MOTOR_B_CONTROL_2, LOW);
}// Set motor driver to go backward
void backward() {
  digitalWrite(MOTOR_A_CONTROL_1, LOW);
  digitalWrite(MOTOR_A_CONTROL_2, HIGH);
  digitalWrite(MOTOR_B_CONTROL_1, LOW);
  digitalWrite(MOTOR_B_CONTROL_2, HIGH);
}
// Set motor driver to go left
void left() {
  digitalWrite(MOTOR_A_CONTROL_1, HIGH);
  digitalWrite(MOTOR_A_CONTROL_2, LOW);
  digitalWrite(MOTOR_B_CONTROL_1, LOW);
  digitalWrite(MOTOR_B_CONTROL_2, HIGH);
}
// Set motor driver to go right
void right() {
  digitalWrite(MOTOR_A_CONTROL_1, LOW);
  digitalWrite(MOTOR_A_CONTROL_2, HIGH);
  digitalWrite(MOTOR_B_CONTROL_1, HIGH);
  digitalWrite(MOTOR_B_CONTROL_2, LOW);
}
// Set motor driver to short break mode
void shortBreak() {
  digitalWrite(MOTOR_A_CONTROL_1, HIGH);
  digitalWrite(MOTOR_A_CONTROL_2, HIGH);
  digitalWrite(MOTOR_B_CONTROL_1, HIGH);
  digitalWrite(MOTOR_B_CONTROL_2, HIGH);
}
