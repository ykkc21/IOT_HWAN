#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define STASSID "usamo"
#define STAPSK  "11111111"
#define SENSOR "95P86B"

const char *ssid = STASSID;
const char *password = STAPSK;
//와이파이 연결 password


const int redLED = 14;  //red LED를 GPIO14번(D5) 핀에 연결
const int greenLED = 12; //green LED를 GPIO12번(D6) 핀에 연결
const int buzzer = 0;  //피에조 부저를 GPIO0번(D3) 핀에 연결
const int smokePin = A0; //가스 센서를 아날로그0번 핀에 연결
const int flamePin = 5; //불꽃 센서를 GPIO5번(D1) 핀에 연결

long flame_interval = 100;  
long smoke_interval = 100;
long flame_previousMillis = 0;
long smoke_previousMillis = 0;

int Flame = HIGH; // 불꽃이 감지 되지 않았을 때 HIGH , 불꽃이 감지 되면 LOW
int Smoke = 0;
//int flag = 0;
int smokeSensorThres =450;//가스가 검출된 상태를 알기 위해 일정한 가스 수치 설정. 이 일정한 수치를 넘어서면 가스 검출된 상태

void wifi_connect() {
  Serial.begin(115200); //통신 속도 115200bps로 시리얼 통신 시작
  WiFi.mode(WIFI_STA); //WIFI모드를 WIFI_STA로 설정한다.
  WiFi.begin(ssid, password);//와이파이 접속
  Serial.println("");

 
  while (WiFi.status() != WL_CONNECTED) {//연결이 지연될 시에 시리얼 모니터에 '.' 출력
    delay(500);
    Serial.print(".");
  }

  //WIFI의 정보와 아이피 출력
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());//얻어온 IP주소를 시리얼 모니터에 출력
}

void setup() 
{
  pinMode(redLED, OUTPUT); //red LED를 출력으로 설정
  pinMode(greenLED, OUTPUT);//green LED를 출력으로 설정
  pinMode(buzzer, OUTPUT);//피에조 부저를 출력으로 설정
  pinMode(smokePin, INPUT); //가스 센서를 입력으로 설정
  pinMode(flamePin, INPUT);//불꽃 센서를 입력으로 설정
  
  Serial.begin(115200);//통신 속도 115200bps로 시리얼 통신 시작
  wifi_connect();  //와이파이 연결
  }

void loop() {
  
  Flame = digitalRead(flamePin); 
  Smoke = analogRead(smokePin);
//센서로 부터 읽은 값을 각각 변수에 저장

  Serial.print("flame : ");
  Serial.print(Flame);
  Serial.print(" smoke : ");
  Serial.println(Smoke);
//센서 값을 시리얼 모니터에 출력
  
  flame_loop();
  smoke_loop();
}

void flame_loop(){

unsigned long currentMillis = millis();// 현재 시간 값
  
  if(currentMillis - flame_previousMillis >= flame_interval) {
    // 현재 시간과 이전 시간을 비교해서, 1초가 되었는지 체크
    flame_previousMillis = currentMillis;
    
    if(Flame == LOW) {// 불꽃이 감지 되면 부저가 울린다
      tone(buzzer, 1000, 200); 

      //서버로 화재가 감지됨을 전송
      String url = "http://3.35.55.95:3030/arduino/sensor/95P86B/fire";
      wifi_send(url);
    }
  }
}


void smoke_loop(){
  unsigned long currentMillis = millis();// 현재 시간 값
  
  if(currentMillis - smoke_previousMillis >= smoke_interval) {
    // 현재 시간과 이전 시간을 비교해서, 1초가 되었는지 체크
    smoke_previousMillis = currentMillis;

    char s[10]; // 크기가 10인 char형 배열 선언
    sprintf(s, "%d", Smoke);//배열에 Smoke 값 

   //서버로 가스 값을 전송
    String url = "http://3.35.55.95:3030/arduino/sensor/95P86B/gas/";
    url = url + s;
    wifi_send(url);

    Serial.println(url);
    if(Smoke > smokeSensorThres || Flame == LOW) {
      //가스 수치가 일정 수준을 넘거나 불꽃이 감지가 되면 LED가 green에서 red로 색 변경
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
    }
    //가스나 불꽃이 감지되지 않으면 green 색을 유지
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
