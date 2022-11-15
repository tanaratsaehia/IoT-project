#define BLYNK_TEMPLATE_ID "TMPLtigT0fsM"
#define BLYNK_DEVICE_NAME "PIRSensor"
#define BLYNK_AUTH_TOKEN "feZ5xCUnLJSCv4eYZUhsR5D0S_VBlAIj"

#include <BlynkSimpleEsp32.h>
#include <TridentTD_LineNotify.h>

#define SSID        "D"
#define PASSWORD    "sssd1122"
#define LINE_TOKEN  "sdL42HKKK3WsNxmBQ76a2wYnmls4pCh4Hnjmi1GynZm"

int stateVal;
int sensorVal;
int pirPin = 32;
int Buzzer = 18;

BLYNK_WRITE(V0)
{
  int State_Data = param.asInt();
  if(State_Data == 1){
    stateVal = 1;
  }else { 
    stateVal = 0;
  }
}

BLYNK_WRITE(V1)
{
  int State_Data2 = param.asInt();
  if(State_Data2 == 1){
    digitalWrite(Buzzer, HIGH);
  }else { 
    digitalWrite(Buzzer, LOW);
  }
}

BLYNK_WRITE(V2)
{
  int State_Data3 = param.asInt();
  if(State_Data3 == 1){
    LINE.notify("ตรวจพบการเคลื่อไหว.....");
    delay(1000);
  }
}

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(2, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  digitalWrite(2, HIGH);

  LINE.setToken(LINE_TOKEN);

  LINE.notify("สัญญาณกันขโมย ออนไลน์!");
  Blynk.config(BLYNK_AUTH_TOKEN);
}

void loop() {
  int test1 = digitalRead(pirPin);
  Serial.print("Read pir :");
  Serial.println(test1);
  Serial.print("State param : ");
  Serial.println(stateVal);

  Blynk.run();
  delay(1);
}
