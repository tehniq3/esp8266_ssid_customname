// original https://yoursunny.com/t/2017/HTU21D-ESP8266-SSID/
// modificed by Nicu FLORICA (niq_ro) - http://www.arduinotehniq.com/
#include "DHT.h"
#define DHTPIN 14     // what pin we're connected - D5 (GPIO14)
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#include <ESP8266WiFi.h>
#include <PString.h>
#include <Streaming.h>
// Initialize DHT sensor for normal 16mhz Arduino
//DHT dht(DHTPIN, DHTTYPE);
// NOTE: For working with a faster chip, like an Arduino Due or Teensy, you
// might need to increase the threshold for cycle counts considered a 1 or 0.
// You can do this by passing a 3rd parameter for this threshold.  It's a bit
// of fiddling to find the right value, but in general the faster the CPU the
// higher the value.  The default for a 16mhz AVR is a value of 6.  For an
// Arduino Due that runs at 84mhz a value of 30 works.
// Example to initialize DHT sensor for Arduino Due:
DHT dht(DHTPIN, DHTTYPE, 11);


void
setup()
{
   Serial.begin(9600); 
  WiFi.disconnect();
  WiFi.persistent(false);
  WiFi.mode(WIFI_AP);
   dht.begin();
}

void
loop()
{
  char buf[32];
  PString out(buf, sizeof(buf));
//float t = random(100,350)/10.;
//float h = random(200,700)/10.;

  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
//out << 32.5 << "C " << 57.7 << "%";
out << t << "C " << h << "%";
  WiFi.softAP(out);
  delay(10000);
}
