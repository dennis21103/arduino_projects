// Example testing sketch for various DHT humidity/temperature sensors written by ladyada
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#define DHTPIN 4     // Digital pin connected to the DHT sensor (PIN 4 = D2)
#define PIN_RELAY 5    // Определяем пин, используемый для подключения реле (PIN 5 = D1, 3,3 вольт - разомкнуто, 0 вольт - замкнуто)
//#define ADC A0         //Аналоговый датчик CO2 на порту А0

unsigned long timing; // Переменная для хранения точки отсчета
unsigned long timing2; // Переменная для хранения точки отсчета
float OneMinTemp[30]; // массив температурных значений раз в 2 сек
float OneMinHum[30]; //массив значений влажности раз в 2 сек
float FiveMinTemp[5]; // массив температурных значений раз в 1 мин
float FiveMinHum[5]; //массив значений влажности раз в 1мин
int i = 0; //счетчик
int j = 0; //счетчик
int k = 0; //счетчик для массивов
int timer = 0; //счетчик времени от запуска программы
bool relay1 = 0; // 1 - розетка выключена, 0 - розетка включена 
float t = 0 ; // переменная температуры
float h = 0; // переменная влажности
float Tavg1 = 0; // переменная средней температуры за 1 мин
float Havg1 = 0; // переменная средней влажности за 1 мин
float Tavg5 = 0; // переменная средней температуры за 5 мин
float Havg5 = 0; // переменная средней влажности за 5 мин
float v400 = 2; //уровни напряжений для 400ppm (улица) v400 > v40000
float v40000 = 0;
float buffer = 0;
float buffer1 = 0;
//float v400 = 4.535/10; //уровни напряжений для 400ppm (минимум)
//float v40000 = 3.206/2; //уровни напряжений для 4000ppm (максимум)

#include "DHT.h"
#include "MG811.h"
#include "denWIFI.h"  //внутри: #include "denWIFIcred.h" и #include "denWIFIpage.h"
MG811 mySensor = MG811(A0); // Analog input A0

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE, 30);

void setup() {
      Serial.begin(115200);
      Serial.println(F("DHT22 test! and MG811 CO2 Sensor"));
  for ( j=0; j<30; j++){
      OneMinTemp[j]=0;
       OneMinHum[j]=0;
  }
  for ( j=0; j<5; j++){
      FiveMinTemp[j]=0;
      FiveMinHum[j]=0;
  }
      pinMode(PIN_RELAY, OUTPUT); // Объявляем пин реле как выход
      pinMode(0, LOW);
      digitalWrite(PIN_RELAY, LOW); // Включаем реле - посылаем низкий сигнал (HIGH выключено-разомкнуто)
      dht.begin();
     // Calibration is not done in this examples - use default value
    // mySensor.calibrate() 
      mySensor.begin(v400, v40000);
      startup();
}

float temp (){
   // Wait a few seconds between measurements.
  //delay(2000);

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

  // Compute heat index in Fahrenheit (the default)
//  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
//  float hic = dht.computeHeatIndex(t, h, false);

/**  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);          //отладочная информация
  Serial.println(F("*C "));**/ 
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));
}

float AverageHumidity1min(int i){
   Havg1 = 0;
     for ( j=0; j<30; j++){ 
      Havg1 = Havg1 + OneMinHum[j];
                             }
   Havg1 = Havg1/30;
   FiveMinHum[i]=Havg1;
 //  Serial.print(F("Sredniyr znacheniya za 1 minyty Humidity: "));     //отладочная информация
 //  Serial.print(Havg1);                                               //отладочная информация
 //  Serial.print(F("%  Temperature: "));                               //отладочная информация
   return Havg1;
                        }

float AverageTemp1min(int i){
   Tavg1 = 0;
    for ( j=0; j<30; j++){ 
      Tavg1 = Tavg1 + OneMinTemp[j]; 
                            }
   Tavg1 = Tavg1/30;
   FiveMinTemp[i]=Tavg1;
 // Serial.print(Tavg1);       //отладочная информация
 // Serial.println(F("*C "));  //отладочная информация
  return Tavg1;
                    }
float CO2(){
  buffer = mySensor.raw();
  buffer1 = mySensor.read();
/**    Serial.print("Raw voltage: ");
    Serial.print(mySensor.raw());
    Serial.print("V, C02 Concetration: "); //отладочная информация
    Serial.print(mySensor.read());
    Serial.println(" ppm");**/
           }

void loop() {
  mainwifi();
  if (millis() - timing > 2100){ // Вместо 2000 подставьте нужное вам значение паузы 
  timing = millis();
  temp();
  CO2();
  OneMinTemp[k] = t;
  OneMinHum[k] = h;
  k=k+1;
  if ( i == 5 ) { 
    i=0; Tavg5 = 0; Havg5 = 0;
       for ( j=0; j<5; j++){
      Tavg5 = Tavg5 + FiveMinTemp[j];
      Havg5 = Havg5 + FiveMinHum[j];
  }
  Tavg5 = Tavg5/5; Havg5 = Havg5/5;
  /** Serial.print(F("Sredniyr znacheniya za 5 minyt Humidity: "));
   Serial.print(Havg5);
   Serial.print(F("%  Temperature: "));                               //отладочная информация
   Serial.print(Tavg5);
   Serial.println(F("*C "));**/
               }
  if (k > 30){
        k = 0;
        AverageHumidity1min(i);
        AverageTemp1min(i);
        CO2();
        i = i + 1;    
            } 
  timer = timer + 2;
  if ( h > 65 ){ 
       digitalWrite(PIN_RELAY, HIGH);
       relay1 = 1;
      if ( relay1 !=0 and h < 48){ // 1 - розетка выключена, 0 - розетка включена 
           digitalWrite(PIN_RELAY, LOW);
           relay1 = 0; 
                                 } 
               }
 // Serial.print (timer);             //отладочная информация
 // Serial.println (" seconds");      //отладочная информация
 }
}
