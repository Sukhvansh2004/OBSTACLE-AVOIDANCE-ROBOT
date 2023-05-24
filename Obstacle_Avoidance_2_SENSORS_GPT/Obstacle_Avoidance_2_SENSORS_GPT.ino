// Ultrasonic sensor pins
const int trigPin1 = 2; // Trigger pin for sensor 1
const int echoPin1 = 3; // Echo pin for sensor 1
const int trigPin2 = 4; // Trigger pin for sensor 2
const int echoPin2 = 5; // Echo pin for sensor 2

// Motor control pins
const int leftMotorPin1 = 6; // Motor 1 control pin 1
const int leftMotorPin2 = 7; // Motor 1 control pin 2
const int rightMotorPin1 = 8; // Motor 2 control pin 1
const int rightMotorPin2 = 9; // Motor 2 control pin 2

void setup() {
  // Ultrasonic sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  // Motor control pins
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  // Measure distances from ultrasonic sensors
  float distance1 = getDistance(trigPin1, echoPin1);
  float distance2 = getDistance(trigPin2, echoPin2);

  // Print the distances
  Serial.print("Distance from Sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Distance from Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Check if obstacles are within range
  if (distance1 < 20 && distance2 < 20) {
    // Reverse and turn right
    backward();
    delay(500);
    turnRight();
  } else if (distance1 < 20) {
    // Turn left
    turnLeft();
  } else if (distance2 < 20) {
    // Turn right
    turnRight();
  } else {
    // Move forward
    forward();
  }
}

// Function to measure distance using ultrasonic sensor
float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  float distance = duration * 0.034 / 2;
  return distance;
}

// Function to move forward
void forward() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

// Function to move backward
void backward() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}

// Function to turn left
void turnLeft() {
  digitalWrite(leftMotorPin1, LOW);
  digitalWrite(leftMotorPin2, HIGH);
  digitalWrite(rightMotorPin1, HIGH);
  digitalWrite(rightMotorPin2, LOW);
}

// Function to turn right
void turnRight() {
  digitalWrite(leftMotorPin1, HIGH);
  digitalWrite(leftMotorPin2, LOW);
  digitalWrite(rightMotorPin1, LOW);
  digitalWrite(rightMotorPin2, HIGH);
}
