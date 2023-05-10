#include "RTC.h"

RTC_DS1307 rtc;

void RTC_init(void) {
  Wire.begin();
//  Serial.begin(115200);
  
  while(!rtc.begin()){
    Serial.print("RTC reboot");
  }

//   Uncomment the following line to set the time on the RTC module
//  rtc.adjust(DateTime(__DATE__, __TIME__));
}

String RTC_worker(void) {
  DateTime now = rtc.now();
  int hh=now.hour();
  int mm=now.minute();
  int ss=now.second();
  String dat=String(hh);
  dat+=":";
  dat+=String(mm);
  dat+=":";
  dat+=String(ss);
  return dat;
}
