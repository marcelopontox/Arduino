#include <SoftwareSerial.h>
char c;
bool flag = true;
String data;
SoftwareSerial altPort(5,6);
unsigned int cnt = 0;
unsigned int tCnt = 0;

void setup() {
  // put your setup code here, to run once:
  altPort.begin(9600);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Begin Test");  
  altPort.println("AT");
  delay(100);
  altPort.println("AT+CWJAP=\"CoolDog\",\"86053436\"");
  getWifiInfo();
  delay(5000);
  update1();
}


void loop() {
  // put your main code here, to run repeatedly:
  getWifiInfo();
  getCmd();
}

void getWifiInfo(){
  if (altPort.available()) {
    data = "";
    cnt = 0;
    tCnt = 0;
    Serial.print("Get Wifi response:");
    while (altPort.available()) {
      c = altPort.read();
      cnt++;
      tCnt++;
      data += c;
      if (cnt >= 32) {
        //delay(100);
        //Serial.println(data);
        cnt = 0;
        data = "";
      }
    }
    Serial.println(data);
    Serial.println(tCnt);
  }
}

void getCmd(){
  if (Serial.available()) {
    data = "";
    flag = true;
    while (Serial.available()) {
      c = (char)Serial.read();
      //Serial.println(c);
      /*
      if(c == '\n' && data.equals("datasent")){
        update1();
        flag=false;
        data = "";
        break;
      }
      */
      data += c;
    }
    Serial.print("Send AT:");
    if (flag)altPort.println(data);
    Serial.println(data);
  }
}
void update1() {
  /*
  altPort.println("AT+CIPCLOSE");
  delay(500);
  */
  Serial.print("In AT Cmd:");
  altPort.println("AT+CIPMUX=1");
  delay(2000);
  getWifiInfo();
  altPort.println("AT+CIPSTART=4,\"TCP\",\"materonep001.sinaapp.com\",80");
  delay(2000);
  getWifiInfo();
  altPort.println("AT+CIPSEND=4,77");
  delay(2000);
  getWifiInfo();
  altPort.print("GET /homestatus.php?h=9888&t=8889 HTTP/1.1\r\n");
  delay(1000);
  getWifiInfo();
  altPort.print("host:materonep001.sinaapp.com\r\n");
  delay(1000);
  getWifiInfo();
  altPort.print("\r\n");
  getWifiInfo();
}
