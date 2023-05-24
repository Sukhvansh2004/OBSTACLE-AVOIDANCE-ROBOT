#include <NewPing.h>

#define sensor_l_echo 12
#define sensor__trig 13

#define sensor_f_echo 2

#define sensor_r_echo 4

#define ENA 11
#define ENB 6

#define IN_A_1 10
#define IN_A_2 9

#define IN_B_1 7
#define IN_B_2 8


int rd=15;
int ld=15;
int fd=10;
int dt=30;

int MAX_DISTANCE=1000;
int offset_x=0;
int offset_y=100;


NewPing sonar_left(sensor__trig, sensor_l_echo, MAX_DISTANCE);
NewPing sonar_right(sensor__trig, sensor_r_echo, MAX_DISTANCE);
NewPing sonar_forward(sensor__trig, sensor_f_echo, MAX_DISTANCE);

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

int p=0;
void loop() {
  delay(10);
  int df=sonar_forward.ping_cm();
  delay(10);
  int dr=sonar_right.ping_cm();
  delay(10);
  int dl=sonar_left.ping_cm();
//  if(dl==0 || dr==0|| df==0 
  Serial.print(df);
  Serial.print(" ");
  Serial.print(dl);
  Serial.print(" ");
  Serial.print(dr);
  Serial.println(" ");

  if(df<fd && p++>10){
    if(dl<dr){
      backward();
      delay(300);
      right();
      delay(856);
      
    }
    else{
      backward();
      delay(300);
      left();
      delay(856);
    }
    stationary();
  }
  else if(dr<rd){
    left();
    delay(dt);
    p=0;
  }
  else if(dl<ld){
    right();
    delay(dt);
    p=0;
  }
  else{
    forward();
    delay(dt);
  }
}
