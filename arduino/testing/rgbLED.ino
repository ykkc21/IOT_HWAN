int RED = 11;//red LED를 11번 핀에 연결
int GREEN = 10; //green LED를 10번 핀에 연결
int BLUE = 9;//blue LED를 9번 핀에 연결
  
void setup()
{
  pinMode(RED, OUTPUT);  //red LED를 출력으로 설정
  pinMode(GREEN, OUTPUT);//green LED를 출력으로 설정
  pinMode(BLUE, OUTPUT);  //blue LED를 출력으로 설정
}

//LED가 번갈아가면서 red, green, blue 색으로 변경
void loop()
{
  analogWrite(RED, 255); // RED ON
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 0);
  delay(1000);
   
  analogWrite(RED, 0);
  analogWrite(GREEN, 255); // GREEN ON
  analogWrite(BLUE, 0);  
  delay(1000);
 
  analogWrite(RED, 0);
  analogWrite(GREEN, 0);
  analogWrite(BLUE, 255);    // BLUE ON
  delay(1000);
}
 
