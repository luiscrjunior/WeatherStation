#include <WiFi.h>
#include <HTTPClient.h>
#include <secrets.h>
#include <ArduinoJson.h>
#include <TimeLib.h>

class Weather
{
public:
  struct weatherInfo_t
  {
    bool error;
    String today_temp;
    String today_uv;
    String today_icon;
    String today_desc;
    String tomorrow_temp;
    String tomorrow_uv;
    String tomorrow_icon;
    String tomorrow_desc;
    String fetched_at;

    weatherInfo_t()
    {
      error = false;

      today_temp = "";
      today_uv = "";
      today_icon = "";
      today_desc = "";

      tomorrow_temp = "";
      tomorrow_uv = "";
      tomorrow_icon = "";
      tomorrow_desc = "";

      fetched_at = "";
    }
  };
  void connect();
  void disconnect();
  void fetch(weatherInfo_t *weatherInfo);
};