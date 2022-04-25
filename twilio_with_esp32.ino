#include "twilio.hpp"

// Set these - but DON'T push them to GitHub!
static const char *ssid = "bond007";
static const char *password = "ddccbbaa";

// Values from Twilio (find them on the dashboard)
static const char *account_sid = " ";// your id on twilio
static const char *auth_token = " "; // auth token getting from twilio
// Phone number should start with "+<countrycode>"
static const char *from_number = " "; // twilio number

// You choose!
// Phone number should start with "+<countrycode>"
static const char *to_number = " "; // to number
static const char *message = "Location Co-ordinates: https://maps.google.com/?q=10.00200764110111,76.3173955897416 ";

Twilio *twilio;


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

void loop() {
}



