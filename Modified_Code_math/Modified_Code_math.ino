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


int rd=10;
int ld=10;
int fd=15;
int dt=15;

int MAX_DISTANCE=500;
int offset_x=0;
int offset_y=100;

float ratio=float(242)/float(255);

NewPing sonar_left(sensor_trig, sensor_l_echo, MAX_DISTANCE);
NewPing sonar_right(sensor_trig, sensor_r_echo, MAX_DISTANCE);
NewPing sonar_forward(sensor_trig, sensor_f_echo, MAX_DISTANCE);

float vel(int reading){
  return 28.99*(0.001);
}

float omega(int reading){
  return 105.07*(0.001);
}

void stationary(){
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,LOW);
}

void backward(int voltage,float distance=0){
  analogWrite(ENA,ratio*voltage);
  analogWrite(ENB,voltage);
  float t=distance/vel(voltage);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,HIGH);
  digitalWrite(IN_B_2,LOW);

  if (distance!=0){
    delay(t);
    stationary();
  }
}

void forward(int voltage,float distance=0){
  analogWrite(ENA,ratio*voltage);
  analogWrite(ENB,voltage);
  float t=distance/vel(voltage);
  
  digitalWrite(IN_A_1,LOW);
  digitalWrite(IN_A_2,HIGH);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);
  
  if (distance!=0){
    delay(t);
    stationary();
  }
}

void right(int voltage,float angle=0){
  analogWrite(ENA,ratio*voltage);
  analogWrite(ENB,voltage);
  float t=angle/omega(voltage);
  
  digitalWrite(IN_A_1,HIGH);
  digitalWrite(IN_A_2,LOW);

  digitalWrite(IN_B_1,LOW);
  digitalWrite(IN_B_2,HIGH);

  if (angle!=0){
    delay(t);
    stationary();
  }
  
}

void left(int voltage,float angle=0){
  analogWrite(ENA,ratio*voltage);
  analogWrite(ENB,voltage);
  float t=angle/omega(voltage);
  
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
  Serial.begin(9600);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);

  pinMode(IN_A_1,OUTPUT);
  pinMode(IN_A_2,OUTPUT);

  pinMode(IN_B_1,OUTPUT);
  pinMode(IN_B_2,OUTPUT);
  
}
  
int offx=100;
int offy=100;

int state=1;
int dir=0;
float angleoff=0;

void dist_update(int distance){
  if (state==1){
    offy=offy-distance;
  }
  else if(state==2){
    offx=offx-distance;
  }
  else if(state==3){
    offx=offx+distance;
  }
  else{
    offy=offy+distance;
  }
}

void update_dir(int dir){
  if (dir==0){
    return;
  }
  else if(dir==1){
    if (state==1){
      state=3;
    }
    else if(state==2){
      state=1;
    }
    else if(state==3){
      state=4;
    }
    else if(state==4){
      state=2;
    }
  }
  else if(dir==2){
    if (state==1){
      state=2;
    }
    else if(state==2){
      state=4;
    }
    else if(state==3){
      state=1;
    }
    else if(state==4){
      state=3;
    }
  }
  else if(dir=3){
    state=5-state; 
  }
}

bool traceback(){
  if(offy>15 || offy<-15){
    if(offy>0){
      change_to_dir(1);
      return true;
    }
    else{
      change_to_dir(4);
      return true;
    }
  }
  else if(offx>15 || offx<-15){
    if(offx>0){
      change_to_dir(2);
      return true;
    }
    else{
      change_to_dir(3);
      return true;
    }
  }
  return false;
}

bool runner=true;

void change_to_dir(int dir){
  if(dir==1){
    if(state==1){
      return;
    }
    else if(state==2){
      left(255,90);
    }
    else if(state==3){
      right(255,90);
    }
    else{
      right(255,180);
    }
    state=1;
  }
  if(dir==2){
    if(state==1){
      right(255,90);
    }
    else if(state==2){
      return;
    }
    else if(state==3){
      right(255,180);
    }
    else{
      left(255,90);
    }
    state=2;
  }
  if(dir==3){
    if(state==1){
      left(255,90);
    }
    else if(state==2){
      left(255,180);
    }
    else if(state==3){
      return;
    }
    else{
      right(255,90);
    }
    state=3;
  }
  if(dir==4){
    if(state==1){
      right(255,180);
    }
    else if(state==2){
      right(255,90);
    }
    else if(state==3){
      left(255,90);
    }
    else{
      return;
    }
    state=4;
  }
}

int p=0;
float time_stamp=millis();
void loop() {
  while(runner){
    int df=sonar_forward.ping_cm();
    int dr=sonar_right.ping_cm();
    int dl=sonar_left.ping_cm();
    Serial.print(df);
    Serial.print(" ");
    Serial.print(dr);
    Serial.print(" ");
    Serial.println(dl);
    Serial.println(p);
    if(df<fd && p++>8){
      backward(255,7);
      update_dir(3);
      dist_update(7);
      update_dir(3);
      int flag1=0;
      int flag2=0;
      int firstIter=1;
      while(df<(fd+15)){
        df=sonar_forward.ping_cm();
        dr=sonar_right.ping_cm();
        dl=sonar_left.ping_cm();
        if(firstIter){
          if(dl>dr){
            left(255);
            delay(dt);
            angleoff=angleoff+omega(255)*dt;
            flag1=1;
            if(flag2==1){
              firstIter=0;
              flag2=0;
            }
            dir=1;
          }
          else{
            right(255);
            delay(dt);
            angleoff=angleoff-omega(100)*dt;
            flag2=1;
            if(flag1==1){
              firstIter=0;
              flag1=0;
            }
            dir=2;
          }
        }
        else{
          if(flag1==1){
            left(255,90-angleoff);
            dir=1;
          }
          else{
            right(255,90+angleoff);
            dir=2;
          }
        }
      }
    }
    
    else if(dl<ld){
      right(255);
      delay(dt);
    }

    if(dr<rd){
      left(255);
      delay(dt);
    }
    
    else{
      update_dir(dir);
      dir=0;
      forward(255);
      delay(dt);
      dist_update(10);
      angleoff=0;
    //  runner=traceback();
      if(millis()-time_stamp>1000){
      p=0;
      time_stamp=millis();
      }
    }
  }
}
