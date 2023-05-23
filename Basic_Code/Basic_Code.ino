#include <NewPing.h>

#define sensor_l_echo 13
#define sensor_l_trig 12

#define sensor_f_echo 8
#define sensor_f_trig 7

#define sensor_r_echo 2
#define sensor_r_trig 4

#define ENA 11
#define ENB 3

#define IN_A_1 10
#define IN_A_2 9

#define IN_B_1 6
#define IN_B_2 5


int rd=10;
int ld=10;
int fd=15;
int dt=30;

int MAX_DISTANCE=500;
int offset_x=0;
int offset_y=100;


NewPing sonar_left(sensor_l_trig, sensor_l_echo, MAX_DISTANCE);
NewPing sonar_right(sensor_r_trig, sensor_r_echo, MAX_DISTANCE);
NewPing sonar_forward(sensor_f_trig, sensor_f_echo, MAX_DISTANCE);

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
  int df=sonar_forward.ping_cm();
  int dr=sonar_right.ping_cm();
  int dl=sonar_left.ping_cm();
  Serial.print(df);
  Serial.print(" ");
  Serial.print(dl);
  Serial.print(" ");
  Serial.print(dr);
  Serial.println(" ");
  
  if(dr<rd){
    left();
    delay(10*dt);
  }
  else if(dl<ld){
    right();
    delay(10*dt);
  }
  else if(df<fd){
  //  backward();
  //  delay(dt*40);
    int flag=1;
    int c=0;
    while(df<fd){
      df=sonar_forward.ping_cm();
      dr=sonar_right.ping_cm();
      dl=sonar_left.ping_cm();
      if(dl<ld && flag==1){
        c++;
        if(c==20){
          flag=0;
        }
      }
      if(flag=1){
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
