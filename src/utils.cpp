#include <utils.h>

int Utils::getTextRightPos(Display *display, String text, int16_t x, int16_t y)
{
  int16_t x1, y1;
  uint16_t w, h;
  display->getTextBounds(text, x, y, &x1, &y1, &w, &h);
  return x1 + w;
};

String Utils::removeAccent(String text)
{
  String textWithoutAccent = text;
  textWithoutAccent.toLowerCase();
  textWithoutAccent.replace("á", "a");
  textWithoutAccent.replace("é", "e");
  textWithoutAccent.replace("í", "i");
  textWithoutAccent.replace("ó", "o");
  textWithoutAccent.replace("ú", "u");
  return textWithoutAccent;
}