

#define BLYNK_TEMPLATE_ID "TMPL4hJdSCZMq" //BLYNK template id-je.
#define BLYNK_TEMPLATE_NAME "Quickstart Template" //BLYNK template neve. 
#define BLYNK_AUTH_TOKEN "pPLCSmDXJJ21DmE-FFWluIHokmPgfT9_" //BLYNK autentikációs token.

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 2          //  digitális pin.  


#define DHTTYPE DHT11     // DHT 11 tipusú modul.


DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// Wifi adatok
char ssid[] = "Remias_Link_2.4G"; 
char pass[] = "Dusnok#4_2";

// Ez a funkció minden másodpercben továbbítja az adatoktak a digitális pin-eken keresztül.
void sendSensor()
{
  float h = dht.readHumidity(); // szenzor adatok beolvasása.
  float t = dht.readTemperature();  

  if (isnan(h) || isnan(t)) {
    Serial.println("Hiba a  DHT11 sensor olvasása közben!");
    return;
  }
 
  Blynk.virtualWrite(V5, h); // adatok kiírása a digitális pin-re.
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  // Debug konzolra való kiírás.
  Serial.begin(9600);
	//BLYNK elindítása 
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();

 
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

