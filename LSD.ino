#include <TFT_ILI9163C.h>

#define WHITE   0xFFFF
#define RED   0xF800

#define CS 10
#define DC 9

int x = 0;
int y = 0;

TFT_ILI9163C tft = TFT_ILI9163C(CS, DC, 8);

void setup() {
  tft.begin();
  tft.fillScreen();
}

void loop(){
  draw();
  delay(500);
  x++;
  y++;
}

unsigned long draw() {
  
  tft.setCursor(x, y);
  tft.setTextColor(WHITE);  
  tft.setTextSize(1);
  tft.drawRect(x, 0, 100, 100, WHITE);
  tft.drawRect(0, y, 100, 100, RED);
}
  
