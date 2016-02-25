#include <PinChangeInt.h>

volatile uint8_t mode = 0;
volatile uint8_t lightstate = 0;
volatile unsigned long lasttime = 0;
volatile bool buttonPressed = false;
volatile unsigned long lastmicros = 0;

void ModeChange()
{
  mode++;
  if (mode > 2)
  {
    mode = 0;
  }
  lightstate = 0;
  lasttime = millis();
}

void ButtonPressed()
{ 
  if (digitalRead(1) == LOW)
  {
    buttonPressed = true;
  }
  else
  {
    buttonPressed = false;
  }
}

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  attachPinChangeInterrupt(1, ButtonPressed, CHANGE);
}

void normal() {
  unsigned long elapsed = millis() - lasttime;
  
  if (lightstate == 0) //green
  {
    digitalWrite(0, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    if (elapsed > 20000)
    {
      lightstate++;
      lasttime += elapsed;
    }
  }
  else if (lightstate == 1) //yellow
  {
    digitalWrite(0, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    if (elapsed > 3000)
    {
      lightstate++;
      lasttime += elapsed;
    }
  }
  else if (lightstate == 2) //red
  {
    digitalWrite(0, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    if (elapsed > 15000)
    {
      lightstate = 0;
      lasttime += elapsed;
    }
  }
}

void blinkred() {
  unsigned long elapsed = millis() - lasttime;
  digitalWrite(0, LOW);
  digitalWrite(4, LOW);

  if (lightstate == 0)
  {
    digitalWrite(5, HIGH);
    if (elapsed > 400) 
    {
      lightstate = 1;
      lasttime += elapsed;
    }
  }
  else
  {
    digitalWrite(5, LOW);
    if (elapsed > 400) 
    {
      lightstate = 0;
      lasttime += elapsed;
    }
  }
}

void blinkyellow() {
  unsigned long elapsed = millis() - lasttime;
  digitalWrite(0, LOW);
  digitalWrite(5, LOW);

  if (lightstate == 0)
  {
    digitalWrite(4, HIGH);
    if (elapsed > 400) 
    {
      lightstate = 1;
      lasttime += elapsed;
    }  }
  else
  {
    digitalWrite(4, LOW);
    if (elapsed > 400) 
    {
      lightstate = 0;
      lasttime += elapsed;
    }
  }
}

void loop() {
  unsigned long elapsed = micros() - lastmicros;

  if (buttonPressed == true)
  {
    if (elapsed > 200000)
    {
      ModeChange();
      lastmicros += elapsed;
    }
    buttonPressed = false;
  }
  
  if (mode == 0) 
  {
    normal();
  }
  else if (mode == 1) 
  {
    blinkred();
  }
  else if (mode == 2) 
  {
    blinkyellow();
  }
}


