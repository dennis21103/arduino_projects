
/** To be able to flash through the network port,
 * you need to install the latest version of python
 * Download link: https://www.python.org/downloads/
**/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "WIFIcred.h"
#include "WIFIpage.h"
void startup(void){
  // preparing GPIOs
  ArduinoOTA.setHostname("ESP8266-00001"); // Name of network port for OTA
  //ArduinoOTA.setPassword((const char *)"0000"); // Password for flashing program over air
  ArduinoOTA.begin(); // Initialization OTA

  delay(100);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);
  
 
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
   Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
 
  //+++++++++++++++++++++++ START ----RESET for socket---- ++++++++++++++++++++
  server.on("/", [](){
    server.send(200, "text/html", webPage());
  });
  server.on("/socket1On", [](){
    digitalWrite(PIN_RELAY, LOW);
    server.send(200, "text/html", webPage());
    delay(100);
    
  });
  server.on("/socket1Off", [](){
    digitalWrite(PIN_RELAY, HIGH);
    server.send(200, "text/html", webPage());
    delay(100);
  });	
   //+++++++++++++++++++++++ END  ----RESET for socket---- ++++++++++++++++++++ 
  server.begin();
  Serial.println("HTTP server started");
}
 
void mainwifi(void){
  ArduinoOTA.handle(); Waiting flashing comm
  server.handleClient();
} 