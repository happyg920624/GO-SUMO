/*
 * Pin assignment:
 * D2 - BT
 * 
 * A0 - IR Left
 * A1 - IR Middle
 * A2 - IR Right
 * 
 * A4 - US Trige
 * A5 - US Echo
 * +++++++++++++++++++
 * 
 * APP:
 * F - Forward
 * B - Backward
 * L -Left
 * R - Right
 * M - Forward Left
 * N - Forward Right
 * O - Backward Left
 * P - Backward Right
 * S- Stop
 * X - User1
 * Y - User2
 * Z - User3
 * A - AI
 */

#include <AFMotor.h>
AF_DCMotor BL (1);
AF_DCMotor BR (2);
AF_DCMotor FR (3);
AF_DCMotor FL (4);
byte SPEED = 255;

#include <Ultrasonic.h>
Ultrasonic ultrasonic (A4,A5);
int distCM;

#include <SoftwareSerial.h>
SoftwareSerial blue (9,10);
byte DATA;

boolean searchRight = true;
byte searchSpeed = 200;
byte distance = 40;
boolean whiteLine = true;
int backOffTime = 1000;
boolean ai = false;
int middleIR = A1;

void setup() 
{
 blue.begin(9600);
 FL.setSpeed(255);
 FR.setSpeed(255);
 BL.setSpeed(255);
 BR.setSpeed(255);
 delay(1000);
}

void loop() 
{
 BT();
 AI();
}

//==========
void BT()
{
  if (blue.available() > 0)
  {
    ai = false;
    DATA = blue.read();

     if(DATA=='F'){delay(1);SPEED=blue.read(); forward();}
else if(DATA=='B'){delay(1);SPEED=blue.read(); backward();}
else if(DATA=='L'){delay(1);SPEED=blue.read(); left();}
else if(DATA=='R'){delay(1);SPEED=blue.read(); right();}
else if(DATA=='M'){delay(1);SPEED=blue.read(); forwardLeft();}
else if(DATA=='N'){delay(1);SPEED=blue.read(); forwardRight();}
else if(DATA=='O'){delay(1);SPEED=blue.read(); backwardLeft();}
else if(DATA=='P'){delay(1);SPEED=blue.read(); backwardRight();}
else if(DATA=='S'){STOP();}
else if(DATA=='A'){ai = true;}

else if(DATA=='X')
{


  while(blue.available()==0){}
  while(blue.available()>0)
  {
    DATA=blue.read();
            if(DATA=='F'){forward();}
      else  if(DATA=='B'){backward();}
      else if(DATA=='L'){ left();}
      else if(DATA=='R'){ right();}
      else if(DATA=='M'){forwardLeft();}
      else if(DATA=='N'){forwardRight();}
      else if(DATA=='O'){backwardLeft();}
      else if(DATA=='P'){backwardRight();}
      else if(DATA=='S'){STOP();}    
      while(blue.available()==0)
      DATA=blue.read();
      delay(DATA*10);
      
  }
   }
  }
}
void AI()
{
  if(ai)
  {

    US();

///SEARCHING***
   while(distCM>distance)
   {
    if(searchRight){SPEED=searchSpeed;right();}
    else{SPEED=searchSpeed;left();}
    US();
   }
//PUSHING**
  SPEED=255;
  forward();

  if(whiteLine)
    {
      while(analogRead(middleIR)>100){} //>100=black
    }
    else
    {
      while(analogRead(middleIR)<100){} //100=white
    }
  
//BACK OFF££
  backward();
  delay(backOffTime);
  }
}



//--------------
void forward()
{
  FL.setSpeed(SPEED);
  FR.setSpeed(SPEED);
  BL.setSpeed(SPEED);
  BR.setSpeed(SPEED);
  FL.run(FORWARD);
  FR.run(FORWARD);
  BL.run(FORWARD);
  BR.run(FORWARD);
}
//**********
void backward()
{
  FL.setSpeed(SPEED);
  FR.setSpeed(SPEED);
  BL.setSpeed(SPEED);
  BR.setSpeed(SPEED);
  FL.run(BACKWARD);
  FR.run(BACKWARD);
  BL.run(BACKWARD);
  BR.run(BACKWARD);
}
///+++++++
void left()
{
  FL.setSpeed(SPEED);
  FR.setSpeed(SPEED);
  BL.setSpeed(SPEED);
  BR.setSpeed(SPEED);
  FL.run(BACKWARD);
  FR.run(FORWARD);
  BL.run(BACKWARD);
  BR.run(FORWARD);
}

void right()
{
  FL.setSpeed(SPEED);
  FR.setSpeed(SPEED);
  BL.setSpeed(SPEED);
  BR.setSpeed(SPEED);
  FL.run(FORWARD);
  FR.run(BACKWARD);
  BL.run(FORWARD);
  BR.run(BACKWARD);
}
//++++++++++++++++
void forwardLeft()
{
  FL.setSpeed(SPEED);
  FR.setSpeed(SPEED);
  BL.setSpeed(SPEED);
  BR.setSpeed(SPEED);
  FL.run(RELEASE);
  FR.run(FORWARD);
  BL.run(RELEASE);
  BR.run(FORWARD);
}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void forwardRight()
{
  FL.setSpeed(SPEED);
  FR.setSpeed(SPEED);
  BL.setSpeed(SPEED);
  BR.setSpeed(SPEED);
  FL.run(FORWARD);
  FR.run(RELEASE);
  BL.run(FORWARD);
  BR.run(BACKWARD);
}

void backwardLeft()
{
  FL.setSpeed(SPEED);
  FR.setSpeed(SPEED);
  BL.setSpeed(SPEED);
  BR.setSpeed(SPEED);
  FL.run(RELEASE);
  FR.run(BACKWARD);
  BL.run(RELEASE);
  BR.run(BACKWARD);
}
///////
void backwardRight()
{
  FL.setSpeed(SPEED);
  FR.setSpeed(SPEED);
  BL.setSpeed(SPEED);
  BR.setSpeed(SPEED);
  FL.run(BACKWARD);
  FR.run(RELEASE);
  BL.run(BACKWARD);
  BR.run(RELEASE);
}
//////////
void STOP()
{
  FL.run(RELEASE);
  FR.run(RELEASE);
  BL.run(RELEASE);
  BR.run(RELEASE);
}
//------------
void US()
{
  int i;
  delay(20);
  i=ultrasonic.distanceRead();
  if(i>0){distCM==i;}
}


