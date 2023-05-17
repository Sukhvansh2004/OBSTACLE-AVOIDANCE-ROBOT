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
#define IN_B_2 7

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

int vel(int reading){
  return reading; //mathematical equation converting the input voltage to speed
}

int omega(int reading){
  return reading; //mathematical equation converting input voltage to angular velocity
}

void stationary(){
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,LOW);
}

void forward(int voltage,int distance=0){
  analogWrite(ENA,voltage);
  analogWrite(ENB,voltage);
  int t=distance/vel(voltage);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,HIGH);
  digitalWrite(IN_B_2,LOW);

  if (distance!=0){
    delay(t);
    stationary();
  }
}

void backward(int voltage,int distance=0){
  analogWrite(ENA,voltage);
  analogWrite(ENB,voltage);
  int t=distance/vel(voltage);
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,HIGH);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);
  
  if (distance!=0){
    delay(t);
    stationary();
  }
}

void left(int voltage,int angle=0){
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  int t=angle/omega(voltage);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);

  if (angle!=0){
    delay(t);
    stationary();
  }
  
}

void right(int voltage,int angle=0){
  analogWrite(ENA,100);
  analogWrite(ENB,100);
  int t=angle/omega(voltage);
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,HIGH);

  digitalWrite(IN_B_1,HIGH);
  digitalWrite(IN_B_2,LOW);
  
  if (angle!=0){
    delay(t);
    stationary();
  }
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
int angleoff=0;

void loop() {
  int df=sonar_forward.ping_cm();
  int dr=sonar_right.ping_cm();
  int dl=sonar_left.ping_cm();

  if(dr<rd){
    left(100,90-angleoff);
  }
  else if(dl<ld){
    right(100,90+angleoff);
  }
  else if(df<fd){
    int flag1=0;
    int flag2=0;
    int firstIter=1;
    while(df<fd){
      df=sonar_forward.ping_cm();
      dr=sonar_right.ping_cm();
      dl=sonar_left.ping_cm();
      if(firstIter){
        if(dl>dr){
          left(100);
          delay(dt);
          angleoff=angleoff+omega(100)*dt;
          flag1=1;
          if(flag2==1){
            firstIter=0;
            flag2=0;
          }
        }
        else{
          right(100);
          delay(dt);
          angleoff=angleoff-omega(100)*dt;
          flag2=1;
          if(flag1==1){
            firstIter=0;
            flag1=0;
          }
        }
      }
      else{
        if(flag1==1){
          left(100,90-angleoff);
        }
        else{
          right(100,90+angleoff);
        }
      }
    }
  }
  else{
    forward(255,5);
    angleoff=0;
  }
}
