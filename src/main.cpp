#include <Arduino.h>

#include <display.h>
#include <weather.h>
#include <utils.h>

#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansOblique9pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

#include <icons.h>

Display display;
Weather weather;

void updateWeather()
{

  Weather::weatherInfo_t weatherInfo;

  weather.connect();
  weather.fetch(&weatherInfo);
  weather.disconnect();

  if (weatherInfo.error)
  {
    return;
  }

  Serial.println("[WeatherStation] Initializing Display...");
  display.init();

  Serial.println("[WeatherStation] Printing...");

  /* Rotation */
  display.setRotation(ROTATE_270);

  /* Clear screen */
  display.fillScreen(COLOR_WHITE);

  /* Draw Separators */
  display.drawLine(148, 0, 148, 152, COLOR_BLACK);
  display.drawLine(0, 20, 296, 20, COLOR_BLACK);

  /* Draw Today and Tomorrow labels */
  display.setTextColor(COLOR_BLACK);
  display.setFont(&FreeSans9pt7b);

  display.setCursor(55, 15);
  display.print("Hoje");

  display.setCursor(190, 15);
  display.print("Amanha");

  /* Temperatures */
  display.setFont(&FreeSansBold18pt7b);
  display.setTextColor(COLOR_RED);

  display.setCursor(15, 70);
  display.print(weatherInfo.today_temp);

  display.setCursor(163, 70);
  display.print(weatherInfo.tomorrow_temp);

  /* Draw degree symbol */

  int16_t rightPos = Utils::getTextRightPos(&display, weatherInfo.today_temp, 15, 50);

  display.drawCircle(rightPos + 9, 50, 3, COLOR_RED);
  display.drawCircle(rightPos + 9, 50, 4, COLOR_RED);

  rightPos = Utils::getTextRightPos(&display, weatherInfo.tomorrow_temp, 163, 50);

  display.drawCircle(rightPos + 9, 50, 3, COLOR_RED);
  display.drawCircle(rightPos + 9, 50, 4, COLOR_RED);

  /* Draw Weather icons */
  display.drawBitmap(85, 30, getIcon(weatherInfo.today_icon), 48, 48, COLOR_RED);
  display.drawBitmap(233, 30, getIcon(weatherInfo.tomorrow_icon), 48, 48, COLOR_RED);

  /* Write Weather description */
  display.setFont(&FreeSans9pt7b);
  display.setTextColor(COLOR_BLACK);

  display.setCursor(15, 100);
  display.print(Utils::removeAccent(weatherInfo.today_desc));

  display.setCursor(163, 100);
  display.print(Utils::removeAccent(weatherInfo.tomorrow_desc));

  /* Write UV's */
  display.setCursor(15, 120);
  display.print("UV: " + weatherInfo.today_uv);

  display.setCursor(163, 120);
  display.print("UV: " + weatherInfo.tomorrow_uv);

  /* Write Date/Time that the data were fetched  */
  display.fillRect(0, 130, 296, 22, COLOR_BLACK);

  display.setFont(&FreeMono9pt7b);
  display.setTextColor(COLOR_WHITE);
  display.setCursor(45, 145);
  display.print(weatherInfo.fetched_at);

  /* Transmit to the EPD */
  display.display();

  /* Set sleep mode */
  display.sleep();
}

void setup()
{
  Serial.println("[WeatherStation] Initializing...");

  Serial.begin(115200);

  updateWeather();

  Serial.println("[WeatherStation] Going to sleep...");

  esp_sleep_enable_timer_wakeup(30 * 60 * 1000000); /* wake up every 30 minutes */

  esp_sleep_pd_config(ESP_PD_DOMAIN_MAX, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_deep_sleep_start();
}

void loop()
{
}
