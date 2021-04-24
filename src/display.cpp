#include <display.h>
#include <SPI.h>

void Display::init(void)
{
  if (epd.Init() != 0)
  {
    Serial.println("[ERROR] e-Paper init failed...");
    return;
  }
}

void Display::display(void)
{
  epd.DisplayFrame(black_buffer, red_buffer);
}

void Display::sleep(void)
{
  epd.Sleep();
}