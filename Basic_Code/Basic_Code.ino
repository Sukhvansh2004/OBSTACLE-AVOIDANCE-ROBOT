#include <NewPing.h>

#define sensor_f_echo A1
#define sensor_f_trig A2

#define sensor_r_echo A3
#define sensor_r_trig A4

#define sensor_l_echo A5
#define sensor_l_trig A6

#define ENA 10
#define ENB 3

#define IN_A_1 4
#define IN_A_2 5

#define IN_B_1 6
#define IN_B_2 4

int rd=15;
int ld=15;
int fd=20;
int dt=100;

int MAX_DISTANCE=200;
int offset_x=0;
int offset_y=100;

NewPing sonar_left(sensor_l_trig, sensor_l_echo, MAX_DISTANCE);
NewPing sonar_right(sensor_r_trig, sensor_r_echo, MAX_DISTANCE);
NewPing sonar_forward(sensor_f_trig, sensor_f_echo, MAX_DISTANCE);

void forward(){
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,HIGH);
  digitalWrite(IN_B_2,LOW);

}

void backward(){
  analogWrite(ENA,255);
  analogWrite(ENB,255);
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,HIGH);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);

}

void left(){
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);
}

void right(){
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  
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

  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(IN_A_1,OUTPUT);
  pinMode(IN_A_2,OUTPUT);

  pinMode(IN_B_1,OUTPUT);
  pinMode(IN_B_2,OUTPUT);
  
}
int pointer=0;

void loop() {
  int df=sonar_forward.ping_cm();
  int dr=sonar_right.ping_cm();
  int dl=sonar_left.ping_cm();

  if(dr<rd){
    if(pointer==0){
      backward();
      delay(dt*5);
      stationary();
      pointer=1;
    }
    left();
    delay(dt);
  }
  else if(dl<ld){
    if(pointer==0){
      backward();
      delay(dt*5);
      stationary();
      pointer=1;
    }
    right();
    delay(dt);
  }
  else if(df<fd){
    while(df<fd){
      df=sonar_forward.ping_cm();
      dr=sonar_right.ping_cm();
      dl=sonar_left.ping_cm();
      if(dl>dr){
        left();
        delay(dt);
      }
      else{
        right();
        delay(dt);
      }
    }
  }
  else{
    pointer=0;
    forward();
    delay(dt);
  }
}
