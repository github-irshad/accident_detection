#include "twilio.hpp" // Twilio library

#include <Wire.h>
#include <Adafruit_Sensor.h>    // Adafruit  sensor library
#include <Adafruit_ADXL345_U.h> // ADXL345 library

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(); // ADXL345 Object


// WiFi Credentials
static const char *ssid = " ";
static const char *password = " ";

// Values from Twilio (find them on the dashboard)
static const char *account_sid = " ";
static const char *auth_token = " ";


// Phone number should start with "+<countrycode>"
static const char *from_number = " ";


// Phone number should start with "+<countrycode>"
static const char *to_number = " ";
static const char *message = "Your bike KL-11-XX-YYYY may got accident.Last location Co-ordinates: https://maps.google.com/?q=10.00200764110111,76.3173955897416 ";

Twilio *twilio;

float xaccel;
float yaccel;
float zaccel;

float roll,pitch;


void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi network ;");
  Serial.print(ssid);
  Serial.println("'...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }
  Serial.println("Connected!");

  //ADXL345 Starts here
  
  if (!accel.begin()) // if ASXL345 sensor not found
   {
      Serial.println("ADXL345 not detected");
      while (1)
         ;
   }

  
  
  



  
}

void loop() {

  sensors_event_t event;
   accel.getEvent(&event);

   xaccel = event.acceleration.x;
   yaccel = event.acceleration.y;
   zaccel = event.acceleration.z;

 
   Serial.println("******Acceleration Values*****");
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
   Serial.println("*************** ");
   delay(500);

   if(xaccel >= 3 || yaccel >= 2 ){
    RP_calculate(xaccel,yaccel,zaccel);
    float rollValue = roll;
    if(rollValue >= 75 || rollValue <= -75){
  
      
      // Twilio Connection Starts here
  twilio = new Twilio(account_sid, auth_token);
  String response;
  bool success = twilio->send_message(to_number, from_number, message, response);
  if (success) {
    Serial.println("Sent message successfully!");
  } else {
    Serial.println(response);
  }
      
      }
    }
}



float RP_calculate(float x_Buff,float y_Buff,float z_Buff)
{

  //float x, y, z;
         //Roll & Pitch are the angles which rotate by the axis X and y

  
   
  roll = atan2(y_Buff , z_Buff) * 57.3;
  pitch = atan2((- x_Buff) , sqrt(y_Buff * y_Buff + z_Buff * z_Buff)) * 57.3;

   
  Serial.println("*******Roll & Pitch******** ");
  Serial.print("Roll: ");
  Serial.println(roll);
  Serial.print("Pitch: ");
  Serial.println(pitch);
  

  return roll;
  
}

