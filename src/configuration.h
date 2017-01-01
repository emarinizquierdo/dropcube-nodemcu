#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266WiFiMulti.h>
#include "ESP8266WebServer.h"
#include <DNSServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "dropcube-c11b6.firebaseio.com"
#define FIREBASE_AUTH "g8LHGVLv3QJ8yFBatXY1cmzS1tCkwEBY1qT6PIoo"
#define DROPCUBE_ID "edu"

/* MODE CONTROL */
unsigned int modeNextTime = 0;
String mode = "NORMAL";




//#define LED     D0        // Led in NodeMCU at pin GPIO16 (D0).
#define BRIGHT    350     //max led intensity (1-500)
#define INHALE    1250    //Inhalation time in milliseconds.
#define PULSE     INHALE*1000/BRIGHT
#define REST      1000    //Rest Between Inhalations.

//Strom useful
#define BETWEEN 30000
#define DURATION 200
#define TIMES 20
unsigned long lastTime = 0;
int waitTime = 0;


char dropcube_id[34] = "YOUR_DROPCUBE_ID";

const int RED = D2;
const int GREEN = D4;
const int BLUE = D5;
const int GROUND = D3;

int red;
int green;
int blue;


/* Color fading */

long value3;
long value2;
long value1;

long current_value3;
long current_value2;
long current_value1;

int x;

/* End color fading */



void config(){
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(RED, OUTPUT);   // LED pin as output.
  pinMode(GREEN, OUTPUT);   // LED pin as output.
  pinMode(BLUE, OUTPUT);   // LED pin as output.
  pinMode(GROUND, OUTPUT);

  digitalWrite(GROUND, HIGH);


  WiFiManagerParameter custom_dropcube_id("dropcubeid", "dropcube id", dropcube_id, 32);


  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset saved settings
  //wifiManager.resetSettings();

  //set custom ip for portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  wifiManager.addParameter(&custom_dropcube_id);
  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();


  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  strcpy(dropcube_id, custom_dropcube_id.getValue());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(1000);

  value1 = random(1023);
  current_value1 = value1;
  value2 = random(1023);
  current_value2 = value2;
  value3 = random(1023);
  current_value3 = value3;
}
