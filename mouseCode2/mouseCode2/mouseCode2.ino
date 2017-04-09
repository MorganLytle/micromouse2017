

#include <PololuWheelEncoders.h>

int m1Enable = 2;
int m1Logic1 = 3;
int m1Logic2 = 4;
int m2Enable = 1;
int m2Logic1 = 5;
int m2Logic2 = 6;
int leftSensor = A2;
int middleSensor = A1;
int rightSensor = A0;
int baseReadingWall = 40;//Callibrated value for wall reading
int baseReading = 40; //Callibrated value for no wall
//int encoder1 = ;//FIXME
//int encoder2 = ;//FIXME
int motorStatus = 0; //0=halt/1=foward/2=left/3=right
int leftVal = 0;
int midVal = 0;
int rightVal = 0;
int wallCase = 0;
int deadEndFlag = 0;
int offset = 0;
int dir = 0; //0=north/1=east/2=south/3=west
int leftDistance = 0;
int rightDistance = 0;
int wallFollowStatus = 0; //0 = right follow/1 = left follow
static int getCountsM1();
static int getCountsM2();
static int getCountsAndResetM1();
static int getCountsAndResetM2();
int baseMaze[16][16] = { //distances to center with no walls
  {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14},
  {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
  {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
  {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
  {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
  {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
  {8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
  {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
  {7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7},
  {8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8},
  {9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9},
  {10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10},
  {11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11},
  {12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12},
  {13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13},
  {14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14}
};

int visitedMaze[16][16] ={ //map of paths that are dead ends
  //if a cell has a one, then that path is a dead end
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int currX = 0;
int currY = 0;

void halt()
{
  motorStatus = 0;
  digitalWrite(m1Enable, LOW);
  digitalWrite(m2Enable, LOW);
}
  
void calibrate(){ //Gets readings that will be used to compare to future readings
 baseReadingWall = analogRead(leftSensor); //Used to infer information about its environment
 baseReading = analogRead(middleSensor);
}
void start()
{
  int offset = 0;
  if(analogRead(middleSensor) > baseReading+offset)//
  {
    calibrate();
    forward();
  }
  else{
    halt();
  }
}



void forward( )
{
  int motorValue = 150;
  motorStatus = 1;

  digitalWrite(m1Enable, HIGH); //m1 is left motor, m2 is right motor
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m1Logic1, LOW);
  digitalWrite(m2Logic1, LOW); 
  analogWrite(m1Logic2, motorValue);
  analogWrite(m2Logic2, motorValue);
  
  }
  

void left()
{
  //choice number
  motorStatus = 2;
  //Set motors on
  digitalWrite(m1Enable, HIGH);//left motor reverse, right motor foward
  digitalWrite(m2Enable, HIGH);
  //turn left (want to incorporate encoder here somehow)
  //need to know how much the digitalWrite moves the wheels by (definitely or indefinitely?)
  digitalWrite(m2Logic1, LOW);
  digitalWrite(m2Logic2, HIGH);
  digitalWrite(m1Logic1, HIGH);
  digitalWrite(m1Logic2, LOW);

  
}

void right()
{
  motorStatus = 3;
  digitalWrite(m1Enable, HIGH);
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m1Logic1, LOW);
  digitalWrite(m1Logic2, HIGH);
  digitalWrite(m2Logic1, HIGH);
  digitalWrite(m2Logic2, LOW);
  
}

//void uTurn()
//{
//  //turn around
    //go back
//}

void leftCheck()
{
  if(dir == 0)
  {
    leftDistance = baseMaze[currX - 1][currY];
  }
  else if(dir==1)
  {
    leftDistance = baseMaze[currX][currY + 1];
  }
  else if(dir==2)
  {
    leftDistance = baseMaze[currX + 1][currY];
  }
  else if(dir==3)
  {
    leftDistance = baseMaze[currX][currY - 1];
  }
}

void rightCheck()
{
  if(dir == 0)
  {
    rightDistance = baseMaze[currX + 1][currY];
  }
  else if(dir==1)
  {
    rightDistance = baseMaze[currX][currY - 1];
  }
  else if(dir==2)
  {
    rightDistance = baseMaze[currX - 1][currY];
  }
  else if(dir==3)
  {
    rightDistance = baseMaze[currX][currY + 1];
  }
}


void setup()
{
  Serial.begin(9600);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  pinMode(m1Logic1, OUTPUT);
  pinMode(m1Logic2, OUTPUT);
  pinMode(m2Logic1, OUTPUT);
  pinMode(m2Logic2, OUTPUT);
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
 // pinMode(encoder1, INPUT);
 // pinMode(encoder2, INPUT);
  calibrate();
  start();
  
}

void loop() 
{
//State machine
//default=>Read Peripherals =>Determine Walls=> update maze=>choose next step=>Take Action=>Adjust Motor Speed (Proportional)
//default state is in the center of a cell
leftVal = analogRead(leftSensor); //Read Peripherals
midVal = analogRead(middleSensor);
rightVal = analogRead(rightSensor);

if(!((currX == 8)&&(currY == 8))||((currX == 8)&&(currY == 7))||((currX == 7)&&(currY == 8))||((currX == 7)&&(currY == 7)))
{//check if at center
  //determine wall case

//if not at center {
//check at intersection

//check if boundary
if(currX == 0)
{
  if(dir == 0)
  {
    rightCheck();
  }
  if(dir == 1)
  {
    rightCheck();
    leftCheck();
    
  }
  if(dir == 2)
  {
    leftCheck();
  }
}
else if(currY == 0)
{
  
}
else if(currX == 8)
{
  
}
else if(currY == 8)
{

}

else
{

//check the distance of cell adjacent 
}
//initiate appropriate wall follow
//check wall follow criteria
//if intersection, store location, and come back to this location if there is a dead end,
//and cut off that section with visited bits
//}
//else{halt}
}
else
{
  halt();
}




















}
