#include <TFT_ILI9163C.h>
#include <SPI.h>

#define WHITE 0xFFFF
#define BLACK 0x0000

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#define BOX_WIDTH 9
#define BOX_HEIGHT 10

#define CS 10
#define DC 9

int x = SCREEN_WIDTH / 2 - BOX_WIDTH / 2;
int y = SCREEN_HEIGHT / 2 - BOX_HEIGHT / 2;

int playerX = SCREEN_WIDTH / 2;
int playerY = 25;

bool dead = false;

int oldX = 0;
int oldY = 0;

int oldPlayerX = 0;
int oldPlayerY = 0;

int speed = 30;

int score = 0;

int direction_x = 2;
int direction_y = 1;

int button1 = 14;
int buttonState1 = 0;

int foodX = SCREEN_WIDTH / 2 - 1;
int oldFoodX = 0;

int foodY = SCREEN_HEIGHT - 20;
int oldFoodY = 0;

TFT_ILI9163C tft = TFT_ILI9163C(CS, DC, 8);


void setup() {
  pinMode(button1, INPUT);
  tft.begin();
  tft.fillScreen(BLACK);
  drawFood();
  drawScore();
}

void loop() {
  if (millis() % speed < 2) {
    if (dead == true)
    {
      tft.setCursor(0, SCREEN_HEIGHT / 2);
      tft.setTextSize(1);
      String gameOverText = "Game Over - Score : ";
      String actualScoreText = gameOverText + score;
      tft.print(actualScoreText);
    }
    else
    {
      buttonState1 = digitalRead(button1);

      if (buttonState1 == HIGH)
      {
        playerY--;
      }
      else
      {
        playerY++;
      }

      drawEnemy();
      drawPlayer();

      if (isFoodEaten())
      {
        clearFood();
        if (foodY == 30)
        {
          foodY = SCREEN_HEIGHT - 20;
        }
        else
        {
          foodY = 30;
        }
        score++;
        tft.fillScreen(BLACK);
        drawFood();
        drawScore();
      }

      if (isDead())
      {
        tft.fillScreen(BLACK);
        dead = true;
      }
    }
  }
}

unsigned long drawEnemy() {
  tft.drawRect(oldX, oldY, BOX_WIDTH, BOX_HEIGHT, BLACK);

  oldX = x;
  oldY = y;

  x += direction_x;
  y += direction_y;

  tft.drawRect(x, y, BOX_WIDTH, BOX_HEIGHT, WHITE);

  if (x >= SCREEN_WIDTH - BOX_WIDTH - 1 || x <= 1 || y <= 0 || y >= SCREEN_HEIGHT - BOX_HEIGHT ) {
    direction_x = -direction_x;
    direction_y = -direction_y;
  }

}

unsigned long drawPlayer() {
  tft.drawPixel(oldPlayerX, oldPlayerY, BLACK);

  oldPlayerX = playerX;
  oldPlayerY = playerY;

  tft.drawPixel(playerX, playerY, WHITE);
}

unsigned long drawScore() {
  tft.setCursor(0, 0);
  tft.setTextSize(2);
  String scoreText = "Score : ";
  String actualScoreText = scoreText + score;
  tft.print(actualScoreText);
}

unsigned long drawFood()
{
  oldFoodX = foodX;
  oldFoodY = foodY;

  tft.fillRect(foodX, foodY, 2, 2, WHITE);
}

bool isDead()
{
  if (playerY >= SCREEN_HEIGHT)
  {
    return true;
  }
  if (playerX >= x  && playerX <= x + BOX_WIDTH)
  {
    if (playerY >= y  && playerY <= y + BOX_HEIGHT)
    {
      return true;
    }
  }
  return false;
}

bool isFoodEaten()
{
  if (playerX >= foodX  && playerX <= foodX + 2)
  {
    if (playerY >= foodY  && playerY <= foodY + 2)
    {
      return true;
    }
  }
  return false;
}

void clearFood()
{
  tft.fillRect(oldFoodX, oldFoodY, 2, 2, BLACK);
}


