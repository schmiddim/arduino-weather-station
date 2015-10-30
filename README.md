#Arduino Weatherstation

I describe here my Inhouse Weatherstation Project.
Most parts of the Code are copied. Check the comments 

![Image of the circuit](./images/circuit.jpg "Station with Arduino Nano")

##What does it make?
The circuit measures temperature and humidity. The results are pushed to [Thingspeak](https://thingspeak.com/channels/63329) over WLAN!
##What do I need? 
##Hardware
* Arduino Nano 
* DS18B20   (Temperature)
* DHT11     (Humidity, Temperature)
* [ESP8266](http://www.amazon.de/gp/product/B00QIAE74Q/ref=as_li_tl?ie=UTF8&camp=1638&creative=19454&creativeASIN=B00QIAE74Q&linkCode=as2&tag=unerklamrande-21)   (Wlan)
This is an online

##Software
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [Fritzing](http://fritzing.org/home/) for viewing the diagrams

##Cloud Service 
You need a channel at Thingspeak - it's for free. Create a channel and use the Write API Key

##How to use the code
This repository contains 6 Arduino sketches. The code is in the **arduino-sketches** folder. 
The wiring diagrams are in the folder **diagrams**. 
You find Informations about the parts in the **images** folder. 
Start with the 01 sketch and continue - in each further sketch a new part will be connected to your circuit for an easier debugging.

The sketches *_04_test_merge_Dht11_ds1820* and *_06_all_together* need some information from you. Copy the file **configuration.h.dist** to **configuration.h**
and enter name of your wLAN + Password and the Thingspeak Write API Key. 

###Pull requets are welcome 



