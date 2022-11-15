
/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLE-sekKh9"
#define BLYNK_DEVICE_NAME "LDR Sensor"
#define BLYNK_AUTH_TOKEN "GFa7f793hQT5D2fvLFEdi18WrWZQ-6z0"
#include <WiFiManager.h>
#include <BlynkSimpleEsp32.h>
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "mtrc4kcrLZQb9vLsYGf8uE8vKfRsHQCA1EUhs23TZDb" // line token ชื่อ Sensor ระดับแสง

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

void ReadLDR()
{
  int l = analogRead(33);
  String lStr = String(l);
  if (isnan(l)) {
    Serial.println(F("Failed to read from LDR sensor!"));
    return;
  }
  Serial.println("Ligh : " + lStr);

  Blynk.virtualWrite(V0,l);
}

BLYNK_WRITE(V1)
{
  int State_DataV2 = param.asInt();
  if(State_DataV2 == 1){
    digitalWrite(32, LOW); //relay2
      LINE.notify("หลอดไฟ เปิด");
  }else { 
    digitalWrite(32, HIGH);
      LINE.notify("หลอดไฟ ปิด");
  }
}

void setup()
{
  pinMode(33, INPUT);
  pinMode(25, OUTPUT);
  pinMode(32, OUTPUT);
  LINE.setToken(LINE_TOKEN);
  WiFi.mode(WIFI_STA); 
  // Debug console
  Serial.begin(115200);

 bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
     res = wm.autoConnect("ConfigWiFi(LDR)"); // anonymous ap
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
     timer.setInterval(3000,ReadLDR);
  
  digitalWrite(32, HIGH);
}

void loop(){
  int l2 = analogRead(33);
  String lStr2 = String(l2);
    if(l2 >= 3000){
      digitalWrite(25, LOW); //relay1
      count += 1;
      delay(200);
      if(count >= 10){
        LINE.notify("หลอดไฟทำงาน ค่าที่วัดได้คือ : " + lStr2);
        count = 0;
        delay(3000);
      }
    }
    else if(l2 == 2000){
      digitalWrite(25, HIGH);
    }
    else if(l2 < 2000){
      digitalWrite(25, HIGH);
    }
  Blynk.run();
    timer.run();
   if(WiFi.status() != WL_CONNECTED){
    Serial.println("Reconnecting to WiFi...");
    initWiFi();    
  }
 
}
