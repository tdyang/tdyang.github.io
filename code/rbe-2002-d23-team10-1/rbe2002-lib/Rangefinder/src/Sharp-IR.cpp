#include <Sharp-IR.h>

const uint32_t SHARP_IR_INTERVAL = 50; // arbitrarily long -- check the datasheet

bool SharpIR::getDistance(float& distance)
{
    bool newReading = false;
    uint32_t currTime = millis();
    if(currTime - lastReading >= SHARP_IR_INTERVAL)
    {
        lastReading = currTime;

        uint16_t adcResult = analogRead(adcPin);
        distance = 18.9 / ((adcResult / 1024) * 5 - 0.372); 

#ifdef __SHARP_DEBUG__
        Serial.println(distance);
#endif

        newReading = true;
    }

    return newReading;
}
