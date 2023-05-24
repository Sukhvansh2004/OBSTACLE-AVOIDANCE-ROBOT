#include <NewPing.h>

#define sensor_l_echo 12
#define sensor_trig 13
#define sensor_f_echo 2
#define sensor_r_echo 4

#define ENA 11
#define ENB 6

#define IN_A_1 10
#define IN_A_2 9

#define IN_B_1 8 
#define IN_B_2 7

int rd=10;
int ld=10;
int fd=15;
int dt=30;

int MAX_DISTANCE=500;
int offset_x=0;
int offset_y=100;

NewPing sonar_left(sensor_trig, sensor_l_echo, MAX_DISTANCE);
NewPing sonar_right(sensor_trig, sensor_r_echo, MAX_DISTANCE);
NewPing sonar_forward(sensor_trig, sensor_f_echo, MAX_DISTANCE);

void backward(){
  analogWrite(ENA,242);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,HIGH);
  digitalWrite(IN_B_2,LOW);

}

void forward(){
  analogWrite(ENA,242);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,HIGH);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);

}

void right(){
  analogWrite(ENA,242);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);
}

void left(){
  analogWrite(ENA,242);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,HIGH);

  digitalWrite(IN_B_1,HIGH);
  digitalWrite(IN_B_2,LOW);
}

void stationary(){
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,LOW);
}
void setup() {

  Serial.begin(9600);
  
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(IN_A_1,OUTPUT);
  pinMode(IN_A_2,OUTPUT);

  pinMode(IN_B_1,OUTPUT);
  pinMode(IN_B_2,OUTPUT);
  
}
int pointer=0;

void loop() {
  forward();
  delay(100);
}
