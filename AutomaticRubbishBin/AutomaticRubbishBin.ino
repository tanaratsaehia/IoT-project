//C++
#include <ESP32Servo.h> //เรียกใช้ ribrary ของ servo motor 
#include <Ultrasonic.h> //เรียกใช้ ribrary ของ ultrasonic

Servo myservo;          //เปลี่ยนชื่อตัวแปรของ servo ให้เป็น myservo

const int pul = 13;     //กำหนด pin 13 ให้เป็นขาที่ส่งสัญญาณ pulse 
const int dir = 12;     //กำหนด pin 12 ให้เป็นขาที่ส่งสัญญาณ direct
const int ena = 14;     //กำหนด pin 14 ให้เป็นขาที่ส่งสัญญาณ enable

#define BUTTON_PIN 33   //กำหนด pin 33 ให้เปิน switch เริ่มทำงาน
int val = 0;            //ประกาศตัวแปรเพื่อรออ่านค่าจาก switch แล้วนำไปใช้งานต่อ
int sensorPin = 25;     //กำหนด pin 25 ให้รอรับ input จาก sensor
int valSensor = 0;      //ประกาศตัวแปรเพื่อรออ่านค่าจาก sensor
int LED1 = 23;          //กำหนดให้ pin 23 ให้เป็นขาที่ควบคุม led1
int LED2 = 22;          //กำหนดให้ pin 22 ให้เป็นขาที่ควบคุม led2
int servo = 26;         //กำหนดให้ pin 26 ใหเป็นขาที่ควบคุม servo motor

Ultrasonic ultrasonic1(15, 2);	    //ประกาศตัวแปร ultrasonic1 และกำหนดให้ขา 15 เป็น trig และขา 2 ให้เป็น echo
Ultrasonic ultrasonic2(18, 19);	    //ประกาศตัวแปร ultrasonic2 และกำหนดให้ขา 18 เป็น trig และขา 19 ให้เป็น echo


void setup() {              //setup เมื่อเปิดเครื่องคำสั่งในนี้จะทำงานเพียงครั้งเดียว
  Serial.begin(115200);     //กำหนดความเร็วที่ส่งข้อมูลผ่าน serial port เป็น 115200 byte per secound
  pinMode(LED1, OUTPUT);    //กำหนดให้ LED1 ให้เป็น output
  pinMode(LED2, OUTPUT);    //กำหนดให้ LED2 ให้เป็น output
  pinMode(dir, OUTPUT);     //กำหนดให้ dir เป็น OUTPUT
  pinMode(pul,OUTPUT);      //กำหนดให้ pul เป็น OUTPUT
  pinMode(ena, OUTPUT);     //กำหนดให้ ena เป็น OUTPUT
  pinMode(sensorPin, INPUT);//กำหนดให้ sensorPin เป็น input
  pinMode(BUTTON_PIN, INPUT_PULLUP);  //กำหนดให้ขา BUTTON_PIN เป็น switch เปิดปิด
  myservo.attach(servo);    //เมื่อเรียกใช้ myservo ให้ส่งข้อมูลผ่านขาที่กำหนดค่าไว้ในตัวแปร servo
}

