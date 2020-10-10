/**********_Try to use_*********
$ zabbix_get -s agent.ip -k agent.ping
$ zabbix_get -s agent.ip -k sensors.temperature.0
$ zabbix_get -s agent.ip -k who
********************************/
#include <ESP8266WiFi.h>
WiFiServer server(10050);//or other Serial
const char *ssid = "";  
const char *password = "";
const int port=10050;
byte pktsize=0;
byte header[50];
byte body[254];
String key=""; // received request
boolean errorflag=false;
boolean debugflag=true;



void setup() 
{
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nWIFI:Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);Serial.print(".");
  
        //U CAN USE WPS
      //if(millis()>=10000){
      //WiFi.beginWPSConfig(); 
      //Serial.println("\nWIFI:Trying WPS");
      //}
  }
  Serial.print("\nWIFI:Connected to ");
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
      Serial.println("SERVER:Client Connected");
    }
    byte dbx=0;
    int counter=0;
    
    while(client.connected()){
      Serial.println(">>>");
      while(client.available()>13){
      client.readBytesUntil('\n',header,5);
      pktsize=client.read();
      if(debugflag)Serial.print("SERVER:Agent Len: ");
      if(debugflag)Serial.println(pktsize);
      for(int i =1;i<=7;i++){
      if(client.read()>0){
        errorflag=true;
        Serial.println("SERVER:PacketOverSize;");
        }
      }

      key="";//the requested key
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
      Serial.println("SERVER:SEEN");
        

      if(errorflag)key="error";
      }
      delay(12);
      client.print("ZBXD\x01");
      Serial.println("SERVER:RESPONDING");
        if(key=="agent.ping"){ //sending Byte
          byte toSend[]={0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '1'}; //1 as char
          client.write(toSend, 9);
          client.stop();
        }else if(key=="agent.version"){ //sending string
          char text[]= "v0.2.2"; //service information!!!!
          byte toSend[]={(byte)String(text).length(), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
          client.write(toSend, 8);//header
          client.print(text);     //useful block
          client.stop();
         } else if(key=="sensors.temperature.0"){ //sending float
          float temperature=65.33+random(-10,10);
          byte toSend[]={(byte)String(temperature).length(), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
          client.write(toSend, 8);
          client.print(temperature);
          client.stop();
         }else{
          char text[]= "ZBX_NOTSUPPORTED";
          byte toSend[]={(byte)String(text).length(), 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
          client.write(toSend, 8);
          client.print(text);
          client.stop();
          }
        
        Serial.println("SERVER:disconnected");       
    }
    
  }
}
