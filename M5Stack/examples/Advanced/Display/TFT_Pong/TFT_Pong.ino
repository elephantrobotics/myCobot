/*
 * Pong
 * Original Code from https://github.com/rparrett/pongclock
 *
 */

// Demo only - not playable

#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREY  0x5AEB

#include <M5Stack.h>

int16_t h = 240;
int16_t w = 320;

int dly = 5;

int16_t paddle_h = 30;
int16_t paddle_w = 4;

int16_t lpaddle_x = 0;
int16_t rpaddle_x = w - paddle_w;

int16_t lpaddle_y = 0;
int16_t rpaddle_y = h - paddle_h;

int16_t lpaddle_d = 1;
int16_t rpaddle_d = -1;

int16_t lpaddle_ball_t = w - w / 4;
int16_t rpaddle_ball_t = w / 4;

int16_t target_y = 0;

int16_t ball_x = 2;
int16_t ball_y = 2;
int16_t oldball_x = 2;
int16_t oldball_y = 2;

int16_t ball_dx = 1;
int16_t ball_dy = 1;

int16_t ball_w = 6;
int16_t ball_h = 6;

int16_t dashline_h = 4;
int16_t dashline_w = 2;
int16_t dashline_n = h / dashline_h;
int16_t dashline_x = w / 2 - 1;
int16_t dashline_y = dashline_h / 2;

int16_t lscore = 12;
int16_t rscore = 4;

void setup(void) {
  
  randomSeed(analogRead(35)*analogRead(36));
   
  M5.begin();
  M5.Power.begin();
  // M5.Lcd.setRotation(1);

  M5.Lcd.fillScreen(BLACK);
  
  initgame();

  M5.Lcd.setTextColor(WHITE, BLACK);
  
}

void loop() {
  delay(dly);

  lpaddle();
  rpaddle();

  midline();

  ball();
}

void initgame() {
  lpaddle_y = random(0, h - paddle_h);
  rpaddle_y = random(0, h - paddle_h);

  // ball is placed on the center of the left paddle
  ball_y = lpaddle_y + (paddle_h / 2);
  
  calc_target_y();

  midline();

  // M5.Lcd.fillRect(0,h-26,w,239,GREY);

  // M5.Lcd.setTextDatum(TC_DATUM);
  // M5.Lcd.setTextColor(WHITE,GREY);
  // M5.Lcd.drawString("TFT_eSPI example", w/2, h-26 , 4);
}

void midline() {

  // If the ball is not on the line then don't redraw the line
  if ((ball_x<dashline_x-ball_w) && (ball_x > dashline_x+dashline_w)) return;

  // Quick way to draw a dashed line
  M5.Lcd.setAddrWindow(dashline_x, 0, dashline_w, h);
  
  for(int16_t i = 0; i < dashline_n; i+=2) {
    M5.Lcd.pushColor(WHITE, dashline_w*dashline_h); // push dash pixels
    M5.Lcd.pushColor(BLACK, dashline_w*dashline_h); // push gap pixels
  }
}

void lpaddle() {
  
  if (lpaddle_d == 1) {
    M5.Lcd.fillRect(lpaddle_x, lpaddle_y, paddle_w, 1, BLACK);
  } 
  else if (lpaddle_d == -1) {
    M5.Lcd.fillRect(lpaddle_x, lpaddle_y + paddle_h - 1, paddle_w, 1, BLACK);
  }

  lpaddle_y = lpaddle_y + lpaddle_d;

  if (ball_dx == 1) lpaddle_d = 0;
  else {
    if (lpaddle_y + paddle_h / 2 == target_y) lpaddle_d = 0;
    else if (lpaddle_y + paddle_h / 2 > target_y) lpaddle_d = -1;
    else lpaddle_d = 1;
  }

  if (lpaddle_y + paddle_h >= h && lpaddle_d == 1) lpaddle_d = 0;
  else if (lpaddle_y <= 0 && lpaddle_d == -1) lpaddle_d = 0;

  M5.Lcd.fillRect(lpaddle_x, lpaddle_y, paddle_w, paddle_h, WHITE);
}

void rpaddle() {
  
  if (rpaddle_d == 1) {
    M5.Lcd.fillRect(rpaddle_x, rpaddle_y, paddle_w, 1, BLACK);
  } 
  else if (rpaddle_d == -1) {
    M5.Lcd.fillRect(rpaddle_x, rpaddle_y + paddle_h - 1, paddle_w, 1, BLACK);
  }

  rpaddle_y = rpaddle_y + rpaddle_d;

  if (ball_dx == -1) rpaddle_d = 0;
  else {
    if (rpaddle_y + paddle_h / 2 == target_y) rpaddle_d = 0;
    else if (rpaddle_y + paddle_h / 2 > target_y) rpaddle_d = -1;
    else rpaddle_d = 1;
  }

  if (rpaddle_y + paddle_h >= h && rpaddle_d == 1) rpaddle_d = 0;
  else if (rpaddle_y <= 0 && rpaddle_d == -1) rpaddle_d = 0;

  M5.Lcd.fillRect(rpaddle_x, rpaddle_y, paddle_w, paddle_h, WHITE);
}

void calc_target_y() {
  int16_t target_x;
  int16_t reflections;
  int16_t y;

  if (ball_dx == 1) {
    target_x = w - ball_w;
  } 
  else {
    target_x = -1 * (w - ball_w);
  }

  y = abs(target_x * (ball_dy / ball_dx) + ball_y);

  reflections = floor(y / h);

  if (reflections % 2 == 0) {
    target_y = y % h;
  } 
  else {
    target_y = h - (y % h);
  }
}

void ball() {
  ball_x = ball_x + ball_dx;
  ball_y = ball_y + ball_dy;

  if (ball_dx == -1 && ball_x == paddle_w && ball_y + ball_h >= lpaddle_y && ball_y <= lpaddle_y + paddle_h) {
    ball_dx = ball_dx * -1;
    dly = random(5); // change speed of ball after paddle contact
    calc_target_y(); 
  } else if (ball_dx == 1 && ball_x + ball_w == w - paddle_w && ball_y + ball_h >= rpaddle_y && ball_y <= rpaddle_y + paddle_h) {
    ball_dx = ball_dx * -1;
    dly = random(5); // change speed of ball after paddle contact
    calc_target_y();
  } else if ((ball_dx == 1 && ball_x >= w) || (ball_dx == -1 && ball_x + ball_w < 0)) {
    dly = 5;
  }

  if (ball_y > h - ball_w || ball_y < 0) {
    ball_dy = ball_dy * -1;
    ball_y += ball_dy; // Keep in bounds
  }

  //M5.Lcd.fillRect(oldball_x, oldball_y, ball_w, ball_h, BLACK);
  M5.Lcd.drawRect(oldball_x, oldball_y, ball_w, ball_h, BLACK); // Less TFT refresh aliasing than line above for large balls
  M5.Lcd.fillRect(   ball_x,    ball_y, ball_w, ball_h, WHITE);
  oldball_x = ball_x;
  oldball_y = ball_y;
}

