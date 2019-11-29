
const int comPin[4] = {
  7, // LED Grün 
  6, // LED Gelb
  5, // LED Rot
  4  // Sound
};
const int segPin[8] = {
    30,
  26, 32,
    24,
  28, 34,
    36, 38
};
const int pushDelay = 200;
const int soundDelay = 200;

void setup() {
  
  // init all com
  for (int i = 0; i < 4; i++) {
    pinMode( comPin[ i ], OUTPUT );
    digitalWrite( comPin[ i ], LOW );
  }
  // init seg
  for ( int i = 0; i < 8; i++ ) {
     pinMode( segPin[ i ], OUTPUT );
     digitalWrite( segPin[ i ], LOW );
  }

  // start Template 
  pushTemplate();

}

void loop() {

}

void pushTemplate () {
  int ledCount = 0;
  boolean dirUp = true;
  for ( int count = 9; count >= 1; count-- ) {
    useSeg( true, count, false );

    for ( int i = 0; i < 5; i++ ) {
      if ( ledCount == 3) {
        ledCount = 0;
        dirUp = true;
      }
      if ( ledCount < 0 ) {
        ledCount = 2; 
        dirUp = false;
      }

      useLED( ledCount );

      if ( dirUp )
        ledCount++;
      else
        ledCount--;
    }

    /*if ( !useNext ) {
      for ( int i = 0; i < 3; i++ ) // push LED's from Green to Red
        useLED( i );
      useNext = true;
    } else {
      for ( int i = 1; i > 0; i-- ) // push LED's from Red to Green
        useLED( i );
      delay( pushDelay * 2 );
      useNext = false;
    }*/
      
  }

  useSeg( true, 0, false );
  for (int i = 0; i < 4; i++) {
    digitalWrite( comPin[ i ], HIGH );
  }
  

  return;
}

void useSeg ( boolean stat, int number, boolean numd ) {
  if ( !stat ) {
    setSeg( false, false, false, false, false, false, false );
    digitalWrite( segPin[ 7 ], LOW );
  }
  
  // switch to new number
  switch ( number ){
    case 0:
      setSeg( true, true, true, false, true, true, true );
      break;
    case 1:
      setSeg( false, false, true, false, false, true, false );
      break;
    case 2:
      setSeg( true, false, true, true, true, false, true );
      break;
    case 3:
      setSeg( true, false, true, true, false, true, true );
      break;
    case 4:
      setSeg( false, true, true, true, false, true, false );
      break;
    case 5:
      setSeg( true, true, false, true, false, true, true );
      break;
    case 6:
      setSeg( true, true, false, true, true, true, true );
      break;
    case 7:
      setSeg( true, false, true, false, false, true, false );
      break;
    case 8:
      setSeg( true, true, true, true, true, true, true );
      break;
    case 9:
      setSeg( true, true, true, true, false, true, true );
      break;
    default:
      break;
  }

  if ( numd )
    digitalWrite( segPin[ 7 ], HIGH );
  else
    digitalWrite( segPin[ 7 ], LOW );

  return;
}
void setSeg ( boolean a, boolean b, boolean c, boolean d, boolean e, boolean f, boolean g ) {
  boolean stats[7] = { a, b, c, d, e, f, g };
  for ( int i = 0; i < 7; i++ )
    if ( stats[ i ] )
      digitalWrite( segPin[ i ], HIGH );
    else
      digitalWrite( segPin[ i ], LOW );
      
  return;
}

void useLED ( int giveComPin ) {

  digitalWrite( comPin[ giveComPin ], HIGH ); // LED i
  delay( pushDelay );
  digitalWrite( comPin[ giveComPin ], LOW );  // LED i

  return;
}

void pushSound () {

  digitalWrite( comPin[ 3 ], HIGH );
  delay( soundDelay );
  digitalWrite( comPin[ 3 ], LOW );

  return;
}
