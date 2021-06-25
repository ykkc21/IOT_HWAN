#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define STASSID "usamo"
#define STAPSK  "11111111"

const char *ssid = STASSID;
const char *password = STAPSK;
String url = "http://3.35.55.95:3030/arduino/room/101";

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

void setup() {
  wifi_connect();
}

void loop() {
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
  delay(10000);
}
