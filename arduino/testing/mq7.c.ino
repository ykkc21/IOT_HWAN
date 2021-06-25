int GasPin = A5; //가스 센서 아날로그 5번핀 연결

void setup() {
  pinMode(GasPin, INPUT); //가스 센서를 입력으로 설정
  Serial.begin(9600);// 통신 속도 9600bps로 시리얼 통신 시작
}

void loop() {
  Serial.println(analogRead(GasPin)); //가스 센서로 부터 아날로그 값을 읽어온 뒤 시리얼 모니터에 센서 값을 출력

  delay(100);
}
