#include "PingSensor.h"

#define TRIGPULSEDURATION 10
#define TIMEOUTUS 38400
//Interrupt variables
volatile bool interrupt_enable=false,echo_state=false;
volatile uint16_t wave_time=0;

/** @brief PingSensor()
  *
  * Default constructor
  */
PingSensor::PingSensor()
{
    // PingSensor::pingPointer=this; //Only one instance allowed
    interrupt_enable=false;
    echo_state=false; //Reset state
}
PingSensor::~PingSensor()
{
    detachInterrupt(echoPin);
}

/** @brief begin
  *
  * Init Ping sensor
  * @Param: _trigPin: trigger pin
  *         _echoPin: echo pin
  *         [_timeoutus: pulse length timeout (microseconds)] (default:38400 us)
  *         [_trigPulseDuration: trigger positive edge duration] (default: 10us)
  */
void PingSensor::begin(uint8_t _trigPin,uint8_t _echoPin,uint16_t _timeoutus,uint8_t _trigPulseDuration)
{
    //Save parameters
    this->trigPin=_trigPin;
    this->echoPin=_echoPin;
    this->timeout=_timeoutus;
    this->trigPulseDuration=_trigPulseDuration;

    //Reset error
    this->error=PSE_NOERR;
    //Init pin
    pinMode(trigPin,OUTPUT); //Pin di trigger
    pinMode(echoPin,INPUT); //Pin di echo
    attachInterrupt(echoPin,&PingSensor::ISREcho,CHANGE); //Set interrupt on echo pin at every front
}

//Overloaded versions-----------------------------------------
void PingSensor::begin(uint8_t _trigPin,uint8_t _echoPin,uint16_t _timeoutus)
{
    begin(_trigPin,_echoPin,_timeoutus,TRIGPULSEDURATION); //Init with standard TRIGGER PULSE DURATION
}
void PingSensor::begin(uint8_t _trigPin,uint8_t _echoPin)
{
    begin(_trigPin,_echoPin,TIMEOUTUS); //Init with standard timeout
}
//-------------------------------------------------------------

/** @brief available
  *
  * Returns 1 if a new measurement is available, 0 otherwise
  */
int8_t PingSensor::available()
{

    if(!interrupt_enable && echo_state) //If new value available
        return 1;

    return 0;

}

/** @brief waitAvailable
  *
  * Locking function. Returns whenever new data is available (Or after given waitTimeout).
  *@param: waitTimeout Maximum function wait time. (Default 2*_timeoutus = 76800)
  *@return: 0 if new data available
            1 if waitTimeout occurred
  *
  */
int8_t PingSensor::waitAvailable(uint16_t waitTimeout)
{
 uint16_t startTime=micros();
    while(!available())
    {
        if(micros()-startTime>waitTimeout)
            return 1;
    }

    return 0; //New data available
}
int8_t PingSensor::waitAvailable()
{
    return waitAvailable(2*this->timeout);
}




/** @brief getRoundTime
  *
  * Gets the time of wave travel (Back and forth) in microseconds. If a new value is available evaluate it, return old value otherwise.
  * You need to use the function available to check if new data is available
  */
uint16_t PingSensor::getRoundTimeMicroseconds()
{
    if(available())
        parseTime();
    return lastRoundTime;
}

/** @brief getDistance
  *
  * Return the distance in mm.
  */
uint16_t PingSensor::getDistance()
{
    return 0.3321f*getRoundTimeMicroseconds()/2;
}
/** @brief getError
  *
  * ***If function trigger isn't called no error occur, ever***
  * @return 0 if no error
  *         PSE_TIMEOUT -> positive front time too high (May be out of range)
  *         PSE_NOFRONT -> Unable to read any front (Check connection)
  *         PSE_FASTTRIGGER -> Trigger called before communication complete (Data may be gibberish)
  *
  */
int8_t PingSensor::getError()
{
    return this->error;
}




/** @brief trigger
  *
  * Trigger ping sensor measurement. It takes at least _trigPulseDuration microseconds to be executed. (Default 10us)
*/
void PingSensor::trigger()
{
    if(interrupt_enable) //If last measurement did not complete
    {
        interrupt_enable=false; //Disable interrupt

        if(wave_time==0)
            this->error=PSE_NOFRONT; //No front Change found
        else if(micros()-wave_time>this->timeout)
            this->error=PSE_TIMEOUT; //Timeout in reading wave
        else
            this->error=PSE_FASTTRIGGER; //Too fast trigger

        wave_time=0;
        echo_state=false; //Reset state
    }
    else if(available())
        parseTime(); //Save old measurement


    //Send a positive front to the ping sensor
    digitalWrite( trigPin, HIGH );
    delayMicroseconds( trigPulseDuration );
    digitalWrite( trigPin, LOW );

    //Enable interrupt evaluation
    interrupt_enable=true;
}
/** @brief parseTime
  *
  * Parse time from interrupt variables. Check availability first!!!
  */
void PingSensor::parseTime()
{
    if(wave_time>this->timeout)  //If timeout occurred
        this->error=PSE_TIMEOUT;    //Signal Timeout Error
    else
    {
        this->error=PSE_NOERR;      //Reset Error
        lastRoundTime=wave_time;    //Save travel time
    }

    wave_time=0;
    echo_state=false;   //Reset echo state

}



//ISR====================================================================

/** @brief ISREcho
  *
  * Function called every front on echo pin
  */
void PingSensor::ISREcho(void)
{
    if(interrupt_enable) //If interrupt evaluation enabled
    {
        if(echo_state==false) //Rising edge
        {
            wave_time=micros(); //Save current time
            echo_state=true; //Signal HIGH level
        }
        else
        {
            wave_time=micros()-wave_time; //Save HIGH level dt
            interrupt_enable=false; //Disable interrupt
        }
    }
}

/***
state
interrupt_enable    echo_state  state
0                   0           RESET
1                   0           Waiting Rising Edge
1                   1           Waiting Falling Edge (wave_time contains start time)
0                   1           New value available (wave_time contains dt)
**/
