#include "Timer.h"
#include "SoftReset.h"


int i = 0;
int p = 0;
const int redLED = 10; //red led 10번 핀
const int greenLED = 9; // green led 9번핀
const int buzzer = 11; //부저 11번핀
const int smokePin = A5;//가스감지 센서 A5핀
const int flamePin = 13; //불꽃감지 센서 13번핀
const int button = 2;
long flame_interval = 1000;  //부저가 울리는 시간 간격
long smoke_interval = 1000; //
long flame_previousMillis = 0; //
long smoke_previousMillis = 0;

boolean curB = HIGH;
boolean lastB = HIGH;
boolean redB = HIGH;
boolean greenB = LOW;
boolean buzzerB = HIGH;

int Flame = HIGH;
int Smoke = 0;
int flag = 0;
int smokeSensorThres =250;

void setup() 
{
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokePin, INPUT);
  pinMode(flamePin, INPUT);
pinMode(button, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(0), button1, CHANGE);
  
  Serial.begin(9600);

}

void loop() {
  
  Flame = digitalRead(flamePin);
  Smoke = analogRead(smokePin);

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
// 현재 시간과 이전 시간을 비교해서, 1초가 되었는지 체크
  if(currentMillis - flame_previousMillis >= flame_interval) {
   flame_previousMillis = currentMillis;
    if(Flame == LOW) {
  tone(buzzer, 1000, 200);} // 불꽃이 감지 되면 부저가 울린다
}



}


void smoke_loop(){
unsigned long currentMillis = millis();// 현재 시간 값
// 현재 시간과 이전 시간을 비교해서, 1초가 되었는지 체크
if(currentMillis - smoke_previousMillis >= smoke_interval) {
smoke_previousMillis = currentMillis;
if(Smoke > smokeSensorThres) { //가스 농도가 일정 수준을 넘으면 가스 센서가 감지해서 led의 불이 green에서 red로 바뀐다.
digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);}
else{
  digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);}
}


}

void button1(){
  
  curB = digitalRead(button); //HIGH


if(digitalRead(redLED) && HIGH &&digitalRead(buzzer)==HIGH){   

if( lastB == HIGH && curB ==LOW){ 
redB=!redB;
greenB=!greenB;
buzzerB=!buzzerB;
 
     lastB = curB;
while (Smoke > smokeSensorThres && Flame == LOW){
     
      digitalWrite(redLED, redB);
      digitalWrite(greenLED, greenB);
      noTone(buzzer);
      delay(1000000);

      
 if(Flame == HIGH && Smoke < smokeSensorThres)
 break;

      soft_restart();
  }

}  
   }

  }
