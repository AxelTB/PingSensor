#ifndef PINGSENSOR_H
#define PINGSENSOR_H
#include "Arduino.h"

class PingSensor
{
public:
	//static PingSensor *pingPointer;
	static void ISREcho(void);

    PingSensor();
    ~PingSensor(); ///Default destructor

    ///Initialize pingsensor
    void begin(uint8_t _trigPin,uint8_t _echoPin);
    void begin(uint8_t _trigPin,uint8_t _echoPin,uint16_t _timeoutus);
    void begin(uint8_t _trigPin,uint8_t _echoPin,uint16_t _timeoutus,uint8_t _trigPulseDuration);
    void trigger();
    uint16_t getDistance();
    uint16_t getRoundTimeMicroseconds();
    uint8_t available();



protected:

    void parseTime();
    uint16_t lastRoundTime;

    uint16_t distance,time;     //Measured data Variables
    uint8_t trigPin, echoPin;   //Pin variables
    uint8_t trigPulseDuration;  //Trigger pulse duration
    uint16_t timeout;           //Read timeout
private:
};

#endif // PINGSENSOR_H
