/*****************************************************************
This Arduino sketch will demo the following:
* Read the gyroscope, accelerometer, and magnetometer
  using the readGryo(), readAccel(), readMag() functions and 
  the gx, gy, gz, ax, ay, az, mx, my, and mz variables.
* Calculate actual acceleration, rotation speed, 
  magnetic field strength using the calcAccel(), calcGyro() 
  and calcMag() functions.
* Use the data from the LSM9DS1 to calculate 
  orientation and heading.
*****************************************************************/
#include <Wire.h>
#include <SparkFunLSM9DS1.h>

LSM9DS1 imu;

#define LSM9DS1_M 0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW
#define PRINT_SPEED 50 // 50 ms between prints
static unsigned long lastPrint = 0; // Keep track of print time

// Earth's magnetic field varies by location. Add or subtract 
// a declination to get a more accurate heading. Calculate your's here:
// http://www.ngdc.noaa.gov/geomag-web/#declination
#define DECLINATION -8.58 // Declination (degrees) in Boulder, CO.

void setup() 
{
  Serial.begin(9600);
  
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;

  if (!imu.begin())
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    while (1) ;
  }
}

void loop()
{
  if ( imu.gyroAvailable() & imu.accelAvailable() & imu.magAvailable() )
  {
    imu.readGyro();
    imu.readAccel();
    imu.readMag();
  }
  
  if ((lastPrint + PRINT_SPEED) < millis())
  {
    //printGyro();  // Print "G: gx, gy, gz"
    //printAccel(); // Print "A: ax, ay, az"
    //printMag();   // Print "M: mx, my, mz"

    printAttitude(imu.ax, imu.ay, imu.az, -imu.my, -imu.mx, imu.mz);
    
    lastPrint = millis(); // Update lastPrint time
  }
}

void printGyro()
{
  Serial.print(imu.gx);
  Serial.print(", ");
  Serial.print(imu.gy);
  Serial.print(", ");
  Serial.println(imu.gz);
}

void printAccel()
{  
  Serial.print(imu.ax);
  Serial.print(", ");
  Serial.print(imu.ay);
  Serial.print(", ");
  Serial.println(imu.az);
}

void printMag()
{  
  Serial.print(imu.mx);
  Serial.print(", ");
  Serial.print(imu.my);
  Serial.print(", ");
  Serial.println(imu.mz);
}

// Calculate pitch, roll, and yaw.
void printAttitude(float ax, float ay, float az, float mx, float my, float mz)
{
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));
  float yaw;
  
  if (my == 0)
    yaw = (mx < 0) ? PI : 0;
  else
    yaw = atan2(mx, my);
   
  yaw -= DECLINATION * PI / 180;
  
  if (yaw > PI) yaw -= (2 * PI);
  else if (yaw < -PI) yaw += (2 * PI);
  else if (yaw < 0) yaw += 2 * PI;
  
  // Convert everything from radians to degrees:
  yaw *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll  *= 180.0 / PI;
  
  Serial.print(int16_t(pitch));
  Serial.print(",");
  Serial.print(int16_t(roll));
  Serial.print(",");
  Serial.print(int16_t(yaw));
  Serial.print(",");
  Serial.print(-1);
  Serial.print(" \n");
}
