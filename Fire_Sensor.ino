#define BLYNK_TEMPLATE_ID "TMPLnLdAwkxT"
#define BLYNK_TEMPLATE_NAME "Temperature Control Fan"
#define BLYNK_AUTH_TOKEN "ssPeLh3IDYuoOylxG_4FLAjF4_R3-u8u"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define Buzzer D5
#define Fire_analog A0
#define Fire_digital 10

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi Note 9 Pro Max";
char pass[] = "12345678";

void setup() {
  Serial.begin(115200);
  pinMode(Buzzer, OUTPUT);      
  pinMode(Fire_digital, INPUT);
  Blynk.begin(auth, ssid , pass );
}
void loop() {
  Blynk.run();
  int firesensorAnalog = analogRead(Fire_analog);
  int firesensorDigital = digitalRead(Fire_digital);

  Serial.print("Fire Sensor: ");
  Serial.print(firesensorAnalog);
  Serial.print("\t");
  Serial.print("Fire Class: ");
  Serial.print(firesensorDigital);
  Serial.print("\t");
  Serial.print("\t");
  
  if (firesensorAnalog < 100) {
    Serial.println("Fire");
    digitalWrite (Buzzer, HIGH) ; //send tone
    delay(1000);
    digitalWrite (Buzzer, LOW) ;  //no tone
    Blynk.logEvent("fire_alert","Fire Detected Take Necessary Actions");
  }
  else {
    Serial.println("No Fire");
  }
  delay(100);
}
