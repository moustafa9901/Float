#include "AquaOTA.h"
#include "wifi.h"
#include "RTC.h"
#include "motor.h"

#define Blink_LED 2
#define INTERVAL 10000

hw_timer_t *Blink_Timer = NULL;

void IRAM_ATTR Blink_Timer_ISR(){
  digitalWrite(Blink_LED, !digitalRead(Blink_LED));
}

unsigned long long currentMillis=0;
unsigned long long previousMillis=0;

TaskHandle_t motor_task;
//TaskHandle_t wifi_task;

int datt;



void setup() {
  
  pinMode(Blink_LED, OUTPUT);
  Blink_Timer = timerBegin(1, 80, true);
  Serial.begin(115200);
  timerAttachInterrupt(Blink_Timer, &Blink_Timer_ISR, true);
  timerAlarmWrite(Blink_Timer, 1000000, true);
  timerAlarmEnable(Blink_Timer); 

  motor_init();

  xTaskCreatePinnedToCore(
                    motor_task_code,   /* Task function. */
                    "motor_task",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &motor_task,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */                  
  delay(500); 
  
  AquaWIFI_Init();
  Server_init();
  RTC_init();

//  create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
//  xTaskCreatePinnedToCore(
//                    wifi_task_code,   /* Task function. */
//                    "wifi_task",     /* name of task. */
//                    10000,       /* Stack size of task */
//                    NULL,        /* parameter of the task */
//                    1,           /* priority of the task */
//                    &wifi_task,      /* Task handle to keep track of created task */
//                    0);          /* pin task to core 1 */
//  delay(500); 

  Serial.begin(115200);
  Serial.println("Booting");
  
}

void motor_task_code( void * pvParameters ){
  
  for(;;){
    motor_worker();
  } 
}
//
//void wifi_task_code( void * pvParameters ){
void wifi_task_code(void){
    if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=INTERVAL)) {
      Serial.print(millis());
      Serial.println("Reconnecting to WiFi...");
      WiFi.disconnect();
      WiFi.reconnect();
      previousMillis = currentMillis;
    }
     
    // AquaOTA_Check();  
    String dat= RTC_worker();
    Recieve(dat);
    handle_client();
  
}
//}
void loop() {
  wifi_task_code();
}
