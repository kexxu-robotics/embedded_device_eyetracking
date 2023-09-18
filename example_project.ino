#include <arduino.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// === Fill in the required information below ===
const char*  WIFI_SSID = "<your-wifi-ssid>";
const char*  WIFI_PSWD = "<your-wifi-password>";
const String DEVICE_ID = "<your-glasses-device-id>";
const char*  DEVICE_IP = "<your-glasses-ip-address>"; // can be found in the kexxu app

// === These values are predefined by Kexxu, you do not need to make changes ===
const int mqtt_port = 1883;
const char* mqtt_user = "kexxu";
const char* mqtt_pass = "vySgEjzJ524Er6PUaK6zKAKUe5MfAP";

WiFiMulti WiFiMulti;
WiFiClient espClient;
PubSubClient client(espClient);
int value = 0;

void setup(void) {
  Serial.begin(115200);
  // add wifi name and password
  WiFiMulti.addAP(WIFI_SSID, WIFI_PSWD);

  if (connectWifi(10)) {  // connected to your wifi
    client.setBufferSize(4096);
    client.setServer(DEVICE_IP, mqtt_port);
    client.setCallback(callback);
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

// connect wifi, returns if success
bool connectWifi(int max_retries) {
  Serial.println();
  Serial.print("Waiting for WiFi... ");

  int waitForWifiN = 0;
  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
    waitForWifiN++;
    if (waitForWifiN > max_retries) {
      Serial.println("waiting for WiFi timed out, aborting");
      WiFi.mode(WIFI_OFF);
      return false;
    }
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(500);

  return true;
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(DEVICE_ID.c_str(), mqtt_user, mqtt_pass)) {
      // subscribing to the eyetracking channel to receive values
      // from the Kexxu Eye Tracking Glasses
      Serial.println("connected");
      String topic = "devices/" + DEVICE_ID + "/eyetracking";
      client.subscribe(topic.c_str());
      Serial.println("subscribed to " + topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

// this gets automatically called when new data is available
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  Serial.println(messageTemp);

  DynamicJsonDocument doc(4096);
  deserializeJson(doc, messageTemp);

  // this is how you can extract the values from the messages:
  double pupil_rel_pos_x = doc["pupil_rel_pos_x"];
  double pupil_rel_pos_y = doc["pupil_rel_pos_y"];
  
  String output = "";
  output += pupil_rel_pos_x;
  output += ", ";
  output += pupil_rel_pos_y;
  Serial.println(output);
}