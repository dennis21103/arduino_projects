// - Used libraries: 
// - DHT Sensor Library
// - Adafruit Unified Sensor Lib
// - MG811
// - Hardware in this project: Wemos D1 Mini with WiFi, CO2 sensor - MG811, Temp+Hum sensor - DHT22, solid-state relay 


#define DHTPIN 4     // Digital pin connected to the DHT sensor (PIN 4 = D2)
#define PIN_RELAY 5    // solid-state relay pin (PIN 5 = D1, 3,3v - open relay, 0v - close)
//#define ADC A0         // Analog sensor CO2 on А0 port

unsigned long timing; // variable for timer
unsigned long timing2; // variable for timer
float OneMinTemp[30]; // array of temperature values ​​every 2 sec
float OneMinHum[30]; // array of humidity values ​​every 2 sec
float FiveMinTemp[5]; // array of temperature values ​​every 1 min
float FiveMinHum[5]; // array of humidity values ​​every 1 min
int i = 0; // counter
int j = 0; // counter
int k = 0; // counter for arrays
int timer = 0; //time counter from program start
bool relay1 = 0; // 1 - socket off (relay open), 0 - socket on (relay close)
float t = 0 ; // variable for temperature
float h = 0; // variable for humidity
float Tavg1 = 0; // 1 min average temperature variable
float Havg1 = 0; // 1 min average humidity variable
float Tavg5 = 0; // 5 min average temperature variable
float Havg5 = 0; // 5 min average humidity variable
float v400 = 2; //voltage levels for 400ppm on CO2 sensor (outdoor, min) v400 > v40000, not calibrated (need calibrate)
float v40000 = 0;//voltage levels for 40000ppm on CO2 sensor (outdoor, min) v400 > v40000, not calibrated (need calibrate)
float buffer = 0;
float buffer1 = 0;
//
#include "DHT.h"
#include "MG811.h"
#include "WIFI.h"  //include library: #include "denWIFIcred.h" и #include "denWIFIpage.h"
MG811 mySensor = MG811(A0); // Analog input A0
//
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.
//
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
//
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE, 30);
//
void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 test! and MG811 CO2 Sensor"));
  for ( j = 0; j < 30; j++) {
    OneMinTemp[j] = 0;
    OneMinHum[j] = 0;
  }
  for ( j = 0; j < 5; j++) {
    FiveMinTemp[j] = 0;
    FiveMinHum[j] = 0;
  }
  pinMode(PIN_RELAY, OUTPUT); // Output mode pin for relay
  pinMode(0, LOW);
  digitalWrite(PIN_RELAY, LOW); // solid-state relay - close, Low level signal, socket on (HIGH level signal = relay open and socket be off)
  dht.begin();//functions from DHT library
  // Calibration is not done in this examples - use default value
  // mySensor.calibrate()
  mySensor.begin(v400, v40000); //functions from MG811 library
  startup(); //functions for start WiFi 
}

float temp () {
  // Wait a few seconds between measurements.
  //delay(2000); //not used because in loop use variable timing

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  :: h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  :: t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return 0;
  }
//--------- not interesting for me ---------------
  // Compute heat index in Fahrenheit (the default)
  //  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  //  float hic = dht.computeHeatIndex(t, h, false);
//---------------- for debug info -----------------------
  /*  Serial.print(F("Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.println(F("*C "));*/
/*//--------- not interesting for me ---------------
  //  Serial.print(f);
  //  Serial.print(F("°F  Heat index: "));
  //  Serial.print(hic);
  //  Serial.print(F("°C "));
  //  Serial.print(hif);
  //  Serial.println(F("°F"));*/
}

float AverageHumidity1min(int i) {
  Havg1 = 0;
  for ( j = 0; j < 30; j++) {
    Havg1 = Havg1 + OneMinHum[j];
  }
  Havg1 = Havg1 / 30;
  FiveMinHum[i] = Havg1;
/*//---------------- for debug info -----------------------
 *  Serial.print(F("Sredniyr znacheniya za 1 minyty Humidity: "));
 *  Serial.print(Havg1);
 *  Serial.print(F("%  Temperature: ")); */
  return Havg1;
}

float AverageTemp1min(int i) {
  Tavg1 = 0;
  for ( j = 0; j < 30; j++) {
    Tavg1 = Tavg1 + OneMinTemp[j];
  }
  Tavg1 = Tavg1 / 30;
  FiveMinTemp[i] = Tavg1;
  // Serial.print(Tavg1);       //for debug
  // Serial.println(F("*C "));  //for debug
  return Tavg1;
}
float CO2() {
  buffer = mySensor.raw();
  buffer1 = mySensor.read();
  /* //---------------- for debug info -----------------------   
   *   Serial.print("Raw voltage: ");
   *  Serial.print(mySensor.raw());
   *   Serial.print("V, C02 Concetration: ");
   *   Serial.print(mySensor.read());
   *   Serial.println(" ppm");*/
}

void loop() {
  mainwifi();
  if (millis() - timing > 2100) { // pause for entering in cycle
    timing = millis();
    temp();
    CO2();
    OneMinTemp[k] = t;
    OneMinHum[k] = h;
    k = k + 1;
    if ( i == 5 ) {
      i = 0; Tavg5 = 0; Havg5 = 0;
      for ( j = 0; j < 5; j++) {
        Tavg5 = Tavg5 + FiveMinTemp[j];
        Havg5 = Havg5 + FiveMinHum[j];
      }
      Tavg5 = Tavg5 / 5; Havg5 = Havg5 / 5;
      
      /* //---------------- for debug info -----------------------
       * Serial.print(F("Sredniyr znacheniya za 5 minyt Humidity: "));
       * Serial.print(Havg5);
       * Serial.print(F("%  Temperature: "));
       * Serial.print(Tavg5);
       * Serial.println(F("*C "));*/
    }
    if (k > 30) {
      k = 0;
      AverageHumidity1min(i);
      AverageTemp1min(i);
      CO2();
      i = i + 1;
    }
    timer = timer + 2;
    if ( h > 65 ) {
      digitalWrite(PIN_RELAY, HIGH);
      relay1 = 1;
      if ( relay1 != 0 and h < 48) { // 1 - socket off, 0 - socket on
        digitalWrite(PIN_RELAY, LOW);
        relay1 = 0;
      }
    }
    // Serial.print (timer);             //for debug
    // Serial.println (" seconds");      //for debug
  }
}
