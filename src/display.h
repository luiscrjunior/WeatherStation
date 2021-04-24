#include "epd2in66b.h"
#include "epdpaint.h"

#ifndef DISPLAY_H
#define DISPLAY_H

class Display
{
public:
  void init(void);

private:
  Epd epd;
  uint8_t black_buffer[(EPD_WIDTH / 8) * EPD_HEIGHT];
  uint8_t red_buffer[(EPD_WIDTH / 8) * EPD_HEIGHT];
};

#endif
