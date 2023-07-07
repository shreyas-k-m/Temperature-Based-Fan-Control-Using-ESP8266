#define BLYNK_TEMPLATE_ID "TMPLnLdAwkxT"
#define BLYNK_TEMPLATE_NAME "Temperature Control Fan"
#define BLYNK_AUTH_TOKEN "ssPeLh3IDYuoOylxG_4FLAjF4_R3-u8u"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"
#define DHTPIN D5     // Digital pin connected to the DHT sensor

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define FAN_PIN D2   // FAN RELAY
#define BUZZER_PIN D1   // Buzzer pin
WidgetLED FAN(V0);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi Note 9 Pro Max";
char pass[] = "12345678";

float humDHT = 0;
float tempDHT = 0;
int Val=0;

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println(F("DHT11 test!"));
  dht.begin();
  Blynk.begin(auth, ssid , pass );
}

BLYNK_WRITE(V3)
{
  Val = param.asInt(); // assigning incoming value from pin V3 to a variable

  Serial.print("The Threshhold value is: ");
  Serial.println(Val);
  Serial.println();
}

void loop() {
  
  Blynk.run();

  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humDHT = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempDHT = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humDHT) || isnan(tempDHT))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(tempDHT);
  Serial.print(F("°C "));
  Serial.println();
  Serial.print(F("Humidity: "));
  Serial.print(humDHT);
  Serial.print(F("%"));
  Serial.println();
  
  Serial.println("***********************");
  Serial.println();

  // Compare Threshold value from Blynk and DHT Temperature value.
  if (Val > tempDHT)
  {
    digitalWrite(FAN_PIN, HIGH);
    FAN.off();
    Serial.println("Fan Turned Off!!");
}
  else {
    digitalWrite(FAN_PIN, LOW);
    FAN.on();
    digitalWrite(BUZZER_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Fan Turned On");
  } 

  Blynk.virtualWrite(V1, tempDHT);
  Blynk.virtualWrite(V2, humDHT);
}
