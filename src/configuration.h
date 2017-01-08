#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266WiFiMulti.h>
#include "ESP8266WebServer.h"
#include <DNSServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <FirebaseArduino.h>

//Config constants
#define FIREBASE_HOST "dropcube-c11b6.firebaseio.com"
#define FIREBASE_AUTH "g8LHGVLv3QJ8yFBatXY1cmzS1tCkwEBY1qT6PIoo"

//RAINBOW CONSTANTS
#define BRIGHT    350     //max led intensity (1-500)
#define INHALE    1250    //Inhalation time in milliseconds.
#define PULSE     INHALE*1000/BRIGHT
#define REST      1000    //Rest Between Inhalations.

//STORM CONSTANTS
#define BETWEEN 30000
#define DURATION 200
#define TIMES 20
unsigned long lastTime = 0;
int waitTime = 0;

//Config vars
char dropcube_id[34] = "5692462144159744";

const int RED = D2;
const int GREEN = D4;
const int BLUE = D5;
const int GROUND = D3;

//Control vars
unsigned int modeNextTime = 0;
String modeValue = "NORMAL";
int hotValue;
int windValue;
int rainValue;
int snowValue;
bool stormValue;

//Rainbow vars
long value3;
long value2;
long value1;
long current_value3;
long current_value2;
long current_value1;
int x;


void config(){
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(RED, OUTPUT);   // LED pin as output.
  pinMode(GREEN, OUTPUT);   // LED pin as output.
  pinMode(BLUE, OUTPUT);   // LED pin as output.
  pinMode(GROUND, OUTPUT);

  digitalWrite(GROUND, HIGH);


  WiFiManagerParameter custom_dropcube_id("dropcubeid", "dropcube id", dropcube_id, 32);
  WiFiManager wifiManager;

  wifiManager.addParameter(&custom_dropcube_id);
  wifiManager.autoConnect("AutoConnectAP");

  Serial.println("connected...yeey :)");
  strcpy(dropcube_id, custom_dropcube_id.getValue());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  delay(1000);

}
