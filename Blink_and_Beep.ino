#define DEBUG
#include "pitches.h"

#define BUTTONS 5
unsigned char ledPins[]={3,5,6,9,10};  // Blue, Yellow, Green, Red, White
unsigned char btnPins[]={2,4,7,8,12};  // Blue, Yellow, Green, Red, White
unsigned char pinSpeaker=11;           // Position of speaker
unsigned int tones[5] = {
  NOTE_B3,
  NOTE_C3,
  NOTE_D3,
  NOTE_E3,
  NOTE_F3
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  #ifdef DEBUG
  Serial.println("");
  #endif

  // Setting pins
  for (unsigned char index = 0; index < BUTTONS; index++)
  {
    pinMode(ledPins[index], OUTPUT);
    digitalWrite(ledPins[index], HIGH);
    pinMode(btnPins[index], INPUT_PULLUP);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  checkButtonInputs();
}

void playTone(int note=0) {
  #ifdef DEBUG
  Serial.print("DEBUG: Playing tone increase by: ");
  Serial.println(note);
  #endif
  
  static int currentTone;
  currentTone += note;
  Serial.print("DEBUG: Playing tone : ");
  Serial.println(currentTone);
  if (currentTone > 0)
  {
    tone(pinSpeaker, currentTone);
  } else {
    noTone(pinSpeaker);
    currentTone = 0;
  }
}

void checkButtonInputs()
{
  static bool previousState[BUTTONS];
  bool currentState[BUTTONS];

  for (unsigned char index = 0; index < BUTTONS; index++)
  {
    currentState[index] = digitalRead(btnPins[index]);  // Read the button
    if (currentState[index] != previousState[index])
    {
      // State has changed
      previousState[index] = currentState[index];
      digitalWrite(ledPins[index], currentState[index]);

      if (currentState[index] == HIGH)
      {
        playTone(tones[index] * -1);
      }
      if (currentState[index] == LOW)
      {
                              playTone(tones[index]);
      }
    }
  }
}
