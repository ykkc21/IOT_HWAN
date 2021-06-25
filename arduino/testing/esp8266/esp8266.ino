#include <ESP8266WiFi.h>// WIFI 라이브러리

const char* ssid = "bohyun";
const char* password = "19991108";
//와이파이 접속 password

WiFiServer server(80);//HTTP 통신은 80번 포트를 사용

void setup() {
  Serial.begin(9600); // 통신 속도 9600bps로 시리얼 통신 시작
  delay(10);

  pinMode(2, OUTPUT);// GPIO2를 2번 핀에 연결
  digitalWrite(2, 0);
  
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  
  WiFi.begin(ssid, password); //와이파이에 연결
  
  while (WiFi.status() != WL_CONNECTED) {//연결이 지연될 시에 시리얼 모니터에 '.' 출력
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");//접속되었으면 연결 확인
 
  
  server.begin();
  Serial.println("Server started"); // 서버 연결 시작

  Serial.println(WiFi.localIP()); //얻어온 IP주소를 시리얼 모니터에 출력
}

void loop() { // 클라이언트(사용자)가 접속을 했을때
  WiFiClient client = server.available();
  if (!client) {
    return; //클라이언트로(사용자)로부터 응답이 없으면 return
  }
  
  // 클라이언트가 데이터를 전송할 때 까지 기다림
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // 사용자가 전송한 리퀘스트 헤더를 읽음
  String req = client.readStringUntil('\r');//Wr은 문장의 끝을 알려줌. 문장씩 읽어들임
  Serial.println(req);
  client.flush();//데이터가 전송완료가 될 때까지 기다림
  
  // 리퀘스트 헤더에 저희가 필요로 하는 요청이 들어있는지 확인
  int val;
  if (req.indexOf("/gpio/0") != -1)// /gplo/0 이면 0으로 세팅
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)// /gpio/1 이면 1로 세팅
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  digitalWrite(2, val);// 요청한 내용대로 해당 디지털 핀을 제어
  
  client.flush();

  String s = "GET /process/login?id=inbin HTTP/1.0\r\n\r\n ";
  s += (val)?"high":"low";
  s += "</html>\n";// 결과 출력



  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}
