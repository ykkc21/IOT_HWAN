const int redLED = 10;
const int greenLED = 9;
const int buzzer = 11;
const int smokePin = A5;
const int flamePin = 13;

int Flame = HIGH;
int Smoke = 0;

int smokeSensorThres = 450;

void setup() 
{
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokePin, INPUT);
  pinMode(flamePin, INPUT);

  Serial.begin(9600);
}

void loop() {
  Flame = digitalRead(flamePin);
  Smoke = analogRead(smokePin);

  Serial.print("flame : ");
  Serial.print(Flame);
  Serial.print(" smoke : ");
  Serial.println(Smoke);

  if(Flame == LOW)
  {
    tone(buzzer, 1000, 200);
  }

  if(Smoke > smokeSensorThres)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  }
  else
  {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
  delay(100);
}
