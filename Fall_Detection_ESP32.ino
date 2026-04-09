#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <MAX30105.h>
#include <heartRate.h>
#include <TinyGPS++.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

const int BUZZER_PIN = 18;
const int VOICE_PIN = 19;   
const int BUTTON_PIN = 5;  
const int MPU_ADDR = 0x68;
#define RXD2 16
#define TXD2 17

const char* ssid = "Galaxy A35 5G 969A";
const char* password = "password";
const char* apiKey = "o.GhPIdzxSNcJYOntgS63EORIDR8GVOuqH";

float FALL_THRESHOLD = 1.5; 

TinyGPSPlus gps;
MAX30105 particleSensor;

const byte RATE_SIZE = 4; 
byte rates[RATE_SIZE]; 
byte rateSpot = 0;
long lastBeat = 0; 
int beatAvg = 0;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
  
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(VOICE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  digitalWrite(VOICE_PIN, LOW);

  // WiFi Connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if(WiFi.status() == WL_CONNECTED) Serial.println("\n[WIFI CONNECTED]");
  else Serial.println("\n[WIFI TIMEOUT] Continuing to sensors...");

  Wire.begin(21, 22);
  Wire.setClock(400000);

  // MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); Wire.write(0);
  if (Wire.endTransmission() != 0) {
    Serial.println("MPU6050 NOT FOUND!");
  }

  // MAX30105
  if (particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    particleSensor.setup(); 
    particleSensor.setPulseAmplitudeRed(0x24); 
    particleSensor.setPulseAmplitudeIR(0x24);
  }
  
  Serial.println("[SYSTEM READY]");
}

void loop() {
  // GPS
  while (Serial2.available() > 0) gps.encode(Serial2.read());

  // Heart Rate
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    float bpm = 60 / (delta / 1000.0);
    if (bpm < 255 && bpm > 20) {
      rates[rateSpot++] = (byte)bpm; 
      rateSpot %= RATE_SIZE; 
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++) beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  //(MPU6050)
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  if (Wire.available() >= 6) {
    int16_t rawX = Wire.read() << 8 | Wire.read();
    int16_t rawY = Wire.read() << 8 | Wire.read();
    int16_t rawZ = Wire.read() << 8 | Wire.read();
    
    float AccX = (float)rawX / 16384.0;
    float AccY = (float)rawY / 16384.0;
    float AccZ = (float)rawZ / 16384.0;
    float totalAcc = sqrt(AccX*AccX + AccY*AccY + AccZ*AccZ);

    // G-Force
    static unsigned long lastPrint = 0;
    if (millis() - lastPrint > 500) {
      Serial.print("G-Force: "); Serial.println(totalAcc);
      lastPrint = millis();
    }

    if (totalAcc > FALL_THRESHOLD) {
      Serial.println("!!! FALL DETECTED !!!");
      handleFallSequence();
    }
  }
  
  delay(10); 
}

void handleFallSequence() {
  // ISD1820
  Serial.println("Triggering Voice...");
  digitalWrite(VOICE_PIN, HIGH);
  delay(1000); 
  digitalWrite(VOICE_PIN, LOW);

  Serial.println("Voice Alert Started. 15s to press button...");

  unsigned long startTimer = millis();
  bool safe = false;

  while (millis() - startTimer < 15000) {
    // SOS Beep pattern
    digitalWrite(BUZZER_PIN, (millis() % 500 < 250)); 

    if (digitalRead(BUTTON_PIN) == LOW) { // Button Pressed
      safe = true;
      break;
    }
    delay(5);
  }

  digitalWrite(BUZZER_PIN, LOW);

  if (safe) {
    Serial.println("User marked as SAFE.");
    delay(2000); 
  } else {
    Serial.println("Timeout reached. Sending SOS!");
    sendAlert();
  }
}

void sendAlert() {
  if (WiFi.status() != WL_CONNECTED) return;

  String lat = gps.location.isValid() ? String(gps.location.lat(), 6) : "0.0";
  String lng = gps.location.isValid() ? String(gps.location.lng(), 6) : "0.0";
  String mapUrl = "http://maps.google.com/maps?q=" + lat + "," + lng;
  String msg = "EMERGENCY: Fall detected! BPM: " + 
  String(beatAvg) + " Location: https://maps.app.goo.gl/5C2GZSB8webAT3y97 ";
  WiFiClientSecure client;
  client.setInsecure(); 
  HTTPClient http;
  
  if (http.begin(client, "https://api.pushbullet.com/v2/pushes")) {
    http.addHeader("Access-Token", apiKey);
    http.addHeader("Content-Type", "application/json");
    String payload = "{\"type\": \"note\", \"title\": \"SOS\", \"body\": \"" + msg + "\"}";
    http.POST(payload);
    http.end();
  }
}
