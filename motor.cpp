#include <Arduino.h>
#include "wifi.h"
#include "motor.h"

#define DELAY_WHILE_FILLED 25000
#define DELAY_WHILE_EMPTY 100000

#define START_INTERVAL 120000

const int lsw1= 36 ;
const int lsw2= 34;
const int output1= 25;
const int output2= 26;
int start_time;
int state=0;

void motor_init(void) {
  start_time = millis();
  Serial.begin(115200);
  pinMode(lsw1,INPUT);
  pinMode(lsw2,INPUT);
  pinMode(output1,OUTPUT);
  pinMode(output2,OUTPUT);
  digitalWrite(output1,HIGH);
  digitalWrite(output2,LOW);
}

void fault_state(void){
  digitalWrite(output1,LOW);
  digitalWrite(output2,LOW);
  while(true){
    digitalWrite(2,!digitalRead(2));
    delay(500);
  }
}

void fill(void){
  digitalWrite(output1,LOW);
  digitalWrite(output2,HIGH); 
  if(digitalRead(lsw1) == LOW) state ++;
  if(state == 4) state = 0;
}

void wait_while_filled(void){
  digitalWrite(output1,LOW);
  digitalWrite(output2,LOW); 
  delay(DELAY_WHILE_FILLED);
  state ++;
  if(state == 4)state = 0;
}

void empty(void){
  digitalWrite(output1,HIGH);
  digitalWrite(output2,LOW); 
  if(digitalRead(lsw2) == LOW)state ++;
  if(state == 4)state = 0;
}

void wait_while_empty(void){
  digitalWrite(output1,LOW);
  digitalWrite(output2,LOW); 
  delay(DELAY_WHILE_EMPTY);
  state ++;
  if(state == 4)state = 0;
}

void motor_worker(void) {
  Serial.println(state);
  if (signall.compareTo("0") == 0 || millis() - start_time > START_INTERVAL){
    switch(state){
      
      case 0:fill() ; break;
      case 1:wait_while_filled() ; break;
      case 2:empty() ; break;
      case 3:wait_while_empty() ; break;
    }
  }
  
  else{
    digitalWrite(output1,LOW);
    digitalWrite(output2,LOW); 
  }
}
int get_state(void)
{
  return(state);
}
