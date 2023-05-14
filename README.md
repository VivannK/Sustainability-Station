# Sustainability-Station
By Umang Sharma and Vivann Khanna

## Inspiration
We saw the amount of food that is being wasted on a daily basis when we did our compost duty and thought that with this device we can raise awareness. Along with that, we thought it can make compost duty much easier by automatically uploading the weight to the web server so that we don't have to manually do it. We also thought that in addition, we could add a temp and humidity sensor to make sure that we are sustainable in other factors besides food waste.

## What it does
As said above, it uses a weight sensor to upload weight data to the server and allows us to easily get weight data instead of manually having to do it. It also uploads temp and humidity sensor data to the server.

## How we built it
We built it by using an esp32 board with Arduino IDE. Since it has wifi capabilities, we used those to make a web server. Then we also used an hx11 weight sensor and a DHT11 humidity and temp sensor.

## Challenges we ran into
The main challenge that we ran into was trying to get the IP to work, it would always load forever and say it was unreachable.
