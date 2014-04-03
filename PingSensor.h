#ifndef PINGSENSOR_H
#define PINGSENSOR_H


class PingSensor
{
public:
    PingSensor(); ///Default constructor
    PingSensor(uint8_t,uint8_t); ///Initialize pingsensor
    PingSensor(uint8_t,uint8_t,uint16_t); ///Initialize pingsensor with defined timeout
    ~PingSensor(); ///Default destructor
    void trigger();
    uint16_t getDistance();
    uint16_t getRoundTime();

protected:
    uint16_t distance,time; //Measured data Variables
    uint8_t trigPin, echoPin; //Pin variables
    uint16_t timeout;
private:
};

#endif // PINGSENSOR_H
