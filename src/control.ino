void checkMode(){

  if (modeNextTime > millis()) {
    return;
  }

String path = "/MODE";

  mode = Firebase.getString(dropcube_id + path);
  //TODO control errors.
  if (!Firebase.success()) {
      Serial.print("getting value failed");
      mode = "NORMAL";
  }

  Serial.print(mode);
  modeNextTime = millis() + 5000;

}
