//Check Mode Control
void checkMode(){

  if (modeNextTime > millis()) {
    return;
  }

  String mode_path = "/MODE";
  String hot_path = "/HOT";
  String wind_path = "/WIND";
  String rain_path = "/RAIN";
  String snow_path = "/SNOW";
  String storm_path = "/STORM";

  modeValue = Firebase.getString(dropcube_id + mode_path);

  if (!Firebase.success()) {
    Serial.print("getting value failed");
    modeValue = "NORMAL";
  }

  hotValue = Firebase.getString(dropcube_id + hot_path).toInt();

  if (!Firebase.success()) {
    Serial.print("getting value failed");
    hotValue = 0;
  }

  windValue = Firebase.getString(dropcube_id + wind_path).toInt();

  if (!Firebase.success()) {
    Serial.print("getting value failed");
    windValue = 0;
  }

  rainValue = Firebase.getString(dropcube_id + rain_path).toInt();

  if (!Firebase.success()) {
    Serial.print("getting value failed");
    rainValue = 0;
  }

  snowValue = Firebase.getString(dropcube_id + snow_path).toInt();

  if (!Firebase.success()) {
    Serial.print("getting value failed");
    snowValue = 0;
  }

  stormValue = Firebase.getString(dropcube_id + storm_path) == "true";

  if (!Firebase.success()) {
    Serial.print("getting value failed");
    stormValue = false;
  }

  Serial.println("Mode: " + modeValue);
  Serial.printf("Hot: %d\r\n", hotValue);
  Serial.printf("Wind: %d\r\n", windValue);
  Serial.printf("Rain: %d\r\n", rainValue);
  Serial.printf("Snow: %d\r\n", snowValue);
  Serial.printf("Storm: %d\r\n", stormValue);

  modeNextTime = millis() + 5000;

}
