#include <ESP32Servo.h>
#include <Ultrasonic.h>

Servo myservo;

const int pul = 13;
const int dir = 12;
const int ena = 14;

#define BUTTON_PIN 33
int val = 0;
int sensorPin = 25;
int valSensor = 0;
int LED1 = 23;
int LED2 = 22;
int servo = 26;

Ultrasonic ultrasonic1(15, 2);
Ultrasonic ultrasonic2(18, 19);


void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(pul,OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  myservo.attach(servo);
}

void loop() {
  digitalWrite(ena,HIGH);
  myservo.write(190);

  int countSen1 = ultrasonic1.read();
  int countSen2 = ultrasonic2.read();

  if(countSen1 <= 10){
    digitalWrite(LED2, HIGH); 
    digitalWrite(LED1, HIGH);
    delay(350); 
    digitalWrite(LED1, LOW);
    delay(350);
    ESP.restart();
  }

  if(countSen2 <= 10){
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, HIGH);
    delay(350);
    digitalWrite(LED1, LOW);
    delay(350);
    ESP.restart();
  }

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  delay(500);
  digitalWrite(LED2, LOW);
  delay(500);

  Serial.print("Sensor 01: ");
  Serial.print(countSen1);
  Serial.println("cm");
  Serial.print("Sensor 02: ");
  Serial.print(countSen2);
  Serial.println("cm");
  valSensor = digitalRead(sensorPin);
  val = digitalRead(BUTTON_PIN);

  if (val == LOW){    
    digitalWrite(ena,LOW);
    
    if (valSensor == 1){
      bin1();
      delay(500);
    }
    if (valSensor == 0){
      bin2();
      delay(500);
    }
  }
  ESP.restart();
}
void bin1(){
    for (int i=0; i < 1000; i++)
    {
    digitalWrite(ena,LOW);
    digitalWrite(dir,HIGH);
    digitalWrite(pul,HIGH);
    delayMicroseconds(500);
    digitalWrite(pul,LOW);
    delayMicroseconds(500);
    }
    delay(500);
    myservo.write(90);
    delay(500);
    myservo.write(190);
    delay(1500);


    for (int i=0; i < 1000; i++)
    {
    digitalWrite(dir,LOW);
    digitalWrite(pul,HIGH);
    delayMicroseconds(500);
    digitalWrite(pul,LOW);
    delayMicroseconds(500);
    }
    delay(1000);
}

void bin2(){
    for (int i=0; i < 3350; i++)
    {
    digitalWrite(ena,LOW);
    digitalWrite(dir,HIGH);
    digitalWrite(pul,HIGH);
    delayMicroseconds(500);
    digitalWrite(pul,LOW);
    delayMicroseconds(500);
    }
    delay(500);
    myservo.write(90);  
    delay(500);
    myservo.write(190);
    delay(1500);


    for (int i=0; i < 3350; i++)
    {
    digitalWrite(dir,LOW);
    digitalWrite(pul,HIGH);
    delayMicroseconds(500);
    digitalWrite(pul,LOW);
    delayMicroseconds(500);
    }
    delay(1000);
}