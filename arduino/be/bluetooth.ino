#include <SoftwareSerial.h> // 0,1번핀 제외하고 Serial 통신을 하기 위해 선언

// Serial 통신핀으로 D11번핀을 Rx로, D10번핀을 Tx로 선언
SoftwareSerial mySerial(11, 10); // HC-06 TX=11번핀 , RX=10번핀 연결

void setup()
{
 Serial.begin(9600); // 통신 속도 9600bps로 PC와 시리얼 통신 시작
 mySerial.begin(9600); // 통신 속도 9600bps로 블루투스 시리얼 통신 시작
}

void loop()
{
 // mySerial 핀에 입력이 들어오면, 바이트단위로 읽어서 PC로 출력
 if (mySerial.available()){
   Serial.write(mySerial.read());
 }
  // Serial 핀에 입력이 들어오면, 바이트단위로 읽어서 블루투스로 출력
 if (Serial.available()){
   mySerial.write(Serial.read());
 }
}
