#include <Bluepad32.h>
#include <ESP32Servo.h> 

const int PWMA = 5;  const int AIN1 = 6;  const int AIN2 = 7;  
const int BIN1 = 20; const int BIN2 = 10; const int PWMB = 21; 
const int SERVO_PIN = 1; 

const int SERVO_CENTER = 90;  
const int SERVO_RANGE = 35;   

Servo steeringServo;
ControllerPtr myControllers[BP32_MAX_GAMEPADS];

void setup() {
  pinMode(PWMA, OUTPUT); pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT); pinMode(PWMB, OUTPUT);
  
  steeringServo.attach(SERVO_PIN);
  steeringServo.write(SERVO_CENTER); 
  BP32.setup(&onConnected, &onDisconnected);
}

void onConnected(ControllerPtr ctl) { myControllers[0] = ctl; }
void onDisconnected(ControllerPtr ctl) { myControllers[0] = nullptr; stopMotors(); }

// Consolidated Drive Function for Forward and Reverse Arcs
void drive(int speed, float turnFactor, bool forward) {
  int leftSpeed = speed;
  int rightSpeed = speed;

  // Set direction based on the 'forward' boolean
  if (forward) {
    digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
  } else {
    digitalWrite(AIN1, LOW); digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW); digitalWrite(BIN2, HIGH);
  }

  // Differential Steering Logic
  if (turnFactor > 0.1) {      // Turning Right
    // Slow down the inner (right) wheel to create an arc
    rightSpeed = speed * (1.0 - (turnFactor * 0.7)); 
  } else if (turnFactor < -0.1) { // Turning Left
    // Slow down the inner (left) wheel to create an arc
    leftSpeed = speed * (1.0 - (abs(turnFactor) * 0.7)); 
  }

  analogWrite(PWMA, leftSpeed);
  analogWrite(PWMB, rightSpeed);
}

void stopMotors() {
  digitalWrite(AIN1, LOW); digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW); digitalWrite(BIN2, LOW);
  analogWrite(PWMA, 0); analogWrite(PWMB, 0);
}

void processGamepad(ControllerPtr ctl) {
  // 1. Calculate Steering
  int stickX = ctl->axisX(); 
  float turnFactor = map(stickX, -512, 512, -100, 100) / 100.0;
  
  // 2. Physical Servo Steering
  steeringServo.write(map(stickX, -512, 512, SERVO_CENTER - SERVO_RANGE, SERVO_CENTER + SERVO_RANGE));

  uint16_t buttons = ctl->buttons();
  
  // 3. Movement Logic
  if (buttons & 0x0008)      drive(255, turnFactor, true);  // Y: Turbo
  else if (buttons & 0x0004) drive(50, turnFactor, true);   // X: Fast
  else if (buttons & 0x0002) drive(20, turnFactor, true);   // B: Medium
  else if (buttons & 0x0001) drive(10, turnFactor, true);   // A: Slowest
  else if (buttons & 0x0010) drive(20, turnFactor, false);  // L1: Reverse with Steering!
  else stopMotors();
}

void loop() {
  BP32.update();
  if (myControllers[0]) processGamepad(myControllers[0]);
}