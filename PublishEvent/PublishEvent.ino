#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ArduinoHttpClient.h>
#include <Arduino.h>

const char* ssid     = "FamSA"; // Your WiFi ssid
const char* password = "Malevola#1"; //Your Wifi password

// Get this secret key from the wia dashboard. It should start with `d_sk`
const char* device_secret_key = "d_sk_91j6w1rsl4Uox8sezwys1Fxm";

// Wia API parameters
char server[] = "api.wia.io";
char path[] = "/v1/events";
int port = 80;

WiFiClient client;
int status = WL_IDLE_STATUS;

StaticJsonBuffer<200> jsonBuffer;
HttpClient httpClient = HttpClient(client, server, port);
JsonObject& root = jsonBuffer.createObject();
String response;
int statusCode = 0;
String dataStr;
int gasStatus;
const int ANALOG_PIN = 0;

void setup() {
  
  // initialize serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  WiFi.begin(ssid, password);
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  // attempt to connect to WiFi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Connect to WPA/WPA2 network. Change this line if using open or WEP  network:
    // wait 5 seconds for connection:
    delay(5000);
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("connecting...");
}

// Thing function runs continiously
void loop() {
  
  root["name"] = "Olimpo";
  root["data"] =  analogRead (ANALOG_PIN);

  // if you get a connection, report back via serial:
  if (client.connect(server, port)) {

    sendToWia(root);

  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  delay(1000*15*60); // Wait for 15 minutes to post again
}

// Adds the correct headers for HTTP and sends Data to Wia
void sendToWia(JsonObject& data) {
  data.printTo(dataStr);
  httpClient.beginRequest();
  httpClient.post(path);
  httpClient.sendHeader("Content-Type", "application/json");
  httpClient.sendHeader("Content-Length", data.measureLength());
  httpClient.sendHeader("Authorization", "Bearer "  + String(device_secret_key));
  httpClient.beginBody();
  httpClient.print(dataStr);
  httpClient.endRequest();
}
