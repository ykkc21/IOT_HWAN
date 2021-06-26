#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define STASSID "usamo"
#define STAPSK  "11111111"
#define SENSOR "95P86B"

const char *ssid = STASSID;
const char *password = STAPSK;

int i = 0;
int p = 0;
const int redLED = 14;  //D5
const int greenLED = 12; //D6
const int buzzer = 0;  //D3
const int smokePin = A0;
const int flamePin = 5; //D1
long flame_interval = 100;  //부저가 울리는 시간 간격
long smoke_interval = 100; //
long flame_previousMillis = 0; //
long smoke_previousMillis = 0;

int Flame = HIGH;
int Smoke = 0;
int flag = 0;
int smokeSensorThres =450;

void wifi_connect() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // WIFI 연결될 때까지 대기
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //WIFI의 정보와 아이피 출력
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() 
{
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokePin, INPUT);
  pinMode(flamePin, INPUT);
  
  Serial.begin(115200);
  wifi_connect();
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
}

void flame_loop(){

unsigned long currentMillis = millis();// 현재 시간 값
  // 현재 시간과 이전 시간을 비교해서, 1초가 되었는지 체크
  if(currentMillis - flame_previousMillis >= flame_interval) {
    flame_previousMillis = currentMillis;
    if(Flame == LOW) {
      tone(buzzer, 1000, 200); // 불꽃이 감지 되면 부저가 울린다
      String url = "http://3.35.55.95:3030/arduino/sensor/95P86B/fire";
      wifi_send(url);
    }
  }
}


void smoke_loop(){
  unsigned long currentMillis = millis();// 현재 시간 값
  // 현재 시간과 이전 시간을 비교해서, 1초가 되었는지 체크
  if(currentMillis - smoke_previousMillis >= smoke_interval) {
    smoke_previousMillis = currentMillis;

    char s[10];
    sprintf(s, "%d", Smoke);
    
    String url = "http://3.35.55.95:3030/arduino/sensor/95P86B/gas/";
    url = url + s;
    wifi_send(url);

    Serial.println(url);
    if(Smoke > smokeSensorThres || Flame == LOW) { //가스 농도가 일정 수준을 넘으면 가스 센서가 감지해서 led의 불이 green에서 red로 바뀐다.
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
    }
    else{
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
    }
  }
 }

 void wifi_send(String url){
  //와이파이가 연결되었는지 확인
  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    //url로 http 통신 시작
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, url)) {  // HTTP

      //http에서 응답코드 받아옴
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        
        //서버에서 값 받아옴
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      }
      else {
        //오류
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      //통신 종료
      http.end();
    } else {
      //서버에 연결할 수 없음
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  //통신 속도 조절
  delay(500);
 }
