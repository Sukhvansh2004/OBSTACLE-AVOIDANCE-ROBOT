#include <NewPing.h>

#define sensor_trig 13

#define sensor_l_echo 7
#define sensor_f_echo 2
#define sensor_r_echo 12

#define ENA 11
#define ENB 3

#define IN_A_1 10
#define IN_A_2 9

#define IN_B_1 6 
#define IN_B_2 5

int rd=20;
int ld=20;
int fd=20;
int dt=15;

int offset_x=0;
int offset_y=100;
int MAX_DISTANCE=500;

float vel=28.99*(0.001);
float omega=105.07*(0.001);


NewPing sonar_left(sensor_trig, sensor_l_echo, MAX_DISTANCE);
NewPing sonar_right(sensor_trig, sensor_r_echo, MAX_DISTANCE);
NewPing sonar_forward(sensor_trig, sensor_f_echo, MAX_DISTANCE);


int reading(int trigPin,int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  int distance_cm = duration * 0.034 / 2;

  return distance_cm;  
}

void backward(float distance=0){
  analogWrite(ENA,242);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,HIGH);
  digitalWrite(IN_B_2,LOW);

  if(distance!=0){
    delay(distance/vel);
  }

}

void forward(float distance=0){
  analogWrite(ENA,242);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,HIGH);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);

  if(distance!=0){
    delay(distance/vel);
  }
}

void right(float angle=0){
  analogWrite(ENA,242);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);

  if(angle!=0){
    delay(angle/omega);
  }
}

void left(float angle=0){
  analogWrite(ENA,242);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,HIGH);

  digitalWrite(IN_B_1,HIGH);
  digitalWrite(IN_B_2,LOW);

  
  if(angle!=0){
    delay(angle/omega);
  }
}

void stationary(){
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,LOW);
}
void setup() {

  Serial.begin(9600);
  pinMode(sensor_l_echo,INPUT);
  pinMode(sensor_r_echo,INPUT);
  pinMode(sensor_f_echo,INPUT);
  pinMode(sensor_trig,OUTPUT);
  
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(IN_A_1,OUTPUT);
  pinMode(IN_A_2,OUTPUT);

  pinMode(IN_B_1,OUTPUT);
  pinMode(IN_B_2,OUTPUT);
  
}

void loop() {
  int df=sonar_forward.ping_cm();
  int dr=sonar_right.ping_cm();
  int dl=sonar_left.ping_cm();
  Serial.print(df);
  Serial.print(" ");
  Serial.print(dl);
  Serial.print(" ");
  Serial.print(dr);
  Serial.println(" ");
  Serial.println(f);

  if(df<fd){
    if(dl<dr){
      backward(15);
      right(52);
    }
    else{
      backward(15);
      left(52);
    }
    stationary();
  }
  else if(dr<rd){
    left();
    delay(dt);
  }
  else if(dl<ld){
    right();
    delay(dt);
  }
  else{
    forward();
    delay(dt);
  }
}
