
/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLdnx8UGrn"
#define BLYNK_DEVICE_NAME "DHT11Sensor"
#define BLYNK_AUTH_TOKEN "aVGXWyQCTKKlr5DjokQbl9trr-uOvB3s"
#include <WiFiManager.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "HJTdUGpl9WJRCIfHREyYsxNMOnj0vjb95P2YOa79UMg" // line token ชื่อ Sensor อุณหภูมิ


#define DHTPIN 33
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);
#define CLK 0
#define DIO 4
#include <string>

int count = 0;


#define BLYNK_PRINT Serial
BlynkTimer timer;

WiFiManager wm;
void initWiFi() {
  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    //WiFi.begin(ssid, password);
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void ReadDHT()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("C "));


  Blynk.virtualWrite(V1,t);
  Blynk.virtualWrite(V0,h);
}

BLYNK_WRITE(V2)
{
  int State_DataV2 = param.asInt();
  if(State_DataV2 == 1){
    digitalWrite(27, HIGH); //relay2
      LINE.notify("เครื่องทำความเย็น เปิด");
  }else { 
    digitalWrite(27, LOW);
      LINE.notify("เครื่องทำความเย็น ปิด");
  }
}

void setup()
{
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  LINE.setToken(LINE_TOKEN);
  WiFi.mode(WIFI_STA); 
  // Debug console
  Serial.begin(9600);
      dht.begin();

 bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
     res = wm.autoConnect("ConfigWiFi"); // anonymous ap
      if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
    
    initWiFi();
    
  
  Blynk.config(BLYNK_AUTH_TOKEN);
     timer.setInterval(3000,ReadDHT);
  
  digitalWrite(32, HIGH);
}

void loop()
{
  int t2 = dht.readTemperature();
  String tStr = String(dht.readTemperature());
    if(t2 >= 38){
      digitalWrite(25, LOW); //relay1
      count += 1;
      delay(200);
      if(count >= 10){
        LINE.notify("เครื่องทำความเย็นทำงานขณะนี้อุณหภูมิ : " + tStr + " °C");
        count = 0;
        delay(60000);
      }
    }
    else if(t2 == 37){
      digitalWrite(25, HIGH);
      LINE.notify("เครื่องทำความเย็น หยุด ทำงานขณะนี้อุณหภูมิ : " + tStr + " °C");
    }
    else if(t2 < 36){
      digitalWrite(25, HIGH);
    }
  Blynk.run();
    timer.run();
   if(WiFi.status() != WL_CONNECTED){
    Serial.println("Reconnecting to WiFi...");
    initWiFi();    
  }
 
}
