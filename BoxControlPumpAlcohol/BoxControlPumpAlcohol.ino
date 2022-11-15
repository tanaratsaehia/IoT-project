void setup() {
  // put your setup code here, to run once:
  pinMode(26, INPUT);
  pinMode(5, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = digitalRead(26);
  Serial.println(i);
  if(i == 0){
    delay(300);
    digitalWrite(5, HIGH);
    delay(1500);
    digitalWrite(5, LOW);
    delay(100);
  }
}
