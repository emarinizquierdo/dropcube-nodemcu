#include "configuration.h"


void setup() {

  config();

}

void loop() {

  checkMode();

  if(modeValue == "RAINBOW"){

    rainbow();

  }else if(modeValue == "TEST_HOT"){

    hot(1023);

  }else if(modeValue == "TEST_RAIN"){

    rain(1023);

  }else if(modeValue == "TEST_SNOW"){

    snow(1023);

  }else if(modeValue == "TEST_STORM"){

    rain(1023);
    storm();

  }else if(modeValue == "TEST_WIND"){

    wind(1023);

  }else{

    if(snowValue > 0){

      snow(snowValue);
      if(stormValue){
        storm();
      }

    }else if(rainValue > 0){

      rain(rainValue);
      if(stormValue){
        storm();
      }

    }else if(hotValue > 0){

      hot(hotValue);

    }else if(windValue > 0){

      wind(windValue);

    }else{

      snow(0);
      rain(0);
      hot(0);
      wind(0);

    }
  }
}


void setLEDLight(int led, int value){

    analogWrite(led, value);
    Serial.printf("led %d %d\n", led, value);

}
