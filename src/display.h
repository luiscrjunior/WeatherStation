#include "epd2in66b.h"
#include "epdpaint.h"
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>

#ifndef DISPLAY_H
#define DISPLAY_H

#define COLOR_BLACK 0x0000
#define COLOR_WHITE 0xFFFF
#define COLOR_RED 0xF800

#define ROTATE_270 3

class Display : public Adafruit_GFX
{
public:
  Display() : Adafruit_GFX(EPD_WIDTH, EPD_HEIGHT) {}
  void init(void);
  void display(void);
  void sleep(void);

  void drawPixel(int16_t x, int16_t y, uint16_t color)
  {
    if ((x < 0) || (x >= width()) || (y < 0) || (y >= height()))
      return;

    switch (getRotation())
    {
    case 1:
      _swap_(x, y);
      x = WIDTH - x - 1;
      break;
    case 2:
      x = WIDTH - x - 1;
      y = HEIGHT - y - 1;
      break;
    case 3:
      _swap_(x, y);
      y = HEIGHT - y - 1;
      break;
    }

    uint16_t i = x / 8 + y * (EPD_WIDTH / 8);
    black_buffer[i] = (black_buffer[i] | (1 << (7 - x % 8))); // white
    red_buffer[i] = (red_buffer[i] | (1 << (7 - x % 8)));     // white

    if (color == COLOR_WHITE)
      return;
    else if (color == COLOR_BLACK)
      black_buffer[i] = (black_buffer[i] & (0xFF ^ (1 << (7 - x % 8))));
    else if ((color == COLOR_RED))
      red_buffer[i] = (red_buffer[i] & (0xFF ^ (1 << (7 - x % 8))));
  }

  void fillScreen(uint16_t color)
  {
    uint8_t black = 0xFF;
    uint8_t red = 0xFF;
    if (color == COLOR_WHITE)
      ;
    else if (color == COLOR_BLACK)
      black = 0x00;
    else if (color == COLOR_RED)
      red = 0x00;
    for (uint16_t x = 0; x < sizeof(black_buffer); x++)
    {
      black_buffer[x] = black;
      red_buffer[x] = red;
    }
  }

  template <typename T>
  static inline void
  _swap_(T &a, T &b)
  {
    T t = a;
    a = b;
    b = t;
  };

private:
  Epd epd;
  uint8_t black_buffer[(EPD_WIDTH / 8) * EPD_HEIGHT];
  uint8_t red_buffer[(EPD_WIDTH / 8) * EPD_HEIGHT];
};

#endif
