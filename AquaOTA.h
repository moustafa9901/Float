#ifndef OTA_H
#define OTA_H

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

void AquaWIFI_Init(void);
void AquaOTA_Init(void);
void AquaOTA_Check(void);


#endif
