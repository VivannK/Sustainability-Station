#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>
#include <HX711.h>

const char* ssid = "PUT NETWORK NAME HERE!!!!";
const char* password = "PUT NETWORK PASSWORD HERE!!!!";

const char* htmlTemplate = 
  "<html>"
  "<head>"
  "<meta http-equiv='refresh' content='5'/>"
  "</head>"
  "<body>"
  "<h1>Weight and Temperature/Humidity Data</h1>"
  "<p>Weight: %s lb</p>"
  "<p>Temperature: %s &deg;F</p>"
  "<p>Humidity: %s %%</p>"
  "</body>"
  "</html>";

const int hx11DT = 32;    // Pin connected to HX711 DT (Data) pin
const int hx11SCK = 33;   // Pin connected to HX711 SCK (Clock) pin
const int dht11Pin = 34;  // Pin connected to DHT11 sensor
const int dhtType = DHT11;

HX711 scale;
DHT dht(dht11Pin, dhtType);

const float calibrationFactor = 0.00963211521; 

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  scale.begin(hx11DT, hx11SCK);
  scale.set_scale(calibrationFactor);
  scale.tare();
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String weightData = String(getWeightData());
    String tempData = String(getTemperatureData());
    String humidityData = String(getHumidityData());
    
    String htmlPage = String(htmlTemplate);
    htmlPage.replace("%s", weightData);
    htmlPage.replace("%s", tempData);
    htmlPage.replace("%s", humidityData);
    
    request->send(200, "text/html", htmlPage);
  });
  
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}

float getWeightData() {
  // Read weight sensor data
  float weight = scale.get_units();
  return weight;
}

float getTemperatureData() {
  // Read temperature data
  float temperature = dht.readTemperature();
  return temperature;
}

float getHumidityData() {
  // Read humidity data
  float humidity = dht.readHumidity();
  return humidity;
}