void loop() {                   //loop คำสั่งทั้งหมดในนี้จะทำงานวนซ้ำเรื่อยๆไม่สิ้นสุด
  digitalWrite(ena,HIGH);       //
  myservo.write(190);           //สั่งให้ servo motor หมุนไปที่ 180 องศา

  int countSen1 = ultrasonic1.read();   //ประกาศตัวแปร countSen1 เพื่อรับค่าที่ ultrasonic1 อ่านได้
  int countSen2 = ultrasonic2.read();   //ประกาศตัวแปร countSen2 เพื่อรับค่าที่ ultrasonic2 อ่านได้

  //LED ทั้งสองหลอดถ้าสั่ง HIGH มันจะดับและ LOW มันจะติดเนื่องจากต่อสายสลับกันคำสั่งมันเลยสลับกันขก.ต่อใหม่ครับ

  //เงื่อนไข 2 ตัวจากนี้คือถ้าหากขยะเต็มถังจะทำให้ระบบทั้งหมดไม่ทำงานต่อนอกจากไฟที่แสดงสถานะว่าขยะเต็ม
  if(countSen1 <= 10){          //สร้างเงื่อนไขถ้าหากค่าที่รับมาจาก ultrasonic1 น้อยกว่าหรือเท่ากับ 10 ให้ทำงานในสโคปนี้
    digitalWrite(LED2, HIGH);   //สั่งให้ LED2 ดับ 
    digitalWrite(LED1, HIGH);   //สั่งให้ LED1 ดับ
    delay(350);                 //หน่วงเวลา 0.35 
    digitalWrite(LED1, LOW);    //สั่งให้ LED1 ติด
    delay(350);                 //หน่วงเวลา 0.35 วิ
    ESP.restart();              //สั่งให้บอร์ด ESP restart เพื่อไม่ให้คำสั่งที่อยู่หลังจากนี้ทำงาน จริงๆมีวิธีที่ดีกว่านี้แต่เนื่องจากปัญหาหลายอย่างเลยเลือกวิธีนี้
  }

  if(countSen2 <= 10){          //สร้างเงื่อนไขถ้าหากค่าที่รับมาจาก ultrasonic2 น้อยกว่าหรือเท่ากับ 10 ให้ทำงานในสโคปนี้
    digitalWrite(LED2, HIGH);   //สั่งให้ LED2 ดับ 
    digitalWrite(LED1, HIGH);   //สั่งให้ LED1 ดับ
    delay(350);                 //หน่วงเวลา 0.35 วิ
    digitalWrite(LED1, LOW);    //สั่งให้ LED1 ติด
    delay(350);                 //หน่วงเวลา 0.35 วิ
    ESP.restart();              //สั่งให้บอร์ด ESP restart เพื่อไม่ให้คำสั่งที่อยู่หลังจากนี้ทำงาน จริงๆมีวิธีที่ดีกว่านี้แต่เนื่องจากปัญหาหลายอย่างเลยเลือกวิธีนี้
  }

  
  //ไฟสีฟ้าแสดงสถานะพร้อมใช้งาน
  digitalWrite(LED1, HIGH);     //สั่งให้ LED1 ดับ
  digitalWrite(LED2, HIGH);     //สั่งให้ LED2 ดับ
  delay(500);                   //หน่วงเวลา 0.5 วิ
  digitalWrite(LED2, LOW);      //สั่งให้ LED2 ติด
  delay(500);                   //หน่วงเวลา 0.5 วิ

  
  //แสดงข้อความผ่านและค่าที่รับมาจาก ultrasonic ผ่านทาง serial monitor
  Serial.print("Sensor 01: ");   //แสดงข้อความ Sensor 01: 
  Serial.print(countSen1);       //แสดงค่าที่รับมาจาก ultrasonic1 ผ่านตัวแปร countSen1
  Serial.println("cm");          //แสดงข้อความ cm และขึ้นบรรทัดใหม่ println เป็นคำสั่งแสดงข้อความนั้นๆและขึ้นบรรทัดใหม่

  Serial.print("Sensor 02: ");   //แสดงข้อความ Sensor 02: 
  Serial.print(countSen2);       //แสดงค่าที่รับมาจาก ultrasonic2 ผ่านตัวแปร countSen2
  Serial.println("cm");          //แสดงข้อความ cm และขึ้นบรรทัดใหม่


  valSensor = digitalRead(sensorPin);   //อ่านค่าจาก sensor ผ่านตัวแปร sensorPin และให้ตัวแปร valsensor เก็บค่าไว้
  val = digitalRead(BUTTON_PIN);        //อ่านค่าจาก switch ผ่านตัวแปร BUTTON_PIN และเก็บค่าไว้ที่ตัวแปร val

  //เมื่อกด switch ค่าของตัวแปร val จะเท่ากับ LOW ถ้าไม่กดจะเท่ากับ HIGH
  //ตัวแปร ena เมื่อเป็น HIGH จะทำให้ motor driver ตัดไฟที่ส่งไปเลี้ยงตัว motor และถ้าเป็น LOW จะทำให้ motor driver ส่งไฟไปเลี้ยงตัว motor 
  if (val == LOW){            //เงื่อนไขนี้จะทำงานเมื่อกด switch        
    digitalWrite(ena,LOW);    //สั่ง motor driver ให้จ่ายไฟเลี้ยงไปยัง motor
    
    if (valSensor == 1){      //เงื่อนไขนี้ทำงานเมื่อ sensor ไม่เจอโลหะ
      bin1();                 //function นี้เป็นการสั่งให้ motor หมุนไปที่ถังขยะใบที่ 1 ซึ่งเป็นถังของพลาสติก (สร้าง Function ไว้ข้างล่าง บรรทัด 105)
      delay(500);             //หน่วงเวลา 0.5 วิ
    }
    if (valSensor == 0){      //เงื่อนไขนี้ทำงานเมื่อ sensor ตรวจเจอโลหะ
      bin2();                 //function นี้เป็นการสั่งให้ motor หมุนไปที่ถังขยะใบที่ 2 ซึ่งเป็นถังของโลหะ (สร้าง Function ไว้ข้างล่าง บรรทัด 135)
      delay(500);             //หน่วงเวลา 0.5 วิ
    }
  }
  ESP.restart();              //สั่งให้บอร์ด ESP restart
}     //จบLoop



  //สร้าง Function bin1 และ bin2
void bin1(){ //function ของถังพลาสติก
    
    // 0.45 องศา / 1step
    for (int i=0; i < 1000; i++) //กำหนดให้สเต็ปมอเตอร์หมุน 1000 pulse โดยการทำให้ลูปนี้วนซ้ำ 1000 รอบ
    {
    //ลูปนี้สั่งให้ motor หมุนตามเข็มคือหมุนไปที่ถัง
    digitalWrite(ena,LOW);  //สั่งจ่ายไฟให้ motor
    digitalWrite(dir,HIGH); //ทำการเลือกให้ motor หมุนตามเข็ม
    digitalWrite(pul,HIGH); //สร้างสัญญาณ pulse 1 ลูก
    delayMicroseconds(500); //หน่วงเวลา 0.05วิ ใช่ไหมวะไม่แน่ใจไมโครอะ
    digitalWrite(pul,LOW);  //ดับสัญญาณ pulse เพื่อให้รอบต่อไปส่งสัญต่อได้ถ้า HIGH แล้วไม่สั่งให้ LOW ลูปล้านรอบมันก็นับเป็น 1
    delayMicroseconds(500); //หน่วงเวลา 0.05วิ ใช่ไหมวะไม่แน่ใจไมโครอะ
    }
  
    //สั่งให้ servo motor เปิดและปิด
    delay(500);           //หน่วงเวลา 0.5 วิ 
    myservo.write(90);    //สั่งให้ servo motor เปิดโดยหมุนไปที่องศาที่ 90   
    delay(500);           //หน่วงเวลา 0.5 วิ
    myservo.write(190);   //สั่งให้ servo motor ปิดโดยหมุนไปที่องศาที่ 180 
    delay(1500);          //หน่วงเวลา 1.5 วิ


    for (int i=0; i < 1000; i++) //กำหนดให้สเต็ปมอเตอร์หมุน 1000 pulse โดยการทำให้ลูปนี้วนซ้ำ 1000 รอบ
    {
    //ลูปนี้สั่งให้ motor หมุนทวนเข็มคือหมุนกลับไปที่จุดเดิม
    digitalWrite(dir,LOW);      //ทำการเลือกให้ motor หมุนทวนเข็ม
    digitalWrite(pul,HIGH);     //สร้างสัญญาณ pulse 1 ลูก
    delayMicroseconds(500);     //หน่วงเวลา 0.05วิ ใช่ไหมวะไม่แน่ใจไมโครอะ
    digitalWrite(pul,LOW);      //ดับสัญญาณ pulse เพื่อให้รอบต่อไปส่งสัญต่อได้ถ้า HIGH แล้วไม่สั่งให้ LOW ลูปล้านรอบมันก็นับเป็น 1
    delayMicroseconds(500);     //หน่วงเวลา 0.05วิ ใช่ไหมวะไม่แน่ใจไมโครอะ
    }
    delay(1000);                //หน่วงเวลา 1 วิ
}

void bin2(){ //function ของถังโลหะ
    
    // 0.45 องศา / 1step
    for (int i=0; i < 3350; i++) //กำหนดให้สเต็ปมอเตอร์หมุน 3350 pulse โดยการทำให้ลูปนี้วนซ้ำ 3350 รอบ
    {
    //ลูปนี้สั่งให้ motor หมุนตามเข็มคือหมุนไปที่ถัง
    digitalWrite(ena,LOW);  //สั่งจ่ายไฟให้ motor
    digitalWrite(dir,HIGH); //ทำการเลือกให้ motor หมุนตามเข็ม
    digitalWrite(pul,HIGH); //สร้างสัญญาณ pulse 1 ลูก
    delayMicroseconds(500); //หน่วงเวลา 0.05วิ ใช่ไหมวะไม่แน่ใจไมโครอะ
    digitalWrite(pul,LOW);  //ดับสัญญาณ pulse เพื่อให้รอบต่อไปส่งสัญต่อได้ถ้า HIGH แล้วไม่สั่งให้ LOW ลูปล้านรอบมันก็นับเป็น 1
    delayMicroseconds(500); //หน่วงเวลา 0.05วิ ใช่ไหมวะไม่แน่ใจไมโครอะ
    }
  
    //สั่งให้ servo motor เปิดและปิด
    delay(500);           //หน่วงเวลา 0.5 วิ 
    myservo.write(90);    //สั่งให้ servo motor เปิดโดยหมุนไปที่องศาที่ 90   
    delay(500);           //หน่วงเวลา 0.5 วิ
    myservo.write(190);   //สั่งให้ servo motor ปิดโดยหมุนไปที่องศาที่ 180 
    delay(1500);          //หน่วงเวลา 1.5 วิ


    for (int i=0; i < 3350; i++) //กำหนดให้สเต็ปมอเตอร์หมุน 3350 pulse โดยการทำให้ลูปนี้วนซ้ำ 3350 รอบ
    {
    //ลูปนี้สั่งให้ motor หมุนทวนเข็มคือหมุนกลับไปที่จุดเดิม
    digitalWrite(dir,LOW);      //ทำการเลือกให้ motor หมุนทวนเข็ม
    digitalWrite(pul,HIGH);     //สร้างสัญญาณ pulse 1 ลูก
    delayMicroseconds(500);     //หน่วงเวลา 0.05วิ ใช่ไหมวะไม่แน่ใจไมโครอะ
    digitalWrite(pul,LOW);      //ดับสัญญาณ pulse เพื่อให้รอบต่อไปส่งสัญต่อได้ถ้า HIGH แล้วไม่สั่งให้ LOW ลูปล้านรอบมันก็นับเป็น 1
    delayMicroseconds(500);     //หน่วงเวลา 0.05วิ ใช่ไหมวะไม่แน่ใจไมโครอะ
    }
    delay(1000);                //หน่วงเวลา 1 วิ
}