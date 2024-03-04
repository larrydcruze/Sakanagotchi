/*
Physical Computing - basic distance sensor setup
This reads the value from the distance sensor in CM every 30 milliseconds
The sensor requires a small amount of time between reads to actually receive data
It uses a basic timer function to regulate the timing

*/



// Including the HCSR04 Ultrasonic Sensor library.
#include <HCSR04.h>
#include "Arduino_LED_Matrix.h"   //Include the LED_Matrix library
#include "fishcar.h"
#include "fishlegs.h"


// Defining pin numbers for the ultrasonic sensor.
byte triggerPin = 14; // Pin connected to the trigger pin of the sensor.
byte echoPin = 15;    // Pin connected to the echo pin of the sensor.

// Creating an instance of UltraSonicDistanceSensor to interact with the sensor.
UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);


// Variables to manage the timing of sensor readings.
unsigned long lastRead = 0; // The last time (in milliseconds) the sensor was read.
int rate = 30;              // The time interval (in milliseconds) between sensor readings.

// Variable to store the measured distance.
float distanceMeasured;

float changeThreshold = 9;


int currentState = 0;
int previousState = 1;


ArduinoLEDMatrix ledScreen;  
boolean loopAnimation = true;

// The setup function runs once when you press reset or power the board.
void setup () 
{
    Serial.begin(9600); // Initialize serial communication at 9600 bits per second.
    ledScreen.begin();
}

// The loop function runs over and over again forever.
void loop () 
{
   readDistanceSensor();

  if((currentState==1)&&(previousState!=1))
  {
    ledScreen.loadSequence(fishlegs);//add the name of your animation inside the ()
    ledScreen.play(loopAnimation);
  }
 
  if((currentState==0)&&(previousState!=0))
  {
    ledScreen.loadSequence(fishcar);//add the name of your animation inside the ()
    ledScreen.play(loopAnimation);
  }

previousState = currentState;
}




void readDistanceSensor()
{
      unsigned long currentTime = millis(); // Current time in milliseconds since the program started.
 
    // Check if the time interval since the last read is equal to or greater than the set rate.
    if((currentTime - lastRead) >= rate) 
    {
        lastRead = currentTime; // Update the last read time.
        distanceMeasured = distanceSensor.measureDistanceCm(); // Measure the distance.
        Serial.println(distanceMeasured); // Print the measured distance to the Serial monitor.
        if(distanceMeasured<=changeThreshold)
        {
          currentState = 1;
        }
        else
        {
          currentState = 0;
        }
      Serial.print(distanceMeasured); // Print the measured distance to the Serial monitor.
      Serial.print("\t"); //tab
      Serial.print("state : ");
      Serial.println(currentState);

    }
  
}

