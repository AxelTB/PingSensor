#include "PingSensor.h"
#include "Arduino.h"
/** @brief PingSensor()
  *
  * Default constructor
  */
PingSensor::PingSensor()
{
    pingSingleton=this; ///Only one instance allowed
}
/** @brief PingSensor
  *
  * @todo: document this function
  */
 PingSensor::PingSensor(uint8_t _trigPin,uint8_t _echoPin,uint16_t _timeoutus = 38400)
{
    //Save parameters
    this->trigPin=_trigPin;
    this->echoPin=_echoPin;
    this->timeout=_timeoutus;

    //Init pin
    pinMode(trigPin,OUTPUT); //Pin di trigger
    pinMode(echoPin,INPUT); //Pin di echo
    attachInterrupt(echoPin,&PingSensor::ISREcho)
}

/** @brief getRoundTime
  *
  * @todo: document this function
  */
uint16_t PingSensor::getRoundTime()
{

}

/** @brief getDistance
  *
  * @todo: document this function
  */
uint16_t PingSensor::getDistance()
{

}

/** @brief trigger
  *
  * @todo: document this function
  */
void PingSensor::trigger()
{

}



/** @brief PingSensor
  *
  * @todo: document this function
  */
 PingSensor::PingSensor(uint8_t,uint8_t)
{

}

/** @brief PingSensor
  *
  * @todo: document this function
  */
 PingSensor::PingSensor()
{

}

/** @brief ISREcho
  *
  * @todo: document this function
  */
void PingSensor::ISREcho(void)
{

}

