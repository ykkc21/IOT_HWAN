const int redLED = 10; //red LED를 10번 핀에 연결
const int greenLED = 9; //green LED를 9번 핀에 연결
const int buzzer = 11; //피에조 부저를 11번 핀에 연결
const int smokePin = A5; // 가스 센서를 아날로그 5번 핀에 연결
const int flamePin = 13; // 불꽃 센서를 13번 핀에 연결


int Flame = HIGH; // 불꽃이 감지 되지 않았을 때 HIGH , 불꽃이 감지 되면 LOW
int Smoke = 0;

//가스가 검출된 상태를 알기 위해 일정한 가스 수치 설정
//이 일정한 수치를 넘어서면 가스 검출된 상태
int smokeSensorThres = 450;

void setup() 
{
  pinMode(redLED, OUTPUT);//red LED를 출력으로 설정
  pinMode(greenLED, OUTPUT);//green LED를 출력으로 설정
  pinMode(buzzer, OUTPUT);//피에조 부저를 출력으로 설정
  pinMode(smokePin, INPUT); //가스 센서를 입력으로 설정
  pinMode(flamePin, INPUT);//불꽃 센서를 입력으로 설정

  Serial.begin(9600);// 통신 속도 9600bps로 시리얼 통신 시작
}

void loop() {
  //불꽃 센서, 가스 센서의 값을 각각 디지털과 아날로그 값으로 읽어서 변수에 저장
  Flame = digitalRead(flamePin); 
  Smoke = analogRead(smokePin);


  Serial.print("flame : ");
  Serial.print(Flame);//시리얼 모니터에 불꽃 센서 값 출력
  Serial.print(" smoke : ");
  Serial.println(Smoke);//시리얼 모니터에 가스 센서 값 출력

  if(Flame == LOW) //불꽃이 감지되면
  {
    tone(buzzer, 1000, 200); //부저가 울림
  }
  
//가스 센서로 읽어온 값이 일정 수치 이상이면 가스 검출된 상태 이므로
//LED 가 red에서 green으로 색을 변경
  if(Smoke > smokeSensorThres){
    digitalWrite(redLED, HIGH); 
    digitalWrite(greenLED, LOW);
  }
  
  //가스 미검출 상태 이면 LED는 green을 유지 하고 피에조 부저에 소리가 울리지 않음
  else{
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
  delay(100);
}
