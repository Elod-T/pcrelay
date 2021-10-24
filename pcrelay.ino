#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <PubSubClient.h>

// wifi
const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";

// mqtt
const char* mqtt_server = "YOUR MQTT BROKER IP";
const char* mqtt_client_name = "YOUR CLIENT NAME";
const char* mqtt_user = "YOUR MQTT USER"; // if you don't have an account uncomment line 91 and 103, and comment the ones above them
const char* mqtt_pass = "YOUR MQTT PASSWORD";
const char* command_topic = "YOUR COMMAND TOPIC";
WiFiClient espClient;
PubSubClient client(espClient);

// relay
const int relayPin = D1;
const long interval = 1000;

bool check_number(String str) {
  for (int i = 0; i < str.length(); i++){
    if (isDigit(str[i]) == false)
      return false;
  }
  return true;
}

AsyncWebServer server(80);

void callback(String topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  messageTemp.toLowerCase();
  
  if(topic==command_topic){
    if(check_number(messageTemp) == false) {
      if(messageTemp == "on" or messageTemp == "off"){
        digitalWrite(relayPin, HIGH);
        delay(interval);
        digitalWrite(relayPin, LOW);
      }
    } else {
      digitalWrite(relayPin, HIGH);
      delay((messageTemp.toInt() % 11) * 1000);
      digitalWrite(relayPin, LOW);
    }
  }
  Serial.println();
}

void setup(void) {
  Serial.begin(115200);
  // connect to wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hi there, i'm an ESP8266 pc relay!");
  });

  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");

  // mqtt
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.connect(mqtt_client_name, mqtt_user, mqtt_pass);
  //client.connect(mqtt_client_name); // uncomment to authenticate without a user
  client.subscribe(command_topic);

  // relay
  pinMode(relayPin, OUTPUT);
}

void loop(void) {
  if(client.connected()) {
    client.loop();
  } else {
    client.connect(mqtt_client_name, mqtt_user, mqtt_pass);
    //client.connect(mqtt_client_name); // uncomment to authenticate without a user
    client.subscribe(command_topic);
  }
}