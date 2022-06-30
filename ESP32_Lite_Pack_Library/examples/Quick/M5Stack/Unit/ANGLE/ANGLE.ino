const int anglePin = 33; // M5StickC

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(anglePin, ANALOG);
}

void loop() {
  Serial.println(analogRead(anglePin));
  delay(500);
}
