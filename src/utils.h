#include <display.h>

#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:
  static String removeAccent(String text);
  static int getTextRightPos(Display *display, String text, int16_t x, int16_t y);
};

#endif