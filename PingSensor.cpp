#include "PingSensor.h"
#include "atomic"
/** @brief PingSensor()
  *
  * Default constructor
  */
PingSensor::PingSensor()
{
    pingSingleton=this; //Only one instance allowed
    state=PS_RESET; //Reset state
}
/** @brief begin
  *
  * Init Ping sensor
  * @Param: _trigPin: trigger pin
  *         _echoPin: echo pin
  *         [_timeoutus: pulse length timeout (microseconds)] (default:38400 us)
  *         [_trigPulseDuration: trigger positive edge duration] (default: 10us)
  */
void PingSensor::begin(uint8_t _trigPin,uint8_t _echoPin,uint16_t _timeoutus = 38400,uint8_t _trigPulseDuration=10)
{
//Save parameters
    this->trigPin=_trigPin;
    this->echoPin=_echoPin;
    this->timeout=_timeoutus;
    this->trigPulseDuration=_trigPulseDuration;

    //Init pin
    pinMode(trigPin,OUTPUT); //Pin di trigger
    pinMode(echoPin,INPUT); //Pin di echo
    attachInterrupt(echoPin,&PingSensor::ISREcho,CHANGE); //Set interrupt on echo pin at evry front
}

/** @brief available
  *
  * @todo: document this function
  */
uint8_t PingSensor::available()
{

}




/** @brief getRoundTime
  *
  * Gets the time of wave travel (Back and forth). If a new value is available evaluate it, return old value otherwise.
  * You need to use the function available to check if new data is available
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
  * Trigger ping sensor measurement. It takes at least _trigPulseDuration microseconds to be executed. (Default 10us)
*/
void PingSensor::trigger()
{
    //TODO: use
    //Lock all function to easily avoid echo error
    while(stateLock); //Wait for lock
    stateLock=true; //LOCK

    //Send a positive front to the ping sensor
    digitalWrite( trigPin, HIGH );
    delayMicroseconds( 10 );
    digitalWrite( trigPin, LOW );

    //Enable interrupt evaluation
    this->state=PS_TRIGGERED;

    stateLock=false; //FREE
}



/** @brief ISREcho
  *
  * @todo: document this function
  */
void PingSensor::ISREcho(void)
{

}

