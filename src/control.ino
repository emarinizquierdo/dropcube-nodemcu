void checkMode(){

  if (modeNextTime > millis()) {
    return;
  }

String path = "/MODE";
String id = "edu";

  mode = Firebase.getString(id + path);
  Serial.print(mode);
  modeNextTime = millis() + 5000;

}
