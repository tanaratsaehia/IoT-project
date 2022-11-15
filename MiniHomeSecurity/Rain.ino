
#include <WiFiManager.h>
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "iQ2ClIX24buY3bbRtX23jjCN9Hplhxe8zIROIxo1PAv" // line token ชื่อ แจ้งเตือน !!

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



void setup()
{
  pinMode(33, INPUT);
  LINE.setToken(LINE_TOKEN);
  WiFi.mode(WIFI_STA); 
  // Debug console
  Serial.begin(115200);

 bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
     res = wm.autoConnect("ConfigWiFi(Rain)"); // anonymous ap
      if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
    }
    initWiFi();
}

int count = 0;
void loop()
{
  int g = digitalRead(33);
    if(g == 0){
      count += 1;
      if(count >= 10){
        LINE.notify("ตรวจพบฝน อย่าลืมเก็บผ้านะจ๊ะ");
        delay(3000);
      }
      delay(200);
    }
   if(WiFi.status() != WL_CONNECTED){
    Serial.println("Reconnecting to WiFi...");
    initWiFi();    
  }
 
}
