
#include <WiFiManager.h>
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "iQ2ClIX24buY3bbRtX23jjCN9Hplhxe8zIROIxo1PAv" // line token ชื่อ แจ้งเตือน !!

WiFiManager wm;
void WiFi() {
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



void setup()
{
  pinMode(33, INPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  LINE.setToken(LINE_TOKEN);
  WiFi.mode(WIFI_STA); 
  // Debug console
  Serial.begin(115200);

 bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
     res = wm.autoConnect("ConfigWiFi(Gas)"); // anonymous ap
      if(!res) {
        Serial.println("Failed to connect");
        digitalWrite(2, LOW);
        ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
        digitalWrite(2, HIGH);
    }
    WiFi();
}

int count = 0;
void loop()
{
  int g = digitalRead(33);
    if(g == 0){
      count += 1;
      if(count >= 10){
        LINE.notify("ตรวจพบแก๊สรั่ว กรุณาตรวจสอบโดยด่วน");
        delay(3000);
      }
      delay(200);
    }
   if(WiFi.status() != WL_CONNECTED){
    Serial.println("Reconnecting to WiFi...");
    initWiFi();    
  }
 Serial.println(g);
 delay(500);
}
