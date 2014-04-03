#ifndef PINGSENSOR_H
#define PINGSENSOR_H
#include "Arduino.h"

enum {PS_RESET,PS_TRIGGERED,PS_HIGH};

class PingSensor
{
public:
    PingSensor();
    ~PingSensor(); ///Default destructor

    void begin(uint8_t,uint8_t,uint16_t,uint8_t);  ///Initialize pingsensor
    void trigger();
    uint16_t getDistance();
    uint16_t getRoundTime();
    uint8_t available();

    static PingSensor *pingSingleton;
    static void ISREcho(void);

protected:
    uint16_t distance,time;     //Measured data Variables
    uint8_t trigPin, echoPin;   //Pin variables
    uint8_t trigPulseDuration;  //Trigger pulse duration
    uint16_t timeout;           //Read timeout

    uint8_t state; //Data parse FSM state
    bool stateLock;
private:
};

#endif // PINGSENSOR_H
