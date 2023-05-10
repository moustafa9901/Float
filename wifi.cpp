#include "wifi.h"
#include "motor.h"

const char* ssidd = "Aquaphoton";
const char* passwordd = "Aqua2023";

String dat="";
String stt="";

WebServer server(80);
String signall="0";

void Recieve(String x)
{
 stt = get_state();
  dat=x;
}

void handleRoot() {
  String html = " <meta http-equiv='refresh' content='1'><style>h1{color: #0158a7;}</style><h1>Hello from Aquaphoton:</h1><h3>EX07<H3><h2>";
  html += stt;
  html += "</h2><p>";
  html += dat;
  html +="</p>";
  server.send(200,"text/html", html);
}

void handleAbout() {
  server.send(200, "text/html", "<h1>About page</h1><p>This is the about page.</p>");
}
void handleSignal() {
  signall = server.arg("signal");
  Serial.println("Received signal: " + signall);
  server.send(200, "text/plain", "Signal received");
}
void Server_init(void){
 
  Serial.begin(115200);
  WiFi.begin(ssidd, passwordd);
  
// if (WiFi.status() != WL_CONNECTED) {
//    if(startTime2==0){
//    startTime2=millis();
//  }
//  if (millis() - startTime2 > 15000 )
//    {
//      Serial.println("restarted");
//      ESP.restart(); 
//    } 
//    Serial.println("Connecting to WiFi...");
//  }
//  Serial.println("Connected to WiFi");

  server.on("/", handleRoot);
  server.on("/signal", handleSignal);
  
  server.begin();
  Serial.println("HTTP server started");
  Serial.println(WiFi.localIP() );
}

void handle_client(void){
  server.handleClient();
}
