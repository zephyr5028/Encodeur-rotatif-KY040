#include "JlmRotaryEncoder.h"

// surcharge constructeur avec timer - broches dt et clk ainsi que sw si besoin
JlmRotaryEncoder::JlmRotaryEncoder(byte dt, byte clk, byte sw) : m_encoderPinA(dt), m_encoderPinB(clk), m_switchButton(sw),
  m_A_set(false) , m_B_set(false), m_A_change(false), m_B_change(false), m_rotating(false), m_encoderPos(0),  m_unSwitch(true)
{
}

// destrcuteur
JlmRotaryEncoder::~JlmRotaryEncoder()
{
}

//initialisation des branchements
void JlmRotaryEncoder::init()
{
  pinMode(m_encoderPinA, INPUT_PULLUP); // utilisation du pullup
  pinMode(m_encoderPinB, INPUT_PULLUP); // utilisation du pullup
  if (m_switchButton != 0)   pinMode(m_switchButton, INPUT_PULLUP); // utilisation du pullup
}

// changement d'état de A
int JlmRotaryEncoder::encoderA()
{
  // debounce
  if ( m_rotating ) delay (3);  // attendre un petit peut
  m_rotating = true; //activation de l'anti-rebond
  // Confirmation du changement
  if ( digitalRead(m_encoderPinA) != m_A_set )  {
    m_A_set = !m_A_set;

    if (m_B_change) {
      m_encoderPos += 1;
      m_B_change = false;
    } else
      m_A_change = true;

    m_rotating = false;  //libération de l'anti-rebond
  }
  return m_encoderPos;
}

// changement d'etat de B
int JlmRotaryEncoder::encoderB()
{
  if ( m_rotating ) delay (3);
  m_rotating = true;
  if ( digitalRead(m_encoderPinB) != m_B_set )  {
    m_B_set = !m_B_set;

    if (m_A_change) {
      m_encoderPos -= 1;
      m_A_change = false;
    } else
      m_B_change = true;

    m_rotating = false;
  }
  return m_encoderPos;
}

// clear le compteur avec le switch
void JlmRotaryEncoder::switchClear()
{
  //debounce et un seul appui à la fois
  if (digitalRead(m_switchButton) == LOW )  delay(20); else m_unSwitch = true;
  if (digitalRead(m_switchButton) == LOW  and m_unSwitch) {
    m_encoderPos = 0;
    m_A_change = false;
    m_B_change = false;
    m_unSwitch = false;
  }
}

