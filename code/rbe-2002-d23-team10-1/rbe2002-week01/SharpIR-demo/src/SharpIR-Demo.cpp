#include <Arduino.h>
#include <PCint.h>
#include <Sharp-IR.h>
#include <Romi32U4Buttons.h>

SharpIR sharpIR(18); // TODO: Select a pin!!!
Romi32U4ButtonB button;

int i = 0;
unsigned long time = 0;
int IRdelay = 42;

void setup() 
{
  Serial.begin(115200);
  Serial.print("Welcome!\n");

  sharpIR.init();
}

void loop()
{
  float distance = 0;
  i = 0;
  while (button.isPressed()) {
    while (i < 200) {
      if(sharpIR.getDistance(distance) && millis() > time + IRdelay)
      {
        time = millis();
        Serial.println(distance);
        i += 1;
      } 
    }
  }
}
