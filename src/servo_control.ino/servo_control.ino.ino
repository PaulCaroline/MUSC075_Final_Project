#include <Servo.h> 

////////////////////////////////////////////////////////////////
// Author: Paul Caroline
// Date: 06 May 2021
// Final Project: Servo Control
// MUSC 075 - Musical Interfaces in Robotics
/////////////////////////////////////////////////////////////////


#include <Servo.h>

// Define pins for capacitive touch
const int input1 = 15;
const int input2 = 16;
const int input3 = 17;
const int input4 = 18;

/*
* Set a threshold value to govern the difference between two touch signals
* that would be large enough to signify a stopped string.
*/
const int threshold = 50;

// Define current touch read values
int curr1;
int curr2;
int curr3;
int curr4;

// Define previous touch read values
int  prev1;
int  prev2;
int  prev3;
int  prev4;


// Define our servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;


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

  // Initialize touch read values
  curr1 = touchRead(input1);
  curr2 = touchRead(input2);
  curr3 = touchRead(input3);
  curr4 = touchRead(input4);
}

void loop() {
  // Save previous touch values
  prev1 = curr1;
  prev2 = curr2;
  prev3 = curr3;
  prev4 = curr4;

  // Read in new touch values
  curr1 = touchRead(input1);
  curr2 = touchRead(input2);
  curr3 = touchRead(input3);
  curr4 = touchRead(input4);

  // Check signal differences and pluck stopped strings
  if (curr1 - prev1 > threshold) {
    Serial.println("Triggered string 1");

    servo1.write(45);
    delay(100);
    servo1.write(0);
   }

  if (curr2 - prev2 > threshold) {
    Serial.println("Triggered string 2");

    servo2.write(45);
    delay( 100);
    servo2.write(0);
   }

  if (curr3 - prev3 > threshold) {
    Serial.println("Triggered string 3");

    servo3.write(45);
    delay(100);
    servo3.write(0);
   }

  if (curr4 - prev4 > threshold) {
    Serial.println("Triggered string 4");

    servo3.write(45);
    delay(100);
    servo4.write(0);
   }
      
}
