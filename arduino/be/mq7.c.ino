int GasPin = A5;

void setup() {
  pinMode(GasPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(GasPin));

  delay(100);
}
