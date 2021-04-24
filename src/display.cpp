#include <display.h>
#include <SPI.h>

#define COLORED 0
#define UNCOLORED 1

void Display::init(void)
{

  if (epd.Init() != 0)
  {
    Serial.print("e-Paper init failed...");
    return;
  }

  Paint paint_black(black_buffer, EPD_WIDTH, EPD_HEIGHT);
  Paint paint_red(red_buffer, EPD_WIDTH, EPD_HEIGHT);

  Serial.print("e-Paper Clear...\r\n ");
  epd.Clear();

  Serial.print("paint......\r\n ");

  paint_black.SetRotate(ROTATE_270);
  paint_red.SetRotate(ROTATE_270);

  paint_black.Clear(UNCOLORED);
  paint_red.Clear(UNCOLORED);
  paint_black.DrawStringAt(0, 30, "Bianca!", &Font24, COLORED);

  epd.DisplayFrame(black_buffer, red_buffer);

  epd.Sleep();
}