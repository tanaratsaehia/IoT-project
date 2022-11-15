
/* Fill-in your Template ID (only if using Blynk.Cloud) */
#define BLYNK_TEMPLATE_ID "TMPLzJkCHRsa"
#define BLYNK_DEVICE_NAME "Farm"
#define BLYNK_AUTH_TOKEN "Zx9xyvvGnnV6VfPZok_AQQIy7hS_dIuz"
#include <BlynkSimpleEsp32.h>
//#include <TridentTD_LineNotify.h>

#define SSID        "D"
#define PASSWORD    "sssd1122"
#define LINE_TOKEN  "WjrtGQZjK0p2EDFdzATlF1Aw0EqIazKXXxyZWPgeprU"

#define BLYNK_PRINT Serial
BlynkTimer timer;


BLYNK_WRITE(V0)
{
  int State_DataV2 = param.asInt();
  if(State_DataV2 == 1){
    digitalWrite(18, HIGH);
  }else { 
    digitalWrite(18, LOW);
  }
}

BLYNK_WRITE(V1)
{
  int State_DataV2 = param.asInt();
  if(State_DataV2 == 1){
    digitalWrite(19, HIGH);
  }else { 
    digitalWrite(19, LOW);
  }
}

void setup()
{
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT); 
  Serial.begin(115200);
  //Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  //LINE.setToken(LINE_TOKEN);
  Blynk.config(BLYNK_AUTH_TOKEN);
}

void loop()
{
  Blynk.run();
}
