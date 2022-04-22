#include <Wire.h>
#include <Adafruit_Sensor.h>    // Adafruit  sensor library
#include <Adafruit_ADXL345_U.h>  // ADXL345 library

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();   // ADXL345 Object

float xaccel;
float yaccel;
float zaccel;
                       

void setup() {

  Serial.begin(9600);
  if(!accel.begin())   // if ASXL345 sensor not found
  {
    Serial.println("ADXL345 not detected");
    while(1);
  }

}

void loop() {

 sensors_event_t event;
 accel.getEvent(&event);
 
 xaccel = event.acceleration.x;
 yaccel = event.acceleration.y;
 zaccel = event.acceleration.z;
 
 Serial.print("X: ");
 Serial.print(xaccel);
 Serial.print("  ");
  Serial.print("Y: ");
 Serial.print(yaccel);
 Serial.print("  ");
  Serial.print("Z: ");
 Serial.print(zaccel);
 Serial.print("  ");
 Serial.println("m/s^2 ");
 delay(1000);

 RP_calculate(xaccel,yaccel,zaccel);
 
 delay(1000);
 
 }



float RP_calculate(float x_Buff,float y_Buff,float z_Buff)
{

  //float x, y, z;
  float roll,pitch;       //Roll & Pitch are the angles which rotate by the axis X and y

  
   
  roll = atan2(y_Buff , z_Buff) * 57.3;
  pitch = atan2((- x_Buff) , sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;

   

  Serial.print("Roll: ");
  Serial.println(roll);
  Serial.print("Pitch: ");
  Serial.println(pitch);
  
}
