void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Warte auf Daten von der Waage...");
}

void loop() {
  Serial1.write("w"); // send request to the scale
  delay(100);         // wait a bit for the scale to respond (adjust as needed)

  while (Serial1.available()) {
    char c = Serial1.read();
    Serial.print(c);
  }

  delay(500); // delay between requests (adjust based on how often you want to poll)
}