void setup() {

  Serial.begin(115200);

  Serial2.begin(1000000);
}

void loop() {

  while (Serial.available() > 0) {      // If anything comes in Serial (USB),
    Serial2.write(Serial.read());   // read it and send it out Serial2
    
  }

  while (Serial2.available() > 0) {     // If anything comes in Serial 2

    Serial.write(Serial2.read());   // read it and send it out Serial (USB)

  }
}
