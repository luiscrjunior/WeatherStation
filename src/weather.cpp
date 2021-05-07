#include <weather.h>

void Weather::connect(void)
{
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(3000);
    Serial.println("[WeatherStation] Connecting to WiFi...");
  }
  Serial.println("[WeatherStation] Connected to WiFi.");
}

void Weather::disconnect(void)
{
  Serial.println("[WeatherStation] WiFi disconnecting...");
  WiFi.disconnect();
}

void Weather::fetch(weatherInfo_t *weatherInfo)
{
  HTTPClient http;
  DynamicJsonDocument doc(32768);

  Serial.println("[WeatherStation] Fething weather data...");

  String url = "http://api.openweathermap.org/data/2.5/onecall?lat=" +
               String(WEATHER_COORDS_LAT) +
               "&lon=" +
               String(WEATHER_COORDS_LON) +
               "&units=metric&appid=" +
               WEATHER_API +
               "&lang=pt_br";

  http.begin(url.c_str());

  int httpResponseCode = http.GET();

  if (httpResponseCode == HTTP_CODE_OK)
  {
    String payload = http.getString();
    DeserializationError error = deserializeJson(doc, payload);
    if (error)
    {
      Serial.println("[WeatherStation] Error when deserializing JSON response.");
      Serial.println(error.f_str());
      weatherInfo->error = true;
      return;
    }

    int today_temp = doc["current"]["temp"].as<int>();
    int tomorrow_temp = doc["daily"][1]["temp"]["morn"].as<int>();
    unsigned long fetched_at_epoch = doc["current"]["dt"].as<long>() - 10800;

    String fetched_at = String(day(fetched_at_epoch)) +
                        "/" + String(month(fetched_at_epoch)) +
                        "/" + String(year(fetched_at_epoch)) +
                        " " + String(hour(fetched_at_epoch)) +
                        ":" + String(minute(fetched_at_epoch)) +
                        ":" + String(second(fetched_at_epoch));

    weatherInfo->error = false;

    weatherInfo->today_temp = String(today_temp);
    weatherInfo->today_uv = doc["current"]["uvi"].as<String>();
    weatherInfo->today_icon = doc["current"]["weather"][0]["icon"].as<String>();
    weatherInfo->today_desc = doc["current"]["weather"][0]["description"].as<String>();

    weatherInfo->tomorrow_temp = String(tomorrow_temp);
    weatherInfo->tomorrow_uv = doc["daily"][1]["uvi"].as<String>();
    weatherInfo->tomorrow_icon = doc["daily"][1]["weather"][0]["icon"].as<String>();
    weatherInfo->tomorrow_desc = doc["daily"][1]["weather"][0]["description"].as<String>();

    weatherInfo->fetched_at = fetched_at;
  }
  else
  {
    weatherInfo->error = true;
  }

  Serial.println("[WeatherStation] Weather data fetched.");
}
