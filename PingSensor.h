#ifndef PINGSENSOR_H
#define PINGSENSOR_H
#include "Arduino.h"

class PingSensor
{
public:
    PingSensor();
    ~PingSensor(); ///Default destructor

    void begin(uint8_t,uint8_t,uint16_t,uint8_t);  ///Initialize pingsensor
    void trigger();
    uint16_t getDistance();
    uint16_t getRoundTimeMicroseconds();
    uint8_t available();

    static PingSensor *pingSingleton;
    static void ISREcho(void);

protected:

    void parseTime();
    uint16_t lastRoundTime;

    uint16_t distance,time;     //Measured data Variables
    uint8_t trigPin, echoPin;   //Pin variables
    uint8_t trigPulseDuration;  //Trigger pulse duration
    uint16_t timeout;           //Read timeout
private:
};

PingSensor Ping;
#endif // PINGSENSOR_H
