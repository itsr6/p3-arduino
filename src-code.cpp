#include <ESP8266WiFi.h>

// Pin sensor suara (sesuaikan pin yang digunakan di esp 8266 anda)
const int soundSensorPin = D1; 

// Pin input relay (sesuaikan pin yang digunakan di esp 8266 anda)
const int relayPin = D5;       

int clapCount = 0;
unsigned long lastClapTime = 0;

//Sesuaikan nilai ini untuk menghindari pemicu yang salah(bisa juga mengatur potensio pada sensor)
unsigned long debounceDelay = 200; 

void setup() {
  Serial.begin(9600); //untuk esp8266 bisa menggunakan 9600 atau 115200
  pinMode(soundSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // pastikan keadaan awal relay NO (mati)
}

void loop() {
  int soundValue = digitalRead(soundSensorPin); //Membaca keluaran digital dari sensor suara

  if (soundValue == HIGH) {
    unsigned long currentTime = millis();
    if (currentTime - lastClapTime >= debounceDelay) {
      clapCount++;
      Serial.print("Clap detected #");
      Serial.println(clapCount);
      lastClapTime = currentTime;
      if (clapCount == 1) {
        //Tepuk tangan 1x untk menyalakan
        digitalWrite(relayPin, HIGH);
      } 
      else if (clapCount == 2) {
        //Tepuk tangan 2x untk mematikan
        digitalWrite(relayPin, LOW);
        clapCount = 0; // Reset clapCount
      }
    }
  }
}
