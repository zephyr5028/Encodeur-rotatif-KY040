/*
int pinA = 3;  // Connected to CLK on KY-040
int pinB = 4;  // Connected to DT on KY-040
int encoderPosCount = 0;
int pinALast;
int aVal;
boolean bCW;
bool debug= false;

void setup() {
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  /* Read Pin A
    Whatever state it's in will reflect the last position
  */
  /*
  pinALast = digitalRead(pinA);
  Serial.begin (9600);
}

void loop() {
  aVal = digitalRead(pinA);
  if (aVal != pinALast) { // Means the knob is rotating
    // if the knob is rotating, we need to determine direction
    // We do that by reading pin B.
    if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
      encoderPosCount ++;
      bCW = true;
    } else {// Otherwise B changed first and we're moving CCW
      bCW = false;
      encoderPosCount--;
    }
    if (debug) {
    Serial.print ("Rotated: ");
    if (bCW) {
      Serial.println ("clockwise");
    } else {
      Serial.println("counterclockwise");
    }
    Serial.print("Encoder Position: ");
    }
    Serial.println(encoderPosCount);

  }
  pinALast = aVal;
}
*/

// include <liquidcrystal.h>

//LiquidCrystal lcd(12, 11, 10, 8, 7,6,5);

// définition des pin pour le KY040
enum PinAssignments {
  encoderPinA = 2,   // right (DT)
  encoderPinB = 3,   // left (CLK)
  clearButton = 4    // switch (SW)
};

volatile unsigned int encoderPos = 0;  // un compteur
unsigned int lastReportedPos = 1;   // gestion du changement
static boolean rotating=false;      // gestion de l'anti-rebonds

// variable pour les routines d'interruption
boolean A_set = false;             
boolean B_set = false;
boolean A_change = false;
boolean B_change= false;

void setup() {
 // lcd.begin(20,4);
 // lcd.clear();
   Serial.begin (9600);

  pinMode(encoderPinA, INPUT_PULLUP); // utilisation du pullup
  pinMode(encoderPinB, INPUT_PULLUP); // utilisation du pullup
  pinMode(clearButton, INPUT_PULLUP); // utilisation du pullup
  // activation de l'interruption 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // activation de l'interruption 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);
}

void loop(){
  if (lastReportedPos != encoderPos) {
   // lcd.clear();
   // lcd.setCursor(0,0);
   // lcd.print("Index: ");
    Serial.print("Index: ");
    //lcd.print(encoderPos, DEC);
    Serial.print(encoderPos, DEC);
     Serial.print("     A :");
    lastReportedPos = encoderPos;
   // lcd.setCursor(0,1);
   // lcd.print(digitalRead(encoderPinA));
  //  lcd.print(digitalRead(encoderPinB));
    Serial.print(digitalRead(encoderPinA));
    Serial.print("   B :");
    Serial.println(digitalRead(encoderPinB));
    //lcd.print(digitalRead(clearButton));
  }
  //  lcd.setCursor(0,1);
   // lcd.print(digitalRead(encoderPinA));
   // lcd.print(digitalRead(encoderPinB));
   // lcd.print(digitalRead(clearButton));
   // Serial.print(digitalRead(encoderPinA));
   // Serial.print(" ");
    //Serial.println(digitalRead(encoderPinB));
   
  if (digitalRead(clearButton) == LOW )  {
    encoderPos = 0;
    A_change = false;
    B_change= false;
   // lcd.print(encoderPos);
    Serial.println(encoderPos);
  }

  delay (100);
}

// Interruption sur changement d'état de A
void doEncoderA(){
  // debounce
  if ( rotating ) delay (1);  // attendre un petit peut
  rotating = true; //activation de l'anti-rebond
  // Confirmation du changement
  if( digitalRead(encoderPinA) != A_set ) {
    A_set = !A_set;

    if (B_change) {
      encoderPos += 1;
      B_change = false;
    } else
      A_change = true;

    rotating = false;  //libération de l'anti-rebond
  }
}

// Interruption sur changement d'etat de B
void doEncoderB(){
  if ( rotating ) delay (1);
  rotating = true;
  if( digitalRead(encoderPinB) != B_set ) {
    B_set = !B_set;

    if (A_change) {
      encoderPos -= 1;
      A_change = false;
    } else
      B_change = true;

    rotating = false;
  }
}
