#include <Servo.h>        
#include <NewPing.h>      

const int LeftMotorForward = 4;
const int LeftMotorBackward = 5;
const int RightMotorForward = 6;
const int RightMotorBackward = 7;

#define TRIGGER_PIN  A1  
#define ECHO_PIN     A2  
#define MAX_DISTANCE 250 

Servo servo_motor;  
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 

boolean goesForward = false;
int distance = 100;

void setup()
{
  
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(10);   
  servo_motor.write(65);    
  delay(2000);              
  distance = readPing();   
  delay(100);
}

void loop()
{ distance = readPing();
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  
  if (distance <= 20)
  {
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);
    if(distanceLeft<=20 && distanceRight<=20)
    {
      moveBackward();
      delay(1000);
    }
    else if (distanceLeft >= distanceRight)
    {
      turnLeft();
      delay(500);
      moveStop();
      delay(300);
    }
    else
    {
      turnRight();
      delay(500);
      moveStop();
      delay(300);
    }
  }
  else
  {
    moveForward(); 
  }

    
}

int lookRight()      
{  
  servo_motor.write(0);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(65);
  return distance;
}

int lookLeft()      
{
  servo_motor.write(130);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(65);
  return distance;
}

int readPing()      
{
  delay(100);                 
  int cm = sonar.ping_cm();
  if (cm==0)
  {
    cm=250;
  }
  return cm;
}

void moveStop()       
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward()    
{
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward()  
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
}

void turnRight()      
{
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
}

void turnLeft()       
{
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}
