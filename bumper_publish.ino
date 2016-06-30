/* 
 * Button publisher for Rosserial
 */

#include <ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int64.h>

ros::NodeHandle nh;

std_msgs::Int64 bumper_msg;
ros::Publisher pub_bumper("bumpers", &bumper_msg);

enum State{ NEUTRAL, LEFT, RIGHT, FRONT};

const int FL_pin = 7;
const int FR_pin = 5;

int last_reading;
bool last_FL_reading;
bool last_FR_reading;
long last_debounce_time = 0;
long debounce_delay = 50;
bool published = true;

int currentState(bool FL_state, bool FR_state){
  if(!FL_state && !FR_state)
    return NEUTRAL;
  else if(FL_state && !FR_state)
    return LEFT;
  else if(!FL_state && FR_state)
    return RIGHT;
  else 
    return FRONT;
}

void setup()
{
  nh.initNode();
  nh.advertise(pub_bumper);
  // initialize a pin for our bumper
  //pinMode(bumper_pin, INPUT);
  
  pinMode(FL_pin, INPUT);
  pinMode(FR_pin, INPUT);
  
  //last_reading = ! digitalRead(bumper_pin);
  last_FL_reading = !digitalRead(FL_pin);
  last_FR_reading = !digitalRead(FR_pin);
  last_reading = currentState(last_FL_reading, last_FR_reading);
}

//bool bumperStatus;
//bool FR_state;
//bool FL_state;

bool FL_reading;
bool FR_reading;

void loop()
{
    bool FL_reading = !digitalRead(FL_pin);
    bool FR_reading = !digitalRead(FR_pin);
    int reading = currentState(FL_reading, FR_reading);
    //bool reading = ! digitalRead(bumper_pin);
  if (last_reading!= reading){
      last_debounce_time = millis();
      published = false;
  }
  if ( !published && (millis() - last_debounce_time)  > debounce_delay) {
    bumper_msg.data = reading;
    pub_bumper.publish(&bumper_msg);
    
    published = true;  
  }
  
  last_reading = reading;
  nh.spinOnce();
}
