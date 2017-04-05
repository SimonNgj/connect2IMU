
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "MspFlash.h"
#include "ProbA.h"

#define flash SEGMENT_D

MPU6050 accelgyro;

int16_t ax, ay, az;
//int16_t a[3];
//float aux[4];
int16_t i = 0, j=0;
//int pushButtonL = 12;
//int pushButtonR = 7;
unsigned char p = 0;

#define LED_PIN 2
#define PI 	3.141592654
bool blinkState = false;

void setup() {

    Wire.begin();
    Serial.begin(9600);
    accelgyro.initialize();

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
    //pinMode(pushButtonL, INPUT);
    //pinMode(pushButtonR, INPUT);
}

void loop() {
    accelgyro.getAcceleration(&ax, &ay, &az);
//-------------------- November ----------------------
    if(i<400){
      Flash.write(flash+i, (unsigned char*)ax, 5);
      //Flash.write(flash, (unsigned char*)ay, 5);
      //Flash.write(flash, (unsigned char*)az, 5);
    }
    i++;
//----------------------------------------------------
    //Serial.println(String(ax)+" "+String(ay)+ " "+ String(az));
    if(i>420&&i<500)
    {
      Flash.read(flash+j, &p, 5);
      Serial.println(p);
    }
//----------------------------------------------------
    delay(100); 
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
