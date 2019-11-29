
int ledPin = 7;
int delayTime = 500;

void setup() {
  // put your setup code here, to run once:

  pinMode( 7, OUTPUT );

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite( 7, HIGH );
  delay(delayTime);
  digitalWrite( 7, LOW );
  delay(delayTime);

}
