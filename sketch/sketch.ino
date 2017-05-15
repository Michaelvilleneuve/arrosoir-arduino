#include <ESP8266WiFi.h>
const char* ssid     = "XXX";
const char* password = "XXX";
const char* host = "XXX";
const int sleepTimeS = 10;

const int hygrometer = A0;
int value;

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

void loop() {

  value = analogRead(hygrometer);
  value = constrain(value,400,1023);
  value = map(value,400,1023,100,0);

  Serial.println("Soil humidity: ");
  Serial.print(value);
  Serial.println("");
  
  WiFiClient client;
  const int httpPort = 80;
  if (client.connect(host, httpPort)) {
    String content = "Hey, just testing a post request.";
    Serial.println("Sending");
    client.println("POST /p0tt1sp0 HTTP/1.1");
    client.println("Host: 192.168.1.19:4321");
    client.println("Accept: */*");
    client.println("Content-Length: " + content.length());
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println();
    client.println(content);
  }

  delay(30000);

}
