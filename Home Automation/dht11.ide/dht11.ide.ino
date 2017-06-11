//Debadri Dutta's Code
#include <SoftwareSerial.h>
#include<DHT11.h>
SoftwareSerial espSerial =  SoftwareSerial(2,3);   // arduino RX pin=6  arduino TX pin=7  connect the arduino RX pin to esp8266 module TX pin   -  connect the arduino TX pin to esp8266 module RX pin
#define dht_apin A0 // Analog Pin sensor is connected to
 
DHT11 DHT(dht_apin);
int value_humid;
int value_temp;

String apiKey = "LKXRETR7E5YSOXMY";     // replace with your channel's thingspeak WRITE API key

String ssid="Red Devil";    // Wifi network SSID
String password ="pqr123456";  // Wifi network password

boolean DEBUG=true;

//======================================================================== showResponce
void showResponse(int waitTime){
    long t=millis();
    char c;
    while (t+waitTime>millis()){
      if (espSerial.available()){
        c=espSerial.read();
        if (DEBUG) Serial.print(c);
      }
    }
                   
}

//========================================================================
boolean thingSpeakWrite(float value1, float value2){
  String cmd = "AT+CIPSTART=\"TCP\",\"";                  // TCP connection
  cmd += "184.106.153.149";                               // api.thingspeak.com
  cmd += "\",80";
  espSerial.print(cmd+"\r\n");
  if (DEBUG) Serial.println(cmd);
  if(espSerial.find("Error")){
    if (DEBUG) Serial.println("AT+CIPSTART error");
    return false;
  }
  
  
  String getStr = "GET /update?api_key=";   // prepare GET string
  getStr += apiKey;
  
  getStr +="&field1=";
  getStr += String(value1);
  getStr +="&field2=";
  getStr += String(value2);
  // getStr +="&field3=";
  // getStr += String(value3);
  // ...
  getStr += "\r\n\r\n";

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  espSerial.print(cmd+"\r\n");
  if (DEBUG)  Serial.println(cmd);
  
  delay(100);
  if(espSerial.find(">")){
    espSerial.print(getStr);
    if (DEBUG)  Serial.print(getStr);
  }
  else{
    espSerial.print("AT+CIPCLOSE\r\n");
    // alert user
    if (DEBUG)   Serial.println("AT+CIPCLOSE");
    return false;
  }
  return true;
}
//================================================================================ setup
void setup() {                
  DEBUG=true;           // enable debug serial
  Serial.begin(9600); 
    
  espSerial.begin(115200);  // enable software serial
                          // Your esp8266 module's speed is probably at 115200. 
                          // For this reason the first time set the speed to 115200 or to your esp8266 configured speed 
                          // and upload. Then change to 9600 and upload again
  
  //espSerial.println("AT+RST");         // Enable this line to reset the module;
  //showResponse(1000);

  //espSerial.println("AT+UART_CUR=9600,8,1,0,0");    // Enable this line to set esp8266 serial speed to 9600 bps
  //showResponse(1000);
  
  

  espSerial.print("AT+CWMODE=1\r\n");   // set esp8266 as client
  showResponse(1000);

  espSerial.print("AT+CWJAP=\""+ssid+"\",\""+password+"\""+"\r\n");  // set your home router SSID and password
  showResponse(5000);

   if (DEBUG)  Serial.println("Setup completed");
}


// ====================================================================== loop
void loop() {

  // Read sensor values
   int err;
   float tem, humi;
 if((err=DHT.read(humi, tem))==0)
  {
    Serial.print("temperature:");
    Serial.print(tem);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
    value_temp=tem;
    value_humid=humi;
   thingSpeakWrite(value_temp,value_humid);                                      // Write values to thingspeak
      
  
  }
  // thingspeak needs 15 sec delay between updates,     
  delay(1000);  
}

