#include "configuration.h"



void setup() {

  config();

}

void loop() {

  checkMode();
  if(mode == "RAINBOW"){
    rainbow();
  }else if(mode == "TEST_HOT"){
    hot(1023);
  }else if(mode == "TEST_RAIN"){
    rain(1023);
  }else if(mode == "TEST_SNOW"){
    snow(1023);
  }else if(mode == "TEST_STORM"){
    storm();
  }else if(mode == "TEST_WIND"){
    wind(1023);
  }
/*
    case "RAINBOW" :


    break;
    case "TEST_HOT" :
hot(1023);

    break;
    case "TEST_SNOW" :


    break;
    case "TEST_WIND" :


    break;
    case "TEST_STORM" :


    break;
    default: //NORMAL

    break;
  }
*/


/*
    red = Firebase.getFloat("red");
    green = Firebase.getFloat("green");
    blue = Firebase.getFloat("blue");

    setLEDLight(RED, red);
    setLEDLight(GREEN, green);
    setLEDLight(BLUE, blue);
*/
    //delay(1000);
    //storm();

    /*
    setLEDLight(RED, red);
    setLEDLight(GREEN, green);
    setLEDLight(BLUE, blue);
    */

}


void setLEDLight(int led, int value){

    analogWrite(led, value);
    Serial.printf("led %d %d\n", led, value);

}
