#include <TridentTD_LineNotify.h>

#define SSID        "D"
#define PASSWORD    "sssd1122"
#define LINE_TOKEN  "WjrtGQZjK0p2EDFdzATlF1Aw0EqIazKXXxyZWPgeprU"

int var;
void setup() {
  pinMode(33, OUTPUT);
  pinMode(32, INPUT);

  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  LINE.setToken(LINE_TOKEN);

  digitalWrite(33, HIGH);
}

void loop() {
  var = digitalRead(32);
  Serial.println(var);

  if(var == 0){
    LINE.notify("ตรวจพบการเปิดหน้าต่าง ตรวจสอบโดยด่วน");
    digitalWrite(33, LOW);
  }else{
    digitalWrite(33, HIGH);
  }
  delay(3500);
}
