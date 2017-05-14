//
//MOTORS
//
int m2Enable = 2;
int m2Forward = 3;
int m2Reverse = 4;
int m1Speed = 100;//FIXME: Calibrate
int baseM1Speed = 100; //FIXME: Calibrate
int m1Enable = 1;
int m1Forward = 5;
int m1Reverse = 6;
int m2Speed = 100;//FIXME: Calibrate
int baseM2Speed = 100; //FIXME: Calibrate
int motorStatus = 0; //0=halt/1=foward/2=left/3=right
//
//SENSORS
//
int leftSensor = A2;
int middleSensor = A1;
int rightSensor = A0;
int leftVal = 0;
int midVal = 0;
int rightVal = 0;
int baseReadingWall = 40;//Callibrated value for wall reading
int baseReading = 40; //Callibrated value for no wall
int offsetVal = 0;
//
//ENCODERS
//
int encoder1 = 20;
int encoder2 = 21;
int encoderCount1 = 0;
int encoderCount2 = 0;
int encoderAvg = 0;
int tickGoal = 0; 
//
//Navigation
//
int wallCase = 0; //0=left,forward,right/1=left,forward/2=left,right/3=left/4=forward,right/5=forward/6=right/7=uturn
int dir = 0; //0=north/1=east/2=south/3=west
int currX = 0;
int currY = 0;
int nextX = 0;
int nextY = 0;
//static int getCountsM1();
//static int getCountsM2();
//static int getCountsAndResetM1();
//static int getCountsAndResetM2();

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




void halt()
{
  motorStatus = 0;
  digitalWrite(m1Enable, LOW);//deactivates motors
  digitalWrite(m2Enable, LOW);
}
  
void calibrate(){ //Gets readings that will be used to compare to future readings
 baseReadingWall = analogRead(leftSensor); //Used to infer information about its environment
 baseReading = analogRead(middleSensor);
}
void start()
{
  offsetVal = 0;  //FIXME: Calibrate
  motorStatus = 0;
  while(motorStatus == 0) //continues to check for the start signal
  {
  if(analogRead(middleSensor) > baseReading+offsetVal) //Starts the algorithm when a finger is waved in front of the middle sensor.
  {
    calibrate();
    forward();
  }
  else{
    halt();
  }
  }
}

void determineWallCase()
{
  //uses bit representation of walls, where a one represents a wall and a zero represents no wall
  //EX: 0=000=no walls, 5=101=a wall on the left and right

if(leftVal <= baseReadingWall + offsetVal)&&(midVal <= baseReadingWall + offsetVal)&&(rightVal <= baseReadingWall + offsetVal))
//left, forward, or right
{
wallCase = 0;
}

else if((leftVal <= baseReadingWall + offsetVal)&&(midVal <= baseReadingWall + offsetVal)&&(rightVal >= baseReadingWall + offsetVal))
//left, or forward
{
wallCase = 1;  
}

else if(leftVal <= baseReadingWall + offsetVal)&&(midVal >= baseReadingWall + offsetVal)&&(rightVal <= baseReadingWall + offsetVal))
//left, or right
{
wallCase = 2;
}

else if(leftVal <= baseReadingWall + offsetVal)&&(midVal >= baseReadingWall + offsetVal)&&(rightVal >= baseReadingWall + offsetVal))
//left
{
  wallCase = 3;
}

else if(leftVal >= baseReadingWall + offsetVal)&&(midVal <= baseReadingWall + offsetVal)&&(rightVal <= baseReadingWall + offsetVal))
// forward, or right
{
wallCase = 4; 
}

else if(leftVal >= baseReadingWall + offsetVal)&&(midVal >= baseReadingWall + offsetVal)&&(rightVal <= baseReadingWall + offsetVal))
//right
{
wallCase = 6;
}

else if(leftVal >= baseReadingWall + offsetVal)&&(midVal >= baseReadingWall + offsetVal)&&(rightVal >= baseReadingWall + offsetVal))
//dead end
{
wallCase = 7;
} 
}




void forward()
{
  
  motorStatus = 1;
  digitalWrite(m1Enable, HIGH); //m1 is left motor, m2 is right motor
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m2Reverse, LOW);
  digitalWrite(m1Reverse, LOW); 
  //
  //FIXME: determine motor speeds based on wall case
  //
  analogWrite(m2Forward, m1Speed);//initialize the forward motion by assigning the motor speeds to the motors
  analogWrite(m1Forward, m2Speed);
  while (encoderCount1 < tickGoal)//tick goal is one unit step
  {
  if(digitalRead(encoder1) == 1)
  {
   ++encoderCount1;  
  }
  if(digitalRead(encoder2) == 1)
  {
    ++encoderCount2;
  }
  
 
  }
  halt();
  

  m1Speed = baseM1Speed;
  m2Speed = baseM2Speed;
  encoderCount1 = 0;
  encoderCount2 = 0;

    //update location
  if(dir == 0)
  {
    ++currY;
  }
  else if(dir == 1)
  {
    ++currX;
  }
  else if(dir == 2)
  {
    --currY;
  }
  else if(dir == 3)
  {
    --currX;
  }
  nextX=currX;//update start point for the next location, which is calculated in the loop
  nextY=currY;
  }
  
  

void left()
{
  //choice number
  motorStatus = 2;
  //Set motors on
  digitalWrite(m1Enable, HIGH);//left motor reverse, right motor foward
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m1Forward, LOW);
  digitalWrite(m1Reverse, HIGH);
  digitalWrite(m2Forward, HIGH);
  digitalWrite(m2Reverse, LOW);

  while (encoderCount2 < tickGoal)
  {
  if(digitalRead(encoder2) == 1)
  {
  ++encoderCount2;   
  }
  }
  halt();
  encoderCount2 = 0;

      //update direction
  if(dir == 0)
  {
    dir=4;
  }
  else if(dir == 1)
  {
    dir=0;
  }
  else if(dir == 2)
  {
    dir=1;
  }
  else if(dir == 3)
  {
    dir=3;
  }

  }

  


void right()
{
  motorStatus = 3;
  digitalWrite(m1Enable, HIGH);
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m2Forward, LOW);
  digitalWrite(m2Reverse, HIGH);
  digitalWrite(m1Forward, HIGH);
  digitalWrite(m1Reverse, LOW);

  while (encoderCount1 < tickGoal)
  {
  if(digitalRead(encoder1) == 1)
  {
  ++encoderCount1;   
  }
  }
  halt();
  encoderCount1 = 0;
    //update direction
  if(dir == 0)
  {
    dir=1;
  }
  else if(dir == 1)
  {
    dir=2;
  }
  else if(dir == 2)
  {
    dir=3;
  }
  else if(dir == 3)
  {
    dir=4;
  }
  }



void uTurn()
{
  //turn around
  left();
  left();
}




void setup()
{
  Serial.begin(9600);
  pinMode(m1Enable, OUTPUT);
  pinMode(m2Enable, OUTPUT);
  pinMode(m2Forward, OUTPUT);
  pinMode(m2Reverse, OUTPUT);
  pinMode(m1Forward, OUTPUT);
  pinMode(m1Reverse, OUTPUT);
  pinMode(leftSensor, INPUT);
  pinMode(middleSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(encoder1, INPUT);
  pinMode(encoder2, INPUT);
  digitalWrite(m1Enable, LOW);
  digitalWrite(m2Enable, LOW);
 // PololuWheelEncoders::init('20', '18', '21', '19');
  calibrate();
  start();
  
}

void loop() 
{
//State machine
//default state is in the center of a cell
if(baseMaze[currX][currY] != 0)
{
leftVal = analogRead(leftSensor); //Read Peripherals
midVal = analogRead(middleSensor);
rightVal = analogRead(rightSensor);
//Determine wall case
//
determineWallCase(); 
//if intersection => check for unvisited cells
if(wallCase == 0)
//left, forward, or right
{
  randomChoice = random(0, 2);
  if(randomChoice = 0)
  {
    left();
  }
  else if(randomChoice = 1)
  {
    forward();
  }
  else if(randomChoice = 2)
  {
    right();  
  }
  

}

else if(wallCase == 1)
//left, or forward
{
  randomChoice = random(0,1);
  if(randomChoice = 0)
  {
    left();
  }
  else if(randomChoice = 1)
  {
    forward();
  }

}

else if(wallCase == 2)
//left, or right
{
  randomChoice = random(0, 1);
  if(randomChoice = 0)
  {
    left();
  }
  else if(randomChoice = 1)
  {
    right();
  }
}

else if(wallCase == 3)
//left
{
  left();
}


else if(wallCase == 4)
//forward or right
{
  randomChoice = random(1, 2);

  else if(randomChoice = 1)
  {
    forward();
  }
  else if(randomChoice = 2)
  {
    right();  
  }
}

else if(wallCase == 5)
//forward
{
  forward();
}

else if(wallCase == 6)
//right
{
  right();
}

else if(wallCase == 7)
//uturn
{
  uturn();
}

//take direction that hasn't been visited and meets the algorithm requirement
//update next cell with a one, meaning that it has been visited
//if deadEnd => uturn
//if one direction =>take that direction
//
//take action
//
//update location (in foward Function)
//read sensor values
//update motorSpeed values based on these readings

}

else
{
halt();  
}
}
