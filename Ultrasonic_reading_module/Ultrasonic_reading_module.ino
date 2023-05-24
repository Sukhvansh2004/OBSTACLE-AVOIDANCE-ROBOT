const int trigPin = 2;  // Trig pin of the ultrasonic sensor
const int echoPin = 3;  // Echo pin of the ultrasonic sensor

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int reading(trigPin,echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance_cm = duration * 0.034 / 2;

  return distance_cm;  
}
