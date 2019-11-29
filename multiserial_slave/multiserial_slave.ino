#include <LiquidCrystal.h>
#include <Arduino_JSON.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int lcdDelay = 1;

void setup() {
  
  // initialize both serial ports
  Serial.begin(9600);
  Serial1.begin(9600);

  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);

}

void loop() {

  // read from port 1, send to port 0:
  if (Serial1.available()) {

    String serialRead = Serial1.readStringUntil('\n');

    if ( lcdDelay == 15 ) {

      //Serial.println( serialRead );
      JSONVar data = JSON.parse( serialRead );

      if ( JSON.typeof(data) != "undefined" ) {
        Serial.println( serialRead );
        if ( serialRead == "$clear" ) {
          lcd.clear();
        } else {
  
          lcd.clear();
  
          lcd.setCursor(0, 0);
          lcd.print( "Button Left: " );
          lcd.print( ( data[0] ? "yes" : "no" ) );
          lcd.setCursor(0, 1);
          lcd.print( "Button Center: " );
          lcd.print( ( data[1] ? "yes" : "no" ) );
          lcd.setCursor(0, 2);
          lcd.print( "Button Right: " );
          lcd.print( ( data[2] ? "yes" : "no" ) );
          lcd.setCursor(0, 3);
          lcd.print( "Dist: " );
          lcd.print( data[3] );
          
        }
      }

      lcdDelay = 1;
    }
    lcdDelay++;

  }

}
