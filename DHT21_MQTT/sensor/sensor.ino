#include "DHT.h"
#include <ArduinoJson.h>

#define DHTPIN 2    // modify to the pin we connected
#define MQ_7 A0
 
#define DHTTYPE DHT21   // AM2301 
 
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
 Serial.begin(9600);
 Serial.println("DHTxx test!");
 dht.begin();
 
}
 
void loop()
{
 int var = analogRead(MQ_7);
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 String data = "";
 // check if returns are valid, if they are NaN (not a number) then something went wrong!
 if (isnan(t) || isnan(h))
 {
   Serial.println("Failed to read from DHT");
 }
 else
 {
   StaticJsonDocument<200> msgs;
   msgs["MQ7"] = var;
   msgs["h"] = h;
   msgs["t"] = t;
   serializeJson(msgs, Serial);
   Serial.println();
   delay(2000);
 }
}
