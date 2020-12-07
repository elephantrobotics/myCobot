#include <MycobotBasic.h>

MycobotBasic myCobot;

double one_PI = 3.142;  // 180 degree
double half_PI = 1.571; // 90 degree

// setup 6 points with coords - xyz(mm) and euler angles(radian)
double points[6][6] = {{-80.2,  -100.8, 260.3,  0.0,0.0,0.0},
                        {30.3,  -170.4, 230.5,  half_PI,  one_PI,   0.0},
                        {-21.6, 43.7,   307.8,  -half_PI, 0,        one_PI},
                        {78.9,  -102.1, 277.2,  half_PI,  half_PI,  half_PI},
                        {168.3, 20.3,   231.7,  -half_PI, -half_PI, 0.0},
                        {-128.4,  30.3, 233.4,  half_PI,  0.0,      -half_PI}};

void setup() {
  myCobot.setup();
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  Serial.println("point 0");

  int sp = 600;

  // Move to Angle
  myCobot.moveToAngle(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1, sp);

  delay(5000);
 
  // Move to Coords 6 points
  for(int i = 0; i < 6; ++i)
  {
    Serial.print("point ");
    Serial.println(i + 1);
    myCobot.moveToCoord(points[i][0], points[i][1], points[i][2], points[i][3], points[i][4], points[i][5], 1, sp);
    delay(3000);
  }

 

}
