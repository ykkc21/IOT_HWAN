const int flamePin = 11; //불꽃 감지 센서를 11번 핀에 연결
int Flame = HIGH; // 불꽃이 감지 되지 않았을 때 HIGH , 불꽃이 감지 되면 LOW

void setup() 
{
  pinMode(flamePin, INPUT); //불꽃감지 센서를 입력으로 설정
  Serial.begin(9600);// 통신 속도 9600bps로 시리얼 통신 시작
}

void loop() 
{
  Flame = digitalRead(flamePin); //불꽃 감지 센서 값을 읽어옴

  Serial.println(Flame);  //읽어온 센서 값을 시리얼 모니터에 출력
  delay(100);
}
