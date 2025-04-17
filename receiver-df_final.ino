#include <ESP8266WiFi.h>
#include <espnow.h>

#define led1 4  // light
#define led2 5  // oscilloscope
#define led3 0  // solder
#define led4 2  // power

// Structure to declare variable
typedef struct myStruct {
    int a;
    int b;
    int c;
    int d;
} myStruct;

// Create a myStruct called structObj
myStruct structObj;

// Callback function 
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&structObj, incomingData, sizeof(structObj));
 // Serial.print("Bytes received: ");
 // Serial.println(len);
 // Serial.print("D1 button state: ");
 // Serial.println(structObj.a);
 // Serial.print("D3 button state: ");
 // Serial.println(structObj.b);
  // Serial.println();

  digitalWrite(led1, (structObj.a == 100) ? HIGH : LOW);
  digitalWrite(led1, (structObj.a == 200) ? LOW : HIGH);
  
  digitalWrite(led2, (structObj.b == 100) ? HIGH : LOW);
  digitalWrite(led2, (structObj.b == 200) ? LOW : HIGH);

  digitalWrite(led3, (structObj.c == 100) ? HIGH : LOW);
  digitalWrite(led3, (structObj.c == 200) ? LOW : HIGH);
  
  digitalWrite(led4, (structObj.d == 100) ? HIGH : LOW);
  digitalWrite(led4, (structObj.d == 200) ? LOW : HIGH);
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE); //set role
  esp_now_register_recv_cb(OnDataRecv); // set callback
}

void loop() {
  
}
