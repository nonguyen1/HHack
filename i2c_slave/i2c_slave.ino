#include <Wire.h>

#define SLAVE_ADDRESS 0x04
int data; int spd=0; char dir=' ';


void setup() {
  pinMode(9, OUTPUT);pinMode(8, OUTPUT);pinMode(7, OUTPUT);pinMode(6, OUTPUT);
  Serial.begin(9600); // start serial for output
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Serial.println("Ready!");
}

void loop() {
  delay(100);
}

// callback for received data
void receiveData(int byteCount) {
  static int dirRead;
  while (Wire.available()) {
    dirRead = Wire.read();
    spd = Wire.read();
  }
  dir = (char)dirRead;
  Serial.println(dir);
  Serial.println(spd);

}
