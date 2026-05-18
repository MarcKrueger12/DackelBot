#include <Arduino.h>
#include <math.h>
#include "distance.hpp"
#include "buzzer.hpp"
#include "rgbLED.hpp"
#include "servoEars.hpp"
#include "servoTail.hpp"

enum DogState {
  INITIAL_STATE,
  JOY,
  CURIOSITY,
  SADNESS,
  ANGER
};

double lastDistance = 0;
const double activityThreshold = 3.0;

DogState currentState = INITIAL_STATE;
DogState lastState = INITIAL_STATE;

unsigned long lastStateChange = 0;
const unsigned long timeoutDuration = 7000;



void applyState(DogState state){

  switch(state){

    case INITIAL_STATE:
      setColor(0, 255, 255);
      setServoEars(10);
      setTail(90);
      break;

    case JOY:
      happy();
      break;

    case CURIOSITY:
      surprised();
      break;

    case SADNESS:
      sad();
      break;

    case ANGER:
      angry();
      break;
  }
}

void setup() {
  setupBuzzer();
  setupEcho();
  setupLED();
  setupServoEars();
  setupServoWagging();

  applyState(INITIAL_STATE);

  lastStateChange = millis();
  lastDistance = getDistance();
}

void loop() {

  double dist = getDistance();

  if(dist <= 20){
    currentState = JOY;
  }
  else if(dist <= 40){
    currentState = CURIOSITY;
  }
  else if(dist <= 60){
    currentState = SADNESS;
  }
  else if(dist < 80){
    currentState = ANGER;
  }
  else{
    currentState = INITIAL_STATE;
  }


  if(fabs(dist - lastDistance) > activityThreshold){
    lastStateChange = millis();
  }

  lastDistance = dist;

  if(currentState != lastState){
    lastState = currentState;
    lastStateChange = millis();
    applyState(currentState);
  }

  if(millis() - lastStateChange >= timeoutDuration){

    if(currentState != INITIAL_STATE){
      currentState = INITIAL_STATE;
      lastState = INITIAL_STATE;

      applyState(INITIAL_STATE);
    }
  }
}