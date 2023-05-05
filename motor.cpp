#include <Arduino.h>
const int lsw1= 36 ;
const int lsw2= 34;
const int output1= 25;
const int output2= 26;
bool clicked1;
bool clicked2;
int period = 5000;
unsigned long time_now = 0;
int lsw;
void motor_init(void) {
Serial.begin(115200);
pinMode(lsw1,INPUT);
pinMode(lsw2,INPUT);
pinMode(output1,OUTPUT);
pinMode(output2,OUTPUT);
digitalWrite(output1,HIGH);
digitalWrite(output2,LOW);
clicked1=0;
clicked2=0;
}

int state = 0;
void fault_state(void){
  digitalWrite(output1,LOW);
  digitalWrite(output2,LOW);
  while(true){
    digitalWrite(2,!digitalRead(2));
    delay(500);
  }
}
void fill(void){
   Serial.println("fill");
//  Serial.println(digitalRead(output1));
//  Serial.println(digitalRead(output2));
  digitalWrite(output1,LOW);
  digitalWrite(output2,HIGH); 
  if(digitalRead(lsw1) == LOW)state ++;
//  if(digitalRead(lsw2) == LOW)fault_state();
  if(state == 4)state = 0;
}
void wait_while_filled(void){
     Serial.println("wait fill");
digitalWrite(output1,LOW);
digitalWrite(output2,LOW); 
  delay(25000);
  state ++;
  if(state == 4)state = 0;
}
void empty(void){
     Serial.println("empty");

  digitalWrite(output1,HIGH);
  digitalWrite(output2,LOW); 
  if(digitalRead(lsw2) == LOW)state ++;
//  if(digitalRead(lsw1) == LOW)fault_state();
  if(state == 4)state = 0;
}
void wait_while_empty(void){
     Serial.println("wait empty");
digitalWrite(output1,LOW);
digitalWrite(output2,LOW); 
  delay(60000);
  state ++;
  if(state == 4)state = 0;
}

void motor_worker(void) {
//  Serial.println("activated");
//  Serial.println(digitalRead(output1));
//  Serial.println(digitalRead(output2));
//  if(digitalRead(lsw1) == HIGH )
//  {
//    clicked1=0;
//  }
//   if(digitalRead(lsw2) == HIGH ){
//    clicked2=0;
//  }
//  
//
//if (digitalRead(lsw1) == LOW  and clicked1==0)
//{
//  clicked1=1;
//  Serial.println("deactivated");
//  digitalWrite(output1,LOW);
//  digitalWrite(output2,LOW);
//  delay(25000);
//  digitalWrite(output1,HIGH);
//  digitalWrite(output2,LOW);  
//    
//  
//}
//if (digitalRead(lsw2) == LOW  and clicked2==0)
//{
//  clicked2=1;
//  Serial.println("deactivated");
//  digitalWrite(output1,LOW);
//  digitalWrite(output2,LOW);
//  delay(25000);
//  digitalWrite(output1,LOW);
//  digitalWrite(output2,HIGH);  
//    
//  
//}    

  switch(state){
    case 0:fill() ; break;
    case 1:wait_while_filled() ; break;
    case 2:empty() ; break;
    case 3:wait_while_empty() ; break;
  }
}
