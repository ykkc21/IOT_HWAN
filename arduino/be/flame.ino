const int flamePin = 11;
int Flame = HIGH;

void setup() 
{
  pinMode(flamePin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  Flame = digitalRead(flamePin);

  Serial.println(Flame);
  delay(100);
}
