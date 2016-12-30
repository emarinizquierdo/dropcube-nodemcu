#include <Arduino.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


//#define LED     D0        // Led in NodeMCU at pin GPIO16 (D0).
#define BRIGHT    350     //max led intensity (1-500)
#define INHALE    1250    //Inhalation time in milliseconds.
#define PULSE     INHALE*1000/BRIGHT
#define REST      1000    //Rest Between Inhalations.

ESP8266WiFiMulti WiFiMulti;
char dropcube_id[34] = "YOUR_DROPCUBE_ID";

unsigned int nextTime = 0;    // Next time to contact the server

double light = 0;
int ledValue = 0;
int redValue = 0;
int greenValue = 0;

const int GREEN_LED_PIN = D0;
const int RED_LED_PIN = D5;

void setup() {

  pinMode(GREEN_LED_PIN, OUTPUT);   // LED pin as output.
  pinMode(D1, OUTPUT);
pinMode(RED_LED_PIN, OUTPUT);

    // put your setup code here, to run once:
    Serial.begin(115200);

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
}

void loop() {


    if (nextTime > millis()) {
        return;
    }

    light = retrieveLight();
    Serial.println("led value");
    Serial.println(light);
    setLEDLight(light);

    nextTime = millis() + 1800000;

}


double retrieveLight(){

  if((WiFiMulti.run() == WL_CONNECTED)) {

      HTTPClient http;

      Serial.print("[HTTP] begin...\n");
      // configure traged server and url
      //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
      Serial.print(dropcube_id);
      http.begin("http://thedropcubecom.appspot.com/s/lights/particle/1c0035000947343432313031"); //HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if(httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.printf("[HTTP] GET... code: %d\n", httpCode);

          // file found at server
          if(httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              Serial.println(payload);
          }
      } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
  }

}

void setLEDLight(double &value){


    ledValue = value * 255;

    if(ledValue == 0){

        redValue = 15;
        greenValue = 15;

    }else{

        greenValue = ledValue;
        redValue = 255-ledValue;

    }

    analogWrite(GREEN_LED_PIN, 1022);
    digitalWrite(D1, HIGH);
    analogWrite(RED_LED_PIN, redValue);
    Serial.printf("light %d\n", value);
    Serial.printf("green %d\n", greenValue);
    Serial.printf("red %d\n", redValue);
    //Particle.variable("light", value);
    //Particle.variable("green", greenValue);
    //Particle.variable("red", redValue);

/*
    //ramp increasing intensity, Inhalation:
    for (int i=1;i<BRIGHT;i++){
      analogWrite(LED, LOW);          // turn the LED on.
      delayMicroseconds(i*10);         // wait
      digitalWrite(LED, HIGH);         // turn the LED off.
      delayMicroseconds(PULSE-i*10);   // wait
      delay(0);                        //to prevent watchdog firing.
    }
    //ramp decreasing intensity, Exhalation (half time):
    for (int i=BRIGHT-1;i>0;i--){
      digitalWrite(LED, LOW);          // turn the LED on.
      delayMicroseconds(i*10);          // wait
      digitalWrite(LED, HIGH);         // turn the LED off.
      delayMicroseconds(PULSE-i*10);  // wait
      i--;
      delay(0);                        //to prevent watchdog firing.
    }
*/
}
