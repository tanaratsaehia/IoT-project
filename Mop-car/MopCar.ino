
#include <AFMotor.h>      
#include <Servo.h>                
#include <NewPing.h>      
#include <Ultrasonic.h>

Ultrasonic ultrasonic1(A0, A1);	
Ultrasonic ultrasonic2(A2, A3);		

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define TRIG_PIN2 A2 
#define ECHO_PIN2 A3 
#define MAX_DISTANCE 300 
#define MAX_DISTANCE2 300 
#define MAX_SPEED 160 
#define MAX_SPEED_OFFSET 40 
#define COLL_DIST 30 
#define TURN_DIST COLL_DIST+20 
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
NewPing sonar2(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE2);
AF_DCMotor leftMotor1(1, MOTOR12_1KHZ); 
AF_DCMotor leftMotor2(2, MOTOR12_1KHZ); 
AF_DCMotor rightMotor1(3, MOTOR34_1KHZ);
AF_DCMotor rightMotor2(4, MOTOR34_1KHZ);
Servo myservo;
int detect_R = A4; 
int detect_L = A5;
int IR_value_R;
int IR_value_L;
int leftDistance, rightDistance;
int curDist = 0;
int curDist2 = 0;
String motorSet = "";
int speedSet = 0;


void setup() {
  Serial.begin(115200);
  pinMode(detect_R,INPUT);
  pinMode(detect_L,INPUT);
  myservo.attach(10);
  myservo.write(90);
  delay(1000);
 }




void loop() {
  myservo.write(90);
  delay(90);
  //curDist = readPing();   
  //curDist2 = readPing2();

  curDist = ultrasonic1.read();
  curDist2 = ultrasonic2.read();
  IR_value_R = analogRead(detect_R);
  IR_value_L = analogRead(detect_L);
  
  if ((curDist < COLL_DIST)||(curDist2 < COLL_DIST)||(IR_value_R < 100)||(IR_value_L < 100)) {changePath();}
  //if ((curDist < COLL_DIST)||(curDist2 < COLL_DIST)) {changePath();}
  Serial.print("Sen1 ");
  Serial.println(curDist);
  Serial.print("Sen2 ");
  Serial.println(curDist2);
  moveForward();
  //delay(500);
  delay(5);
  }


void changePath() {
  moveStop();
  moveBackward();
  delay(150);
  moveStop();
  myservo.write(36);
    delay(500);
    rightDistance = ultrasonic1.read();
    delay(500);
    myservo.write(144);
    delay(700);
    leftDistance = ultrasonic1.read();
    delay(500);
    myservo.write(90);
    delay(100);
    compareDistance();
  }

  
void compareDistance()
{
  if (leftDistance>rightDistance)
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance)
  {
    turnRight();
  }
   else 
  {
    turnAround();
  }
}


int readPing() {
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

// fix sonar2
int readPing2() {
  delay(70);   
  unsigned int uS = sonar2.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}


void moveStop() {leftMotor1.run(RELEASE); leftMotor2.run(RELEASE); rightMotor1.run(RELEASE); rightMotor2.run(RELEASE);}

void moveForward() {
    motorSet = "FORWARD";
    leftMotor1.run(FORWARD);
    leftMotor2.run(FORWARD);
    rightMotor1.run(FORWARD);
    rightMotor2.run(FORWARD);     
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)
  {
    leftMotor1.setSpeed(speedSet);
    leftMotor2.setSpeed(speedSet);
    rightMotor1.setSpeed(speedSet); 
    rightMotor2.setSpeed(speedSet);
    //delay(5);
  }
}

void moveBackward() {
    motorSet = "BACKWARD";
    leftMotor1.run(BACKWARD);
    leftMotor2.run(BACKWARD);
    rightMotor1.run(BACKWARD);
    rightMotor2.run(BACKWARD);
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)
  {
    leftMotor1.setSpeed(speedSet);
    leftMotor2.setSpeed(speedSet);
    rightMotor1.setSpeed(speedSet); 
    rightMotor2.setSpeed(speedSet); 
    delay(5);
  }
}  

void turnRight() {
  motorSet = "RIGHT";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(BACKWARD);
  rightMotor2.run(BACKWARD);
  rightMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);      
  rightMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);     
  //delay(1500); 
  delay(1800);//700aung     
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);      
}  

void turnLeft() {
  motorSet = "LEFT";
  leftMotor1.run(BACKWARD);
  leftMotor2.run(BACKWARD);
  leftMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);     
  leftMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);    
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
  //delay(1500); 
  delay(1800);
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
}  

void turnAround() {
  motorSet = "RIGHT";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(BACKWARD);
  rightMotor2.run(BACKWARD);
  rightMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);      
  rightMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
  //delay(1700);
  delay(3000);//aung
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);      
}  
