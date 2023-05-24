#include <NewPing.h>  // Library for ultrasonic sensors

// Pin definitions
#define TRIGGER_PIN_FRONT 2  // Trigger pin for front sensor
#define ECHO_PIN_FRONT 3     // Echo pin for front sensor
#define TRIGGER_PIN_LEFT 4   // Trigger pin for left sensor
#define ECHO_PIN_LEFT 5      // Echo pin for left sensor
#define TRIGGER_PIN_RIGHT 6  // Trigger pin for right sensor
#define ECHO_PIN_RIGHT 7     // Echo pin for right sensor
#define MOTORA_ENA 9         // Motor A enable pin
#define MOTORA_IN1 10        // Motor A input 1
#define MOTORA_IN2 11        // Motor A input 2
#define MOTORB_ENB 6         // Motor B enable pin
#define MOTORB_IN3 7         // Motor B input 3
#define MOTORB_IN4 8         // Motor B input 4

// Robot dimensions
#define ROBOT_WIDTH 30       // Width of the robot in cm
#define ROBOT_LENGTH 22.5    // Length of the robot in cm

// Ultrasonic sensor objects
NewPing frontSensor(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT, ROBOT_LENGTH);  // Front sensor
NewPing leftSensor(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT, ROBOT_WIDTH);      // Left sensor
NewPing rightSensor(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT, ROBOT_WIDTH);   // Right sensor

// Movement variables
float linearVelocity = 28.99 * 0.001;   // Linear velocity in cm/ms
float angularVelocity = 105.07 * 0.001; // Angular velocity in degrees/ms

// Function to control the motors
void controlMotors(int motorASpeed, int motorBSpeed, bool motorADirection, bool motorBDirection) {
  analogWrite(MOTORA_ENA, motorASpeed);  // Set speed of motor A
  digitalWrite(MOTORA_IN1, motorADirection);
  digitalWrite(MOTORA_IN2, !motorADirection);
  analogWrite(MOTORB_ENB, motorBSpeed);  // Set speed of motor B
  digitalWrite(MOTORB_IN3, motorBDirection);
  digitalWrite(MOTORB_IN4, !motorBDirection);
}

// Function to move the robot forward
void moveForward() {
  controlMotors(255, 255, HIGH, HIGH);
}

// Function to move the robot backward
void moveBackward() {
  controlMotors(255, 255, LOW, LOW);
}

// Function to turn the robot left
void turnLeft() {
  controlMotors(255, 255, LOW, HIGH);
}

// Function to turn the robot right
void turnRight() {
  controlMotors(255, 255, HIGH, LOW);
}

// Function to stop the robot
void stopRobot() {
  controlMotors(0, 0, LOW, LOW);
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set motor control pins as outputs
  pinMode(MOTORA_ENA, OUTPUT);
  pinMode(MOTORA_IN1, OUTPUT);
  pinMode(MOTORA_IN2, OUTPUT);
  pinMode(MOTORB_ENB, OUTPUT);
  pinMode(MOTORB_IN3, OUTPUT);
  pinMode(MOTORB_IN4, OUTPUT);
}

void loop() {
  // Read distance from front sensor
  int frontDistance = frontSensor.ping_cm();

  // Read distances from left and right sensors
  int leftDistance = leftSensor.ping_cm();
  int rightDistance = rightSensor.ping_cm();

  // Print sensor readings
  Serial.print("Front: ");
  Serial.print(frontDistance);
  Serial.print(" cm, Left: ");
  Serial.print(leftDistance);
  Serial.print(" cm, Right: ");
  Serial.print(rightDistance);
  Serial.println(" cm");

  // Obstacle detection and avoidance logic
  if (frontDistance > 0 && frontDistance <= 20) {
    // If an obstacle is detected in front, turn right
    turnRight();
    delay(500);
  } else if (leftDistance > 0 && leftDistance <= 20) {
    // If an obstacle is detected on the left, turn right
    turnRight();
    delay(500);
  } else if (rightDistance > 0 && rightDistance <= 20) {
    // If an obstacle is detected on the right, turn left
    turnLeft();
    delay(500);
  } else {
    // No obstacles detected, move forward
    moveForward();
  }
}
