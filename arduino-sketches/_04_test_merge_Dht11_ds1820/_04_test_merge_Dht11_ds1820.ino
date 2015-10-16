/**
*Merge _02_test_Dht11 & _01_test_03_ds1820
* 
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <dht.h>

#define ONE_WIRE_BUS 3 /* Digitalport D3  (Pin #2) definieren */
#define dht_dpin A0 //DHT 11

dht DHT;
OneWire ourWire(ONE_WIRE_BUS); /* Ini oneWire instance */
DallasTemperature sensors(&ourWire);/* Dallas Temperature Library für Nutzung der oneWire Library vorbereiten */


void setup(){
  Serial.begin(9600);  
  delay(300);//Let system settle
  Serial.println("Setup");
  sensors.begin();/* Initialize  Dallas Temperature library */
  sensors.setResolution(TEMP_12_BIT); // Set precision  12-Bit
  delay(700);//Wait rest of 1000ms recommended delay before
  //accessing sensor
}//end "setup()"

void loop(){

    DHT.read11(dht_dpin);  //Read from DHT11
    sensors.requestTemperatures(); // Read from DS1820

    logValue("DHT11 ", DHT.humidity, " % humidity");
    logValue("DHT11 ", DHT.temperature, " C temperature");
    logValue("DS1820",sensors.getTempCByIndex(0) , " C temperature");
   
   
    delay(800);//Don't try to access too frequently... in theory
}// end loop()


void logValue(String SensorName, double value, String unit){
  Serial.print(SensorName + " " );
  Serial.print( value  );
  Serial.print(" " + unit);
  Serial.println("");
}
