/**
*Merge _02_test_Dht11 & _01_test_03_ds1820
* 
*/

#include "configuration.h"
#include <SoftwareSerial.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

#define ONE_WIRE_BUS 3 /* Digitalport D3  (Pin #2) definieren */
#define dht_dpin A0 //DHT 11

#define UPDATE "GET /update?key="
#define PARAM1 "&field1="
#define GET UPDATE THING_SPEAK_API_KEY PARAM1

SoftwareSerial monitor(10, 11); // RX, TX

dht DHT;

OneWire ourWire(ONE_WIRE_BUS); /* Ini oneWire instance */
DallasTemperature sensors(&ourWire);/* Dallas Temperature Library für Nutzung der oneWire Library vorbereiten */


void setup(){
  monitor.begin(BAUDRATE);
  Serial.begin(BAUDRATE);  
  sensors.begin();/* Initialize  Dallas Temperature library */
  sensors.setResolution(TEMP_12_BIT); // Set precision  12-Bit
  sendDebug("AT");
  delay(5000);
  if(Serial.find("OK")){
    monitor.println("RECEIVED: OK");
    connectWiFi();
  };
  
}//end "setup()"

void loop(){

    DHT.read11(dht_dpin);  //Read from DHT11
    sensors.requestTemperatures(); // Read from DS1820
   
    char buffer[10];
    float tempC =(float) sensors.getTempFByIndex(0);
    tempC = DallasTemperature::toCelsius(tempC);
    String tempF = dtostrf(tempC, 4, 1, buffer);
    String tempDht = dtostrf(DHT.temperature, 4, 1, buffer);
    String humDht = dtostrf(DHT.humidity, 4, 1, buffer);
   
    updateTemp(tempF, tempDht, humDht);

    delay(60000);
}// end loop()


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
