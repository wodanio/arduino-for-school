#include <Arduino_JSON.h>

const int inputPin[3] = {
  8,  // Left
  9,  // Center
  10  // Right
};

const int triggerPin = 7;
const int echoPin = 6;

int dauer = 0;
int entfernung = 0;

void setup() {
  
  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);

  for ( int i = 0; i < 3; i++) {
    pinMode( inputPin, INPUT );
  }

  pinMode( triggerPin, OUTPUT );
  pinMode( echoPin, INPUT );
  
}

void loop() {

  JSONVar data;
  
  for ( int i = 0; i < 3; i++) {
    if ( digitalRead( inputPin[i] ) == HIGH )
      data[i] = true;
    else data[i] = false;
  }
  
  digitalWrite( triggerPin, HIGH );
  delay(10);
  digitalWrite( triggerPin, LOW );
  dauer = pulseIn( echoPin, HIGH );
  data[3] = round( ( dauer / 2 ) * 0.03432 );

  String jsondata = JSON.stringify( data );

  Serial.println( jsondata );
  Serial1.println( jsondata );
  

  // read from port 0, send to port 1:
  /*if (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(inByte);
  }*/

}
