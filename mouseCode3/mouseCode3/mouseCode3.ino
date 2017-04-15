

int m1Enable = 2;
int m1Logic1 = 3;
int m1Logic2 = 4;
int m1Speed = 100;
int m2Enable = 1;
int m2Logic1 = 5;
int m2Logic2 = 6;
int m2Speed = 100;
int leftSensor = A2;
int middleSensor = A1;
int rightSensor = A0;
int baseReadingWall = 40;//Callibrated value for wall reading
int baseReading = 40; //Callibrated value for no wall
int encoder1 = 20;
int encoder2 = 21;
int encoderCount1 = 0;
int encoderCount2 = 0;
int encoderAvg = 0;
int tickGoal = 0;
int motorStatus = 0; //0=halt/1=foward/2=left/3=right
int leftVal = 0;
int midVal = 0;
int rightVal = 0;
int wallCase = 0;
int deadEndFlag = 0;
int offsetVal = 0;
int dir = 0; //0=north/1=east/2=south/3=west
int leftDistance = 0;
int rightDistance = 0;
int wallFollowStatus = 0; //0 = right follow/1 = left follow


int currX = 0;
int currY = 0;
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
  digitalWrite(m1Enable, LOW);
  digitalWrite(m2Enable, LOW);
}
  
void calibrate(){ //Gets readings that will be used to compare to future readings
 baseReadingWall = analogRead(leftSensor); //Used to infer information about its environment
 baseReading = analogRead(middleSensor);
}
void start()
{
  int offsetVal = 0;
  if(analogRead(middleSensor) > baseReading+offsetVal)//
  {
    calibrate();
    forward(m1Speed, m2Speed);
  }
  else{
    halt();
  }
}



void forward(int m1Speed, int m2Speed)
{
  
  motorStatus = 1;
  digitalWrite(m1Enable, HIGH); //m1 is left motor, m2 is right motor
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m1Logic1, LOW);
  digitalWrite(m2Logic1, LOW); 
  analogWrite(m1Logic2, m1Speed);
  analogWrite(m2Logic2, m2Speed);
  while (encoderCount1 < tickGoal)
  {
  if(digitalRead(encoder1) == 1)
  {
  ++encoderCount1;   
  }
  }
  halt();
  encoderCount1 = 0;
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
  }
  
  

void left()
{
  //choice number
  motorStatus = 2;
  //Set motors on
  digitalWrite(m1Enable, HIGH);//left motor reverse, right motor foward
  digitalWrite(m2Enable, HIGH);
  digitalWrite(m2Logic1, LOW);
  digitalWrite(m2Logic2, HIGH);
  digitalWrite(m1Logic1, HIGH);
  digitalWrite(m1Logic2, LOW);

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
  digitalWrite(m1Logic1, LOW);
  digitalWrite(m1Logic2, HIGH);
  digitalWrite(m2Logic1, HIGH);
  digitalWrite(m2Logic2, LOW);

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
  pinMode(encoder1, INPUT);
  pinMode(encoder2, INPUT);
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
 
//if intersection => check for unvisited cells
if((analogRead(leftSensor) <= baseReadingWall + offsetVal)&&(analogRead(middleSensor) <= baseReadingWall + offsetVal)&&(analogRead(rightSensor) <= baseReadingWall + offsetVal))
//left, forward, or right
{
  
}

if((analogRead(leftSensor) <= baseReadingWall + offsetVal)&&(analogRead(middleSensor) <= baseReadingWall + offsetVal)&&(analogRead(rightSensor) >= baseReadingWall + offsetVal))
//left, or forward
{
  
}

if((analogRead(leftSensor) >= baseReadingWall + offsetVal)&&(analogRead(middleSensor) <= baseReadingWall + offsetVal)&&(analogRead(rightSensor) <= baseReadingWall + offsetVal))
// forward, or right
{
  
}
if((analogRead(leftSensor) <= baseReadingWall + offsetVal)&&(analogRead(middleSensor) >= baseReadingWall + offsetVal)&&(analogRead(rightSensor) <= baseReadingWall + offsetVal))
//left, or right
{
  
}

if((analogRead(leftSensor) >= baseReadingWall + offsetVal)&&(analogRead(middleSensor) >= baseReadingWall + offsetVal)&&(analogRead(rightSensor) >= baseReadingWall + offsetVal))
//dead end
{
  uTurn();
}

if((analogRead(leftSensor) <= baseReadingWall + offsetVal)&&(analogRead(middleSensor) >= baseReadingWall + offsetVal)&&(analogRead(rightSensor) >= baseReadingWall + offsetVal))
//left
{
  left();
}

if((analogRead(leftSensor) >= baseReadingWall + offsetVal)&&(analogRead(middleSensor) >= baseReadingWall + offsetVal)&&(analogRead(rightSensor) <= baseReadingWall + offsetVal))
//right
{
  right();
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
//update motor values based on these readings
}

else
{
halt();  
}
}
