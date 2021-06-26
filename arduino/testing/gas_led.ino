
int redLed = 10; //red LED를 10번 핀에 연결
int greenLed = 9; //green LED를 9번 핀에 연결
int smokeA0 = A5; //가스 센서를 아날로그5번 핀에 연결

//가스가 검출된 상태를 알기 위해 일정한 가스 수치 설정
//이 일정한 수치를 넘어서면 가스 검출된 상태
int sensorThres = 550; 

void setup() {
  pinMode(redLed, OUTPUT); //red LED를 출력으로 설정
  pinMode(greenLed, OUTPUT);//green LED를 출력으로 설정
  pinMode(smokeA0, INPUT); //가스 센서를 입력으로 설정
  Serial.begin(9600); // 통신 속도 9600bps로 시리얼 통신 시작
}

void loop() {
  int analogSensor = analogRead(smokeA0); //가스 센서 값 변수에 저장

  Serial.print("Pin A0: ");
  Serial.println(analogSensor); // 읽어온 값을 시리얼 모니터에 출력
  
  //가스 센서로 읽어온 값이 일정 수치 이상이면 가스 검출된 상태 이므로
  //LED 가 red에서 green으로 색을 변경
  if (analogSensor > sensorThres) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
  } 
  
  //가스가 미검출 상태 이면 LED는 green을 유지
  else{
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
  }
  delay(100);
}
