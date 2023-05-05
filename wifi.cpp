#include "wifi.h"

String dat="";
const char* ssidd = "Aquaphoton";
const char* passwordd = "Aqua2023";
WebServer server(80);
void Recieve(String x)
{
  dat=x;
}

void handleRoot() {
  String html = " <meta http-equiv='refresh' content='1'><h1>Hello from Esp:</h1><p>";
  html += dat;
  html += "</p>";
  server.send(200,"text/html", html);
}

void handleAbout() {
  server.send(200, "text/html", "<h1>About page</h1><p>This is the about page.</p>");
}

void Server_init(void){

  Serial.begin(115200);
  WiFi.begin(ssidd, passwordd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  server.on("/", handleRoot);
  
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP() );
}
void handle_client(void){
server.handleClient();
}
