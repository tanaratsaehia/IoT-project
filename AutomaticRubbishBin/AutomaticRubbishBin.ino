
#include <AFMotor.h>      //add Adafruit Motor Shield library
#include <Servo.h>        //add Servo Motor library            
#include <NewPing.h>      //add Ultrasonic sensor library
#include <Ultrasonic.h>

Ultrasonic ultrasonic1(A0, A1);	// An ultrasonic sensor HC-04
Ultrasonic ultrasonic2(A2, A3);		// An ultrasonic sensor PING)))

#define TRIG_PIN A0 // Pin A0 on the Motor Drive Shield soldered to the ultrasonic sensor
#define ECHO_PIN A1 // Pin A1 on the Motor Drive Shield soldered to the ultrasonic sensor
#define TRIG_PIN2 A2 // Pin A2 -> add ultasonic2 -aung
#define ECHO_PIN2 A3 // Pin A3 -> add ultasonic2 -aung
#define MAX_DISTANCE 300 // sets maximum useable sensor measuring distance to 300cm
#define MAX_DISTANCE2 300 // add ultasonic2 -aung
#define MAX_SPEED 160 // sets speed of DC traction motors to 150/250 or about 70% of full speed - to get power drain down.
#define MAX_SPEED_OFFSET 40 // this sets offset to allow for differences between the two DC traction motors
#define COLL_DIST 30 // sets distance at which robot stops and reverses to 30cm
#define TURN_DIST COLL_DIST+20 // sets distance at which robot veers away from object
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); // sets up sensor library to use the correct pins to measure distance.//rotage sonar -aung
NewPing sonar2(TRIG_PIN2, ECHO_PIN2, MAX_DISTANCE2);// add sonar2 -aung
AF_DCMotor leftMotor1(1, MOTOR12_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor leftMotor2(2, MOTOR12_1KHZ); // create motor #2, using M2 output, set to 1kHz PWM frequency
AF_DCMotor rightMotor1(3, MOTOR34_1KHZ);// create motor #3, using M3 output, set to 1kHz PWM frequency
AF_DCMotor rightMotor2(4, MOTOR34_1KHZ);// create motor #4, using M4 output, set to 1kHz PWM frequency
Servo myservo;  // create servo object to control a servo 
int detect_R = A4; // Pin A4-> add Infrared sensor_R - aung
int detect_L = A5; // Pin A5-> add Infrared sensor_L - aung
int IR_value_R; // aung
int IR_value_L; // aung
int leftDistance, rightDistance; //distances on either side
int curDist = 0;
int curDist2 = 0;// add ultasonic2 -aung
String motorSet = "";
int speedSet = 0;

//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  pinMode(detect_R,INPUT);// set pin as input - aung
  pinMode(detect_L,INPUT);// set pin as input - aung
  myservo.attach(10);  // attaches the servo on pin 10 (SERVO_1 on the Motor Drive Shield to the servo object 
  myservo.write(90); // tells the servo to position at 90-degrees ie. facing forward.
  delay(1000); // delay for one seconds
 }
//------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
  myservo.write(90);  // move eyes forward
  delay(90);
  //curDist = readPing();   // read distance
  //curDist2 = readPing2();   // read distance ->add sonar 2 -aung

  curDist = ultrasonic1.read();
  curDist2 = ultrasonic2.read();
  IR_value_R = analogRead(detect_R); // read distance IR sensor_R- aung
  IR_value_L = analogRead(detect_L); // read distance IR sensor_L - aung
  
  //if ((curDist < COLL_DIST)||(curDist2 < COLL_DIST)||(IR_value_R < 100)||(IR_value_L < 100)) {changePath();}
  if ((curDist < COLL_DIST)||(curDist2 < COLL_DIST)) {changePath();}
  Serial.print("Sen1 ");
  Serial.println(curDist);
  Serial.print("Sen2 ");
  Serial.println(curDist2);
  // if forward is blocked change direction
  moveForward();  // move forward
  //delay(500);
  delay(5);// deduce delay for short distance 
  }
//-------------------------------------------------------------------------------------------------------------------------------------

