///////////////////////////////////////////////////////////////////////////////////////
//THhis code demo how to set sample rate of IMU sensors with Arduino 

#include <Wire.h>

int gyro_x, gyro_y, gyro_z;
long acc_x, acc_y, acc_z;
long loop_timer;
int temp;
int i = 0;
void setup_mpu_6050_registers();
void read_mpu_6050_data();

void setup() {
  Wire.begin();                                                        //Start I2C as master
  setup_mpu_6050_registers();                                          //Setup the registers of the MPU-6050   
  delay(30);                                             
  Serial.begin(115200);
  loop_timer = micros();                                               //Reset the loop timer
}

void loop(){

  read_mpu_6050_data();   

  // ----------- Print output -----------
  Serial.print(i); Serial.print(",");
  Serial.print(int16_t(acc_x)); Serial.print(",");
  Serial.print(int16_t(acc_y)); Serial.print(",");
  Serial.print(int16_t(acc_z)); Serial.print(",");
  Serial.print(int16_t(gyro_x)); Serial.print(",");
  Serial.print(int16_t(gyro_y)); Serial.print(",");
  Serial.print(int16_t(gyro_z)); 
  Serial.print("\n");

 while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
 loop_timer = micros();//Reset the loop timer
  i++;
}

void setup_mpu_6050_registers(){
  //Activate the MPU-6050
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x6B);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  Wire.endTransmission();                                             
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1C);                                                    //Send the requested starting register
  Wire.write(0x10);                                                    //Set the requested starting register
  Wire.endTransmission();                                             
  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1B);                                                    //Send the requested starting register
  Wire.write(0x08);                                                    //Set the requested starting register
  Wire.endTransmission();                                             
}

void read_mpu_6050_data(){                                             //Subroutine for reading the raw gyro and accelerometer data
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  acc_x = Wire.read()<<8|Wire.read();                                  
  acc_y = Wire.read()<<8|Wire.read();                                  
  acc_z = Wire.read()<<8|Wire.read();                                  
  temp = Wire.read()<<8|Wire.read();                                   
  gyro_x = Wire.read()<<8|Wire.read();                                 
  gyro_y = Wire.read()<<8|Wire.read();                                 
  gyro_z = Wire.read()<<8|Wire.read();                                 
}