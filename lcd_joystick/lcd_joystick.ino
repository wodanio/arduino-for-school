#include <LiquidCrystal.h>
#include <Arduino_JSON.h>

#define startPotValue 1
#define endPotValue 1020
#define disPotValues 340

#define curPositionMin 1
#define curPositionXMax 20
#define curPositionYMax 4

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*const int inputPin[4] = {
  33, // Left
  35, // Up
  34, // Down
  32 // Right
};*/

const int inputVR[2] = {
  8,  // VR x
  9   // VR y
};

int curPosition[2] = {
  0,  // X-Koordinate
  0   // Y-Koordinate
};

int eventCache[2] = {
  0,  // VR x
  0   // VR y
};

int newValuesForPrint[2] = {
  0,  // VR x
  0   // VR y
};

void setup() {
  
  // initialize both serial ports
  Serial.begin(9600);

  /*for ( int i = 0; i < 4; i++ ) {
    pinMode( inputPin[ i ], INPUT );
  }*/

  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);

  setCurPosition( 0, 0 );

}

void loop() {
  
  int vrX = transformPotValue( smoothPotValue( analogRead( inputVR[0] ) ) ),
      vrY = transformPotValue( smoothPotValue( analogRead( inputVR[1] ) ) );

  manageKeyEvent( "x", vrX );
  manageKeyEvent( "y", vrY );

  Serial.println(" :end");

  setCurPosition( newValuesForPrint[ 0 ], newValuesForPrint[ 1 ] );

  delay( 100 );
  
}

int smoothPotValue ( int value ) {

  // INT -> DOUBLE | die letze Stelle der Zahl hinter das Komma bringen
  double newValue = value * 10E-2;

  // auf ganze Zahlen runden
  newValue = round( newValue );

  // die erste 0 hinter dem Komma -> vor das Komma
  newValue = newValue * 10;

  // DOUBLE -> INT | return
  return (int) newValue;
}

int transformPotValue ( int value ) {

  int returnAbleValue;

  // Value start on 1 def(startPotValue) up to 1020 def(endPotValue)

  if ( value >= ( endPotValue - disPotValues ) )                            // Joystick's Position Bottom
    returnAbleValue = 3;

  if ( value >= disPotValues && value <= ( endPotValue - disPotValues ) )   // Joystick's Position Center
    returnAbleValue = 2;

  if ( value <= disPotValues )                                              // Joystick's Position Top
    returnAbleValue = 1; 

  return returnAbleValue;
}

int transformCurPostionValue ( int acKey, int thisPosition, int maxPosition ) {

  // transform cursor Position with acKey
  if ( acKey == 1 )
    thisPosition--;
  else if ( acKey == 3 )
    thisPosition++;

  // filter new cursor Position with min and max values
  if ( thisPosition > maxPosition )
    thisPosition = curPositionMin;
  else if ( thisPosition < curPositionMin )
    thisPosition = maxPosition;

  return thisPosition;
}

void manageKeyEvent ( char key, int acKey ) {

  /*int newCurPositionsX = transformCurPostionValue( xAc, curPosition[0], curPositionXMax ),
      newCurPositionsY = transformCurPostionValue( yAc, curPosition[1], curPositionYMax );

  setCurPosition( newCurPositionsX, newCurPositionsY );*/

  int keyNum    = ( ( key == "x" ) ? 0 : 1 );

  if ( acKey != eventCache[ keyNum ] ) {
    
    int newValue  = transformCurPostionValue( acKey, curPosition[ keyNum ], ( ( key == "x" ) ? curPositionXMax : curPositionYMax ) );
    newValuesForPrint[ keyNum ] = newValue;

    Serial.print( " | " );
    Serial.print( keyNum );
    Serial.print( " New Value: " );
    Serial.print( newValue );

    eventCache[ keyNum ] = acKey;
  }
    
  
  return;
}

void setCurPosition ( int x, int y ) {
  if ( x <= curPositionMin || x >= curPositionXMax || y <= curPositionMin || y >= curPositionYMax )
    return;

  curPosition[0] = x;
  curPosition[1] = y;

  lcd.setCursor( x, y );
  lcd.write( "+" );

  return;
}
