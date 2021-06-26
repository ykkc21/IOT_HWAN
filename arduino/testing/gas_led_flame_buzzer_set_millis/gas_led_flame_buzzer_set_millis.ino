//아두이노에서 물리적인 버튼을 사용하지 않고 일정시간마다 리셋하기 위한 라이브러리
#include "Timer.h"
#include "SoftReset.h"

const int redLED = 10; //red LED를 10번 핀에 연결
const int greenLED = 9; // green LED를 9번 핀에 연결
const int buzzer = 11; //피에조 부저를 11번 핀에 연결
const int smokePin = A5;//가스 감지 센서를 아날로그 5번 핀에 연결
const int flamePin = 13; //불꽃 감지 센서 13번 핀에 연결
const int button = 2;//버튼을 2번 핀에 연결

//millis()함수 사용 위한 변수들 
//현재 시간과 이전 시간을 비교하기 위한 interval
long flame_interval = 1000;
long smoke_interval = 1000; 

long flame_previousMillis = 0; 
long smoke_previousMillis = 0;

//버튼 토글 관련 변수들
boolean curB = HIGH; 
boolean lastB = HIGH; 
boolean redB = HIGH;
boolean greenB = LOW;
boolean buzzerB = HIGH;

int Flame = HIGH; // 불꽃이 감지 되지 않았을 때 HIGH , 불꽃이 감지 되면 LOW
int Smoke = 0; //가스 값

//가스가 검출된 상태를 알기 위해 일정한 가스 수치 설정
//이 일정한 수치를 넘어서면 가스 검출된 상태
int smokeSensorThres =250; 

void setup() 
{
  pinMode(redLED, OUTPUT); //red LED를 출력으로 설정
  pinMode(greenLED, OUTPUT);//green LED를 출력으로 설정
  pinMode(buzzer, OUTPUT);//피에조 부저를 출력으로 설정
  pinMode(smokePin, INPUT);//가스 센서를 입력으로 설정
  pinMode(flamePin, INPUT);//불꽃 감지 센서를 입력으로 설정
  pinMode(button, INPUT_PULLUP);//버튼을 입력으로 설정

  //인터럽트를 등록.핀의 상태가 바뀔 경우(LOW->HIGH, HIGH->LOW 둘 다 포함) button1 함수 실행
  attachInterrupt(digitalPinToInterrupt(0), button1, CHANGE); 
  
  Serial.begin(9600);
}

void loop() {

  //각각의 센서 값을 변수에 저장
  Flame = digitalRead(flamePin);
  Smoke = analogRead(smokePin);

  //센서 값들을 시리얼 모니터에 출력
  Serial.print("flame : ");
  Serial.print(Flame);
  Serial.print(" smoke : ");
  Serial.println(Smoke);
  
  flame_loop();
  smoke_loop();
  button1();
}

void flame_loop(){

  unsigned long currentMillis = millis();// 현재 시간 값

  if(currentMillis - flame_previousMillis >= flame_interval) {
    // 현재 시간과 이전 시간을 비교해서, 1초가 되었는지 체크
   flame_previousMillis = currentMillis;
   if(Flame == LOW) {
  tone(buzzer, 1000, 200);} // 불꽃이 감지 되면 부저 울림
  }
}

void smoke_loop(){
  unsigned long currentMillis = millis();// 현재 시간 값

  if(currentMillis - smoke_previousMillis >= smoke_interval) {
    // 현재 시간과 이전 시간을 비교해서, 1초가 되었는지 체크
    smoke_previousMillis = currentMillis;

    //가스 센서로 읽어온 값이 일정 수치 이상이면 가스 검출된 상태 이므로
    //LED 가 red에서 green으로 색을 변경
   if(Smoke > smokeSensorThres) { 
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);}

    //가스 미검출 상태 이면 LED는 green을 유지
    else{
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);}
  }
}

void button1(){
  
  curB = digitalRead(button); //버튼의 상태값을 읽어 변수에 저장

  //가스와 불꽃이 감지되어 LED가 red, 피에조 부저가 울리면
  if(digitalRead(redLED) == HIGH &&digitalRead(buzzer)==HIGH){ 
 
  //버튼의 상태가 바뀌었는지 판단하여 변수들의 상태를 이전과 반대 상태로 변환
  if( lastB == HIGH && curB ==LOW){
    
    redB=!redB;
    greenB=!greenB;
    buzzerB=!buzzerB;
 
    lastB = curB;//현재 상태 값을 lastB변수에 저장
    
    //가스 미검출 상태, 불꽃이 감지 되지 않으면 LED상태 green으로 변경, 피에조 OFF 
    while (Smoke > smokeSensorThres && Flame == LOW){
    
      digitalWrite(redLED, redB);
      digitalWrite(greenLED, greenB);
      noTone(buzzer);
      delay(1000000);

     //일정 시간 지난 뒤 프로그램 재시작
      soft_restart();
     }
    }  
   }
  }
