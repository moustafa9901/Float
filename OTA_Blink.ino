#include "AquaOTA.h"
#include "wifi.h"
#include "RTC.h"
#include "motor.h"
//variabls for blinking an LED with Millis
const int led = 2; // ESP32 Pin to which onboard LED is connected
unsigned long previousMillis = 0;  // will store last time LED was updated
const long interval = 250;  // interval at which to blink (milliseconds)
int ledState = LOW;  // ledState used to set the LED
TaskHandle_t Task1;
TaskHandle_t Task2;
int datt;

void setup() {
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 


Serial.begin(115200);
Serial.println("Booting");
pinMode(led, OUTPUT);


}

void Task1code( void * pvParameters ){
  motor_init();
  for(;;){
  motor_worker();
  } 
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
AquaWIFI_Init();
AquaOTA_Init();
Server_init();
RTC_init();
for(;;){
 AquaOTA_Check();  
 String dat= RTC_worker();
 
 Recieve(dat);
 handleRoot();
 handle_client();
}
}


void loop() {

  }