void changePath() {
  moveStop();   // stop forward movement
  moveBackward(); //add back word-aung
  delay(150);//add move delay-aung
  moveStop();//add stop-aung
  myservo.write(36);  // check distance to the right
    delay(500);
    rightDistance = ultrasonic1.read(); //set right distance
    delay(500);
    myservo.write(144);  // check distace to the left
    delay(700);
    leftDistance = ultrasonic1.read(); //set left distance
    delay(500);
    myservo.write(90); //return to center
    delay(100);
    compareDistance();
  }

  
void compareDistance()   // find the longest distance
{
  if (leftDistance>rightDistance) //if left is less obstructed 
  {
    turnLeft();
  }
  else if (rightDistance>leftDistance) //if right is less obstructed
  {
    turnRight();
  }
   else //if they are equally obstructed
  {
    turnAround();
  }
}


//-------------------------------------------------------------------------------------------------------------------------------------
// rotage sonar
int readPing() { // read the ultrasonic sensor distance
  delay(70);   
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

// fix sonar2
int readPing2() { // read the ultrasonic sensor2 distance-aung
  delay(70);   
  unsigned int uS = sonar2.ping();
  int cm = uS/US_ROUNDTRIP_CM;
  return cm;
}

//-------------------------------------------------------------------------------------------------------------------------------------
void moveStop() {leftMotor1.run(RELEASE); leftMotor2.run(RELEASE); rightMotor1.run(RELEASE); rightMotor2.run(RELEASE);}  // stop the motors.
//-------------------------------------------------------------------------------------------------------------------------------------
void moveForward() {
    motorSet = "FORWARD";
    leftMotor1.run(FORWARD);      // turn it on going forward
    leftMotor2.run(FORWARD);      // turn it on going forward
    rightMotor1.run(FORWARD);     // turn it on going forward
    rightMotor2.run(FORWARD);     // turn it on going forward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    leftMotor1.setSpeed(speedSet);
    leftMotor2.setSpeed(speedSet);
    rightMotor1.setSpeed(speedSet); 
    rightMotor2.setSpeed(speedSet);
    //delay(5);
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------
void moveBackward() {
    motorSet = "BACKWARD";
    leftMotor1.run(BACKWARD);     // turn it on going backward
    leftMotor2.run(BACKWARD);     // turn it on going backward
    rightMotor1.run(BACKWARD);    // turn it on going backward
    rightMotor2.run(BACKWARD);    // turn it on going backward
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    leftMotor1.setSpeed(speedSet);
    leftMotor2.setSpeed(speedSet);
    rightMotor1.setSpeed(speedSet); 
    rightMotor2.setSpeed(speedSet); 
    delay(5);
  }
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnRight() {
  motorSet = "RIGHT";
  leftMotor1.run(FORWARD);      // turn motor 1 forward
  leftMotor2.run(FORWARD);      // turn motor 2 forward
  rightMotor1.run(BACKWARD);    // turn motor 3 backward
  rightMotor2.run(BACKWARD);    // turn motor 4 backward
  rightMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);      
  rightMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);     
  //delay(1500); // run motors this way for 1500   
  delay(1800);//700aung     
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);      // set both motors back to forward
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);      
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  motorSet = "LEFT";
  leftMotor1.run(BACKWARD);      // turn motor 1 backward
  leftMotor2.run(BACKWARD);      // turn motor 2 backward
  leftMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);     
  leftMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);    
  rightMotor1.run(FORWARD);     // turn motor 3 forward
  rightMotor2.run(FORWARD);     // turn motor 4 forward
  //delay(1500); // run motors this way for 1500  
  delay(1800);//700aung
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);      // turn it on going forward
  leftMotor2.run(FORWARD);      // turn it on going forward
  rightMotor1.run(FORWARD);     // turn it on going forward
  rightMotor2.run(FORWARD);     // turn it on going forward
}  
//-------------------------------------------------------------------------------------------------------------------------------------
void turnAround() {
  motorSet = "RIGHT";
  leftMotor1.run(FORWARD);      // turn motor 1 forward
  leftMotor2.run(FORWARD);      // turn motor 2 forward
  rightMotor1.run(BACKWARD);    // turn motor 3 backward
  rightMotor2.run(BACKWARD);    // turn motor 4 backward
  rightMotor1.setSpeed(speedSet+MAX_SPEED_OFFSET);      
  rightMotor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
  //delay(1700); // run motors this way for 1700
  delay(3000);//aung
  motorSet = "FORWARD";
  leftMotor1.run(FORWARD);      // set both motors back to forward
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);      
}  
