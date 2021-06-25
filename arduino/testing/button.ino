int LED = 8; //LED를 8번 핀에 연결
int button = 7; //버튼을 7번 핀에 연결

void setup() {
  Serial.begin(9600);
  
  pinMode(LED,OUTPUT); //LED를 출력으로 설정
  pinMode(button,INPUT); //버튼을 입력으로 설정
  
}

void loop() {
  int readValue = digitalRead(button); //버튼의 상태를 읽어와 변수에 저장
  Serial.println(readValue); //시리얼 모니터에 출력

  if(readValue == HIGH){ //버튼을 누르면(버튼 값이 HIGH면)
    digitalWrite(LED,HIGH); //LED에 불이 들어오고
  }
  else{//버튼 값이 LOW 이면
    digitalWrite(LED,LOW);  //LED에 불이 들어오지 않음
  }

}
