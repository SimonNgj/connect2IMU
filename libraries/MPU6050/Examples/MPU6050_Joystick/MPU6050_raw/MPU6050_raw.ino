
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t a[3];
float aux[4];
float newAngle[3];
int16_t anx, any;
int16_t i = 0;
int pushButtonL = 12;
int pushButtonR = 7;

#define LED_PIN 2
#define PI 	3.141592654
bool blinkState = false;

void setup() {

    Wire.begin();
    Serial.begin(9600);
    accelgyro.initialize();

    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
    pinMode(pushButtonL, INPUT);
    pinMode(pushButtonR, INPUT);
}

void loop() {
    //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    accelgyro.getAcceleration(&ax, &ay, &az);
//---------------------------- August --------------------------------
    	a[0] = ax;
    	a[1] = ay;
    	a[2] = az;

    	aux[3] = 0.0;
    	for(i=0;i<3;i++){
    	   aux[i] = a[i];
    	   aux[i] = aux[i]/1000.0;
    	   aux[3] += aux[i]*aux[i];
    	}

    	aux[3] = sqrt(aux[3]);

    	for(i=0;i<2;i++){
    	    newAngle[i]=((acos(aux[i]/aux[3])*180)/PI)-90;
    	}

    	anx = round(newAngle[0]);
    	any = round(-newAngle[1]);	
		
	int buttonStateL = digitalRead(pushButtonL);
        int buttonStateR = digitalRead(pushButtonR);
        int joyValue1 = analogRead(A4);
	
    Serial.println(String(anx)+" "+String(any)+ " "+ String(joyValue1)+" "+String(buttonStateL)+" "+String(buttonStateR));
    delay(100); 
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
