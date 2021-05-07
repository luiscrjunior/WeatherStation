# WeatherStation

![WeatherStation_Thumb](https://user-images.githubusercontent.com/13292515/117494807-3a45e800-af4b-11eb-9557-6a5b6ca96655.jpg)

Current ESP32 code from the Weather Station that I made that fetches through WiFi data from openweathermap API and displays some weather info (temperature, weather description, icon and UV data) for today and next day.

Used ESP32 board with Waveshare 2.66inch (three colors) E-paper, that works with 18650 battery.

Updates every 30 minutes. After the display is updated, the ESP32 goes into sleep mode, to save battery. But the information remains in the screen due to e-paper technology.

3D printed the cloud shaped case made with Fusion 360. Painted blue. Hosted at https://www.thingiverse.com/thing:4852197

Displayed data is in Portuguese (Brazil), but the code is in English.

## Using

If you're gonna use this ESP32 code, remember to rename `secrets.example.h` to `secrets.h` with your data.
