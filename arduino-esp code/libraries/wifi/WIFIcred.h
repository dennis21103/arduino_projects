
/** Для возможности прошивки по сетевому порту,
 *  необходимо установить последнюю версию python 
 *  Скачать по ссылке: https://www.python.org/downloads/
**/

MDNSResponder mdns;

// Wi-Fi
const char* ssid = "Name wifi network here";
const char* password = "wifi password here";

byte arduino_mac[] = { 0x5C, 0xCF, 0x7F, 0xAB, 0x1D, 0xA4 };
IPAddress ip(192,168,1,212);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);