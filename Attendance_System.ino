const char *password = "****";

 
#include <SPI.h>
#include <MFRC522.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char *ssid = "Unknown";


// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

int buzzer = D1;
int led = D0;

constexpr uint8_t RST_PIN = D3;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = D4;     // Configurable, see typical pin layout above

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class


String tag;

void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  rfid.PCD_DumpVersionToSerial();

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

// Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 Serial.print("Connected!");
  
// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  timeClient.setTimeOffset(16200);
}

void loop() {
  
  if (rfid.PICC_IsNewCardPresent() and rfid.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      tag += rfid.uid.uidByte[i];
    }
    Serial.println(tag);
    
    timeClient.update();
    String formattedTime  = timeClient.getFormattedTime();
    char hour[3] = {formattedTime[0],formattedTime[1],'\n'};
    int h = atoi(hour);
    Serial.print("Time: ");
    Serial.println(h);
    if(h >= 9 and h <= 14){
      digitalWrite(led, HIGH);
      delay(3000);
    digitalWrite(led, LOW);
    }else{
      tone(buzzer, 1000);
      delay(3000);
      noTone(buzzer);
      
    }
    
    tag = "";
    // Halt PICC
    rfid.PICC_HaltA();
    // Stop encryption on PCD
    rfid.PCD_StopCrypto1();
  }
}
