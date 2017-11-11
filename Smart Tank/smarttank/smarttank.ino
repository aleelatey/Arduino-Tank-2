# Arduino Tank
//   THIS IS A PROGRAM TO MAP OUT AN AREA WITH 2D ARRAYS AND THEN NAVIGATE ONLY THROUGH THE
//   ZEROS PRESENT. ULTRASONIC SENSORS ARE NOT USED ALTHOUGH THEY ARE INITIALIZED.
//   THE ENCODERS ARE ALSO NOT USED BUT ARE INITIALIZED

//  @author Pranav

#include "Servo.h"

// Motors
Servo motor1;
Servo motor2;

// Rotary Encoders
int encoderAPin = 4;              //Left      // pin for the rotary encoderA
int encoderBPin = 2;              //Right     // pin for the rotary encoderB
int encoderAPosition = 0;                     // position counter for encoderA
int encoderBPosition = 0;                     // position counter for encoderB
int signalAInput1;                             // signal input 1 for encoderA
int signalAInput2;                             // signal input 2 for encoderA
int signalBInput1;                             // signal input 1 for encoderB
int signalBInput2;                             // signal input 2 for encoderB



// robot location service
// 0 is up
// 1 is right
// 2 is down
// 3 is left
int robotDirection = 2;

// this is the coordinates in the grid of where the robot is
// it is also the x and y indexes in the array.
// remember that the array starts at index 0.
int xcoordinate = 2;
int ycoordinate = 1;

// ultrasonic pins
const int Trig_pin =  5;  // pin for triggering pulse    INPUT
const int Echo_pin = 6;   // pin for recieving echo      OUPUT
long duration;            // how long it takes for the sound to rebound


// motor pins
const int Motor1Pin = 9;  // Left side
const int Motor2Pin = 10; // right side

// the array that it tracks with
// this can be an array of any size
// just make sure that the robot has a free space to move to from its initial position.
int arraything [6] [6] =
{ 
  {    1,1,1,1,1,1    }
  ,
  {    1,1,0,1,0,1    }
  ,
  {    1,1,0,1,0,1    }
  ,
  {    1,1,0,1,0,1    }
  ,
  {    1,1,0,1,1,1    }
  ,
  {    1,1,1,0,1,1    }
};



void setup () {
  // Rotary encoder
  pinMode (encoderAPin, INPUT);
  pinMode (encoderBPin, INPUT);
  Serial.begin(9600);
  Serial.println ("Starting now...");
  \
 
  // ultrasonic
  //  pinMode(Trig_pin, OUTPUT);        // initialize the pulse pin as output:
  //  pinMode(Echo_pin, INPUT);       // initialize the echo_pin pin as an input:


  // motorsmmmmmmmmm
  motor1.attach(Motor1Pin);
  motor2.attach(Motor2Pin);

}


// In English, this program sees if there is something in front of it.
// If no, it moves straight. If yes, it checks its Right.
// If its Right is free, it turns that way, or else, it checks its Left.
// If its Left is free, it turns that way, or else, it just turns 180 degrees
// and goes back the way it came.
//
// Next to do is to encorporate beginning and destination as well as optimum path finding
//
// Last is to use the ultrasonic with the grid.

void loop () {

  while (1==1){
    if (isFrontOpen() == true) {
      moveForward();
      delay (2000);
    }
    else
      if (isRightOpen() == true) {
      turnRight();
      delay (2000);
    }
    else
      if (isLeftOpen() == true) {
        turnLeft();
        delay (2000);
      } 
      else {
        turnAround();
        delay (2000);
      }
  }
}


// Checks if there is something right in front of it using Grids
boolean isFrontOpen () {
  int nextNumber = getFrontNumber();
  if (nextNumber == 0){
    return true;
  }
  else {
    return false;
  }
}

// Checks if there is something to the Right of it using Grids
boolean isRightOpen(){
  int nextNumber = getRightNumber();
  if (nextNumber == 0){
    return true;
  }
  else {
    return false;
  }
}

// Checks if there is something to the Left of it using Grids
boolean isLeftOpen(){
  int nextNumber = getLeftNumber();
  if (nextNumber == 0){
    return true;
  }
  else {
    return false;
  }
}


// Moves straight forward.
void moveForward () {
  motor1.write(180);
  motor2.write(0);

  Serial.println("Forward");
  if (robotDirection == 0)
    ycoordinate = ycoordinate - 1;
  if (robotDirection == 1)
    xcoordinate = xcoordinate + 1;
  if (robotDirection == 2)
    ycoordinate = ycoordinate + 1;
  if (robotDirection == 3)
    xcoordinate = xcoordinate - 1;
  delay (100);
  /*Serial.print("  xcoordinate " );
   Serial.print(xcoordinate);
   delay (500);
   Serial.print(" ycoordinate ");
   Serial.print(ycoordinate);
   delay (500);
   Serial.print("  robot direction: ");
   Serial.print(robotDirection);
   delay(500);
   Serial.println ();
   delay(1000);
  
   */
  delay(800);
}

// Turns 90 degrees to the Right
void turnRight () {
  motor1.write (60);
  motor2.write (60);
  delay(178);
  motor2.write(95) ;
  delay(65) ;
  motor1.write(90);
  Serial.println("Right");
  if (robotDirection == 0)
    robotDirection = 1;
  else if (robotDirection == 1)
    robotDirection = 2;
  else if (robotDirection == 2)
    robotDirection = 3;
  else if (robotDirection == 3)
    robotDirection = 0;
  delay (500);
  Serial.print("  xcoordinate " );
  Serial.print(xcoordinate);
  delay (500);
  Serial.print(" ycoordinate ");
  Serial.print(ycoordinate);
  delay (500);
  Serial.print("  robot direction: ");
  Serial.print(robotDirection);
  delay (500);
  Serial.println();

  delay(1000);
}


// Turns 90 degrees to the Left
void turnLeft () {
  motor1.write(120);
  motor2.write(120);
  delay(325);
  motor2.write(95) ;
  delay(65) ;
  motor1.write(90);
  Serial.println("Left");
  if (robotDirection == 0)
    robotDirection = 3;
  else if (robotDirection == 1)
    robotDirection = 0;
  else if (robotDirection == 2)
    robotDirection = 1;
  else if (robotDirection == 3)
    robotDirection = 2;
  delay (500);
  Serial.print("  xcoordinate " );
  Serial.print(xcoordinate);
  delay (500);
  Serial.print(" ycoordinate ");
  Serial.print(ycoordinate);
  delay (500);
  Serial.print("  robot direction: ");
  Serial.print(robotDirection);
  delay(500);
  Serial.println();
  delay(1000);
}


// Turns 180 degrees
void turnAround () {
  //  delay(1000);
  Serial.println("Around");
  if (robotDirection == 0)
    robotDirection = 2;
  else if (robotDirection == 1)
    robotDirection = 3;
  else if (robotDirection == 2)
    robotDirection = 0;
  else if (robotDirection == 3)
    robotDirection = 1;
  delay (500);
  Serial.print("  xcoordinate " );
  Serial.print(xcoordinate);
  delay (500);
  Serial.print(" ycoordinate ");
  Serial.print(ycoordinate);
  delay (500);
  Serial.print("  robot direction: ");
  Serial.print(robotDirection);
  delay(500);
  Serial.println();

  delay(1000);
}


// Gets the number on the Grid of the space right in front of it.
int getFrontNumber() {
  if (robotDirection == 0) {
    return arraything  [ycoordinate - 1][xcoordinate];
  }
  if (robotDirection == 1)  {
    return arraything  [ycoordinate][xcoordinate + 1];
  }
  if (robotDirection == 2) {
    return arraything [ycoordinate + 1][xcoordinate] ;
  }
  if (robotDirection == 3) {
    return arraything  [ycoordinate][xcoordinate - 1];
  }
}


// Gets the number on the Grid of the space to the Right of it.
int getRightNumber() {
  if (robotDirection == 0) {
    return arraything [ycoordinate][xcoordinate + 1] ;

  }
  if (robotDirection == 1)  {
    return arraything  [ycoordinate + 1][xcoordinate];

  }
  if (robotDirection == 2) {
    return arraything  [ycoordinate][xcoordinate - 1];
  }
  if (robotDirection == 3) {
    return arraything  [ycoordinate - 1][xcoordinate];
  }
}


// Gets the number on the Grid of the Space to the Left of it.
int getLeftNumber() {
  if (robotDirection == 0) {
    return arraything [ycoordinate][xcoordinate - 1] ;
  }
  if (robotDirection == 1)  {
    return arraything  [ycoordinate - 1][xcoordinate];
  }
  if (robotDirection == 2) {
    return arraything [ycoordinate][xcoordinate + 1] ;
  }
  if (robotDirection == 3) {
    return arraything  [ycoordinate + 1][xcoordinate];
  }
}



