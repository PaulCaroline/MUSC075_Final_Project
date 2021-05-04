#include <Servo.h> 

////////////////////////////////////////////////////////////////
// Author: Paul Caroline
// Date: 28 Apr. 2021
// Final Project: Servo Test
// MUSC 075 - Musical Interfaces in Robotics
// ** Special thanks to MERT Arduino & Tech
//    https://www.youtube.com/watch?v=TkA2LJctU1c
/////////////////////////////////////////////////////////////////

// Define pins for capacitive touch
const int touchReadPin1 = 15;
const int touchReadPin2 = 16;
const int touchReadPin3 = 17;
const int touchReadPin4 = 18;

// Define touch read values
int touchVal1;
int touchVal2;
int touchVal3;
int touchVal4;

int touchData[] = {touchVal1, touchVal2, touchVal3, touchVal4};

// Define our servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

Servo servos[] = {servo1, servo2, servo3, servo4};

// Define angle constraints
const int minAngle = 0;
const int maxAngle = 50;

// Angle increment
int angleStep = 30;

// Variables for servo position in degrees
int angle1 = 1;
int angle2 = 1;
int angle3 = 1;
int angle4 = 1;

int angles[] = {angle1, angle2, angle3, angle4};

// Define touch on/off
bool touching1 = false;
bool touching2 = false;
bool touching3 = false;
bool touching4 = false; 

bool touchOnOff[] = {touching1, touching2, touching3, touching4};

void setup() {
  Serial.begin(9600);
  
  // Define servo signal inputs
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);

  // Set initial positions
  servo1.write(1);
  servo2.write(1);
  servo3.write(1);
  servo4.write(1);
}

void loop() {

  // Read touch values
  touchVal1 = touchRead(touchReadPin1);
  touchData[0] = touchVal1;
  touchVal2 = touchRead(touchReadPin2);
  touchData[1] = touchVal2;
  touchVal3 = touchRead(touchReadPin3);
  touchData[2] = touchVal3;
  touchVal4 = touchRead(touchReadPin4);
  touchData[3] = touchVal4;
  
  // Print integer outputs
  Serial.print("G string: ");
  Serial.print(touchVal4);
  Serial.println("\n");

  Serial.print("C string: ");
  Serial.print(touchVal3);
  Serial.println("\n");

  Serial.print("E string: ");
  Serial.print(touchVal2);
  Serial.println("\n");

  Serial.print("A string: ");
  Serial.print(touchVal1);
  Serial.println("\n");


  // Determine from touch values if the string is stopped
  for (int k = 0; k < 4; k++) {
    if (touchData[k] >= 1100) {
      touchOnOff[k] = true;
      Serial.print(k);
      Serial.print(": ");
      Serial.print(touchData[k]);
      Serial.println();
      delay(1000);
    } else {
      touchOnOff[k] = false;    
    }
  }

  // Calculate next servo moves
  for (int i = 0; i < 4; i++) {
    if (touchOnOff[i]) {

      // change the angle for the next iteration of the loop
      angles[i] = angles[i] + angleStep;

      // Reverse the direction
      if (angles[i] >= maxAngle) {
        angleStep = - angleStep;
      }

      if (angles[i] <= minAngle) {
        angleStep = - angleStep;
      }
    }
  }

  // Pluck the triggered strings
  for (int j = 0; j < 4; j++) {
    if (touchOnOff[j]) {
      servos[j].write(angles[j]);
    }
  }

  delay(100);
}
