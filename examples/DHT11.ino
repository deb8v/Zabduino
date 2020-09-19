Z
#include <ESP8266WiFi.h>
#include "DHT.h"
WiFiServer server(10050); 
const char *ssid = "";  
const char *password = "";
const int port=10050;
byte pktsize=0;
byte header[50];
byte body[254];
String key=""; // received request
boolean errorflag=false;
boolean debugflag=true;

DHT dht(D3, DHT11);

void setup() 
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wifi");
  while (WiFi.status() != WL_CONNECTED) {delay(500);Serial.print(".");}

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

  
  server.begin();
  Serial.print(WiFi.localIP());
  Serial.print(':');
  Serial.println(port);
}

void loop() 
{
  WiFiClient client = server.available();
  
  if (client) {
    if(client.connected())
    { errorflag=false;
      Serial.println("Client Connected");
    }
    byte dbx=0;
    int counter=0;
    //WiFi.beginWPSConfig();
    while(client.connected()){
      Serial.println(">>>");
      while(client.available()>13){
      client.readBytesUntil('\n',header,5);
      pktsize=client.read();
      if(debugflag)Serial.print("Agent Len: ");
      if(debugflag)Serial.println(pktsize);
      for(int i =1;i<=7;i++){
      if(client.read()>0){
        errorflag=true;
        Serial.println("ERROR:PacketOverSize;");
        }
      }

      key="";
      for(int i=0;i!=pktsize;i++){
        dbx=client.read();
        if(debugflag)Serial.print(i);
        if(debugflag)Serial.print('\t');
        if(debugflag)Serial.print((char)dbx);
        if(debugflag)Serial.print('\t');
        if(debugflag)Serial.println(dbx);
        if(dbx!=0)key=key+(char)dbx;
        }
      Serial.println(key);
      Serial.println("__Work__");
        

      if(errorflag)key="error";
      }//client.available()
      delay(12);
      client.print("ZBXD\x01");
      Serial.println("Sending");
        if(key=="agent.ping"){
          byte toSend[]={0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '1'};
          client.write(toSend, 9);
          client.stop();
        }else if(key=="agent.version"){
          char text[]= "v0.2.2";
          byte toSend[]={(byte)String(text).length(), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
          client.write(toSend, 8);
          client.print(text);
          client.stop();
         } else if(key=="sensors.temperature.0"){
          float temperature=65.33+random(-10,10);
          byte toSend[]={(byte)String(temperature).length(), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
          client.write(toSend, 8);
          client.print(temperature);
          client.stop();
         } else if(key=="sensors.temperature.1"){
          float temperature=dht.readTemperature();
          Serial.println(dht.readTemperature());
          byte toSend[]={(byte)String(temperature).length(), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
          client.write(toSend, 8);
          client.print(temperature);
          client.stop();
         } else if(key=="sensors.humidity.0"){
          float temperature=dht.readHumidity();
          byte toSend[]={(byte)String(temperature).length(), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
          client.write(toSend, 8);
          client.print(temperature);
          client.stop();
         }else{
          char text[]= "ZBX_ERROR";
          byte toSend[]={(byte)String(text).length(), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
          client.write(toSend, 8);
          client.print(text);
          client.stop();
          }
        
        Serial.println("Client disconnected");       
    }
    
  }
}
