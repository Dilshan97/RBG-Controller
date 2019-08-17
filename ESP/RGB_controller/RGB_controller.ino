/*
   RGB Controller
   this code written by Dilshan Ramesh

*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "Your SSID";
const char* password = "Your Password";

ESP8266WebServer server(80);

const int led = D1;
const int RedLED = 15;   //D8  GPIO15
const int GreenLED = 12; //D6  GPIO12
const int BlueLED = 13;  //D7  GPIO13

int R, G, B;

void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello RGB Controller");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";

    if (i == 0) {
      R = (server.arg(i).toInt());
    }
    else if (i == 1) {
      G = (server.arg(i).toInt());
    }
    else if (i == 2) {
      B = (server.arg(i).toInt());
    }
  }

  Serial.print(R);
  Serial.print(G);
  Serial.println(B);
  
  RGB_Set_Color(R, G, B);

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);

  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);

  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}

void RGB_Set_Color(int r, int g, int b) {
  analogWrite(RedLED, r);
  analogWrite(GreenLED, g);
  analogWrite(BlueLED, b);
}
