
#include "configuration.h"
#include <SoftwareSerial.h>



#define UPDATE "GET /update?key="
#define PARAM1 "&field1="
#define GET UPDATE THING_SPEAK_API_KEY PARAM1

SoftwareSerial monitor(10, 11); // RX, TX

void setup()
{
  monitor.begin(BAUDRATE);
  Serial.begin(BAUDRATE);
  sendDebug("AT");
  delay(5000);
  if(Serial.find("OK")){
    monitor.println("RECEIVED: OK");
    connectWiFi();
  }
}


void loop(){

    updateTemp("1", "2", "3");
    delay(60000);
}

void updateTemp(String tenmpF, String tempDht, String humDht){
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  sendDebug(cmd);
  delay(2000);
  if(Serial.find("Error")){
    monitor.print("RECEIVED: Error");
    return;
  }
  cmd = GET;
  cmd += tenmpF;
  
  cmd+="&field2="+ tempDht;
    cmd+="&field3="+ humDht;
  
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  if(Serial.find(">")){
    monitor.print(">");
    monitor.print(cmd);
    Serial.print(cmd);
  }else{  
    sendDebug("AT+CIPCLOSE");
  }
  if(Serial.find("OK")){
    monitor.println("RECEIVED: OK");
  }else{
    monitor.println("RECEIVED: Error");
  }
}

void sendDebug(String cmd){
  monitor.print("SEND: ");
  monitor.println(cmd);
  Serial.println(cmd);
} 

boolean connectWiFi(){
  Serial.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  sendDebug(cmd);
  delay(5000);
  if(Serial.find("OK")){
    monitor.println("RECEIVED: OK");
    return true;
  }else{
    monitor.println("RECEIVED: Error");
    return false;
  }
}
