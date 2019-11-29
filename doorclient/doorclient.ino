#include <SPI.h>
#include <MFRC522.h>

// need from RFID
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);

// status led
const int statLEDPin[2] = {
  24, // LED Red
  25  // LED Green 
};

void setup() {

  // init RFID
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  // init LED's
  for ( int i = 0; i < 2; i++ ) {
    pinMode( statLEDPin[i], OUTPUT );
    digitalWrite( statLEDPin[i], LOW );
  }

}

void loop() {
  
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

}
