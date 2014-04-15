// 4x4x4 Cube 
// Flame


const int Z1pin = 1;
const int Z2pin = 2;
const int Z3pin = 3;
const int Z4pin = 4;
const int ShiftPWM_clockPin = 5;
const int ShiftPWM_latchPin = 6;
const int ShiftPWM_dataPin = 7;

#define SHIFTPWM_NOSPI
const bool ShiftPWM_invertOutputs = false;
const bool ShiftPWM_balanceLoad =false;

#include <ShiftPWM.h>

void oneByOne(void);
unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
unsigned int numRegisters = 2;
unsigned int numOutputs = numRegisters*8;
unsigned long startTime = 0;
unsigned char Zpin = 1;

void setup(){
  randomSeed(analogRead(0));
  pinMode(Z1pin, OUTPUT);
  pinMode(Z2pin, OUTPUT);
  pinMode(Z3pin, OUTPUT);
  pinMode(Z4pin, OUTPUT);  
  ShiftPWM.SetAmountOfRegisters(numRegisters);
  ShiftPWM.SetPinGrouping(1);
  ShiftPWM.Start(pwmFrequency, maxBrightness);  
  Serial.begin(9600); // for debug
}

void loop(){
  digitalWrite(Z1pin, LOW);
  digitalWrite(Z2pin, LOW);
  digitalWrite(Z3pin, LOW);
  digitalWrite(Z4pin, LOW);
  
  Zpin = random( Z1pin, Z4pin );
  digitalWrite(Zpin, HIGH);
  oneByOne();
}

void oneByOne(void){
  unsigned char brightness;
  unsigned long fadeTime = 1000;
  unsigned long loopTime = numOutputs*fadeTime*2;
  unsigned long time = millis()-startTime;
  unsigned long timer = time%loopTime;
  unsigned long currentStep = timer%(fadeTime*2);
  int activeLED = timer/(fadeTime*2);
  
  if(currentStep <= fadeTime ){
    brightness = currentStep*maxBrightness/fadeTime;
  }
  else{
    brightness = maxBrightness-(currentStep-fadeTime)*maxBrightness/fadeTime;
  }

  ShiftPWM.SetAll(0);
  ShiftPWM.SetOne(activeLED, brightness);
  //Serial.println (activeLED);
}