Here is a sample program for the ultrasonic sensors. This program will just avoid anything and everything that gets in the way.
Included in the program is programming for an extra servo simply spinning back and forth on the top of the robot. If you aren’t doing this on your robot, ignore that part of the code, it should have no effect on your program.



//  THIS CODE AVOIDS OBSTACLES
//  IT CAN EITHER ENCOUNTER AN OBSTACLE ON THE RIGHT OR THE LEFT SIDE
//  THEREFORE, WE PROGRAMMED IT TO TURN TO THE LEFT IF IT ENCOUNTERED AN OBSTACLE ON THE RIGHT
//  AND RIGHT IF WE ENCOUNTERED IT ON THE LEFT

//  @author: Pranav


/*
UltraSonic 1
Pin 5 Triggers the Pulse (Yellow lead)
Pin 6 Recieves the Echo  (Orange lead)

UltraSonic 2
Pin 7 Triggers the Pulse (Yellow lead)
Pin 8 Recieves the Echo  (Orange lead)
*/

#include "Servo.h"
Servo motorR;
Servo motorL;
Servo motorS;

// ultrasonic pins
// ultrasonic Right
const int Trig1_pin =  5;  // pin for triggering pulse    INPUT
const int Echo1_pin = 6;   // pin for recieving echo      OUPUT
long duration1;           // how long it takes for the sound to rebound

// ultrasonic Left
const int Trig2_pin = 7;
const int Echo2_pin = 8;
long duration2;

// motor pins
const int MotorLPin = 2;    // Left
const int MotorRPin = 13;    // Right

// spinning ultrasonic motor
const int MotorSpinPin = 3;
int spinCounter = 0;

// sensing or not
boolean isARightWallThere = false;
boolean isALeftWallThere = false;

// which way to turn
boolean Right = true;


void setup() {
  Serial.begin(9600);
  Serial.println ("Starting");
  // ultrasonic 1
  pinMode(Trig1_pin, OUTPUT);        // initialize the pulse pin as output:
  pinMode(Echo1_pin, INPUT);         // initialize the echo_pin pin as an input:
  //ultrasonic 2
  pinMode(7, OUTPUT);        // initialize the pulse pin as output:
  pinMode(Echo2_pin, INPUT);         // initialize the echo_pin pin as an input:
  // motors
  motorR.attach(MotorRPin);
  motorL.attach(MotorLPin);
  motorS.attach(MotorSpinPin);



}


void loop(){
  while (1==1)  {

    if (spinCounter < 2) {
      motorS.write(160);
    }
    else {
      motorS.write(20);
    }
    if (spinCounter >= 3) {
      spinCounter = 0;
    }

    spinCounter ++;

    checkTheRightWall(); 
    checkTheLeftWall();

    if (isARightWallThere == false && isALeftWallThere == false) {
      motorR.write(120);
      motorL.write(72);


    }
    else {

      if (isARightWallThere == true && isALeftWallThere == true){

        motorR.write(0);
        motorL.write(180);
        delay(300);
        motorR.write(80);
        motorL.write(80);
        delay(500);
        motorR.write(0);
        motorL.write(180);

      }

      else {
        if (isARightWallThere == false && isALeftWallThere == true) {

          motorR.write(50);
          motorL.write(90);

        } 
        else {
          if (isARightWallThere == true && isALeftWallThere == false) {

            motorR.write(90);
            motorL.write(140);
          }

        }

      }



    }

  }
}





void checkTheRightWall () {
  digitalWrite(Trig1_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig1_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig1_pin, LOW);
  duration1 = pulseIn(Echo1_pin,10);
  Serial.println("Duration1:  ");
  Serial.println(duration1, DEC);



  if ((duration1 > 4000 || duration1 == 0)) {
    isARightWallThere = false; 
  }
  else {
    isARightWallThere = true;
  }


}


void checkTheLeftWall() {
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  duration2 = pulseIn(Echo2_pin,10);
  Serial.println("Duration2:  ");
  Serial.println(duration2, DEC);


  if ((duration2 > 4000 || duration2 == 0)) {
    isALeftWallThere = false; 
  }
  else {
    isALeftWallThere = true;
  }

}
