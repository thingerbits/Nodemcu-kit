
#define _DEBUG_
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>
#include "DHT.h" 

#define DHTPIN D7 
#define DHTTYPE DHT11 

#define USERNAME "rahul98"
#define DEVICE_ID "nodeMCU"
#define DEVICE_CREDENTIAL "rahul1998"

#define SSID "Rahul's iPhone"
#define SSID_PASSWORD "0774480066"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);
  Serial.println();

   
 thing.add_wifi(SSID,SSID_PASSWORD);
//WiFi.begin("Peter's iPhone","*************");

Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP()); 
  
 dht.begin();

 

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis()); 

  thing["dht11"] >> [](pson& out)
  {
    // Add the values and the corresponding code
    out["humidity"] = dht.readHumidity();
    out["celsius"] = dht.readTemperature();
  };

}


  


void loop() {
  thing.handle();
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

    // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
}

void sendUptime()
{
  
  

}
