#ifndef WIFI_H
#define WIFI_H

#include <WebServer.h>
void handleRoot();
void handleAbout() ;
void handle_client(void);
void Server_init(void);
void Recieve(String x);
extern String signall;

#endif
