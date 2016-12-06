/*******************************
  gestion d'un codeur rotatif KY040
  avec
  la classe JlmRotaryEncoder

  décembre 2016
*******************************/

// définition des pin pour le KY040
enum PinAssignments {
  encoderPinA = 2,   // right (DT)
  encoderPinB = 3,   // left (CLK)
  clearButton = 4    // switch (SW)
};

// classe encodeur rotatif KY040
#include "JlmRotaryEncoder.h"
JlmRotaryEncoder rotary(encoderPinA, encoderPinB, clearButton); // clearButton si besoin

volatile  int encoderPos = 0;  //  compteur de position
int lastReportedPos = 1;   // gestion du changement

void setup() {
  Serial.begin (9600);
<<<<<<< HEAD
=======
  rotary.init(); // initialisation des branchements
>>>>>>> e51e84fac455bea611def8b606bcbd170080ea23
  attachInterrupt(digitalPinToInterrupt(encoderPinA), doEncoderA, CHANGE);// activation de l'interruption 0 (pin 2)
  attachInterrupt(digitalPinToInterrupt(encoderPinB), doEncoderB, CHANGE); // activation de l'interruption 1 (pin 3)
}

void loop() {
  if (lastReportedPos != encoderPos) {
    Serial.print("Index: ");
    Serial.print(encoderPos, DEC);
    Serial.print("     A :");
    lastReportedPos = encoderPos;
    Serial.print(digitalRead(encoderPinA));
    Serial.print("   B :");
    Serial.println(digitalRead(encoderPinB));
  }
  rotary.switchClear(); // clear compteur si appuis sur sw
  delay (100);
}

// Interruption sur changement d'état de A
void doEncoderA() {
  encoderPos = rotary.encoderA();
}

// Interruption sur changement d'etat de B
void doEncoderB() {
  encoderPos = rotary.encoderB();
}
