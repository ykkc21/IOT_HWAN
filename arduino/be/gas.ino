/*******
 
MQ2 센서 타입에 따라 출력값이 약간씩 상이하므로
가스 미검출 상태로 시리얼 모니터로 출력값 확인 후
int sensorThres = 550; 이부분을 적정한 수치로 변경후 테스트 하세요
www.ohmye.co.kr

*******/

int redLed = 10;
int greenLed = 9;
//int buzzer = 11;
int smokeA0 = A5;

// Your threshold value
int sensorThres = 550;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  //pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    //tone(buzzer, 1000, 200);
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    //noTone(buzzer);
  }
  delay(100);
}
