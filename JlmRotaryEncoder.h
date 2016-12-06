/*********************************

   classe JlmRotaryEncoder KY040

   pour arduino uno et nano

   12 2016

 *********************************/

#ifndef JlmRotaryEncoder_h
#define JlmRotaryEncoder_h

#include <Arduino.h>

class JlmRotaryEncoder
{
  public:

    JlmRotaryEncoder(byte dt, byte clk, byte sw = 0) ; // constructeur avec broches pour dt , clk et sw

    ~JlmRotaryEncoder(); // destructeur

    int encoderA(); //  changement d'état de A
    int encoderB(); // changement d'etat de B
    void switchClear(); // clear compteur avec le switch

  protected:

    void init(); // initialisation des branchements

    byte m_encoderPinA; // right (DT) pin A
    byte m_encoderPinB; // left (CLK) pin B
    byte m_switchButton; // switch (SW) pin sw
    boolean m_unSwitch; // un seul appui à la fois sur sw

    volatile unsigned int m_encoderPos;  // un compteur de position
    boolean m_rotating;    // gestion de l'anti-rebonds

    // variable pour les routines de changement d'état
    boolean m_A_set;
    boolean m_B_set;
    boolean m_A_change;
    boolean m_B_change;

};

#endif
