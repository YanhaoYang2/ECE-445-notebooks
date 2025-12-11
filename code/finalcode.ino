#include <Arduino.h>
#include <ESP32Servo.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

Servo myServo;

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;

const int PIN_AIN1 = 4;
const int PIN_AIN2 = 5;
const int PIN_BIN1 = 6;
const int PIN_BIN2 = 7;

bool btnUp = false;
bool btnDown = false;
bool btnLeft = false;
bool btnRight = false;

void runForward() {
  digitalWrite(PIN_AIN1, HIGH);
  digitalWrite(PIN_AIN2, LOW);
  digitalWrite(PIN_BIN1, HIGH);
  digitalWrite(PIN_BIN2, LOW);
}

void runBackward() {
  digitalWrite(PIN_AIN1, LOW);
  digitalWrite(PIN_AIN2, HIGH);
  digitalWrite(PIN_BIN1, LOW);
  digitalWrite(PIN_BIN2, HIGH);
}

void turnLeft() {
  digitalWrite(PIN_BIN1, HIGH);
  digitalWrite(PIN_BIN2, LOW);
  digitalWrite(PIN_AIN1, LOW);
  digitalWrite(PIN_AIN2, HIGH);
}

void turnRight() {
  digitalWrite(PIN_BIN1, LOW);
  digitalWrite(PIN_BIN2, HIGH);
  digitalWrite(PIN_AIN1, HIGH);
  digitalWrite(PIN_AIN2, LOW);
}

void brake() {
  digitalWrite(PIN_AIN1, LOW);
  digitalWrite(PIN_AIN2, LOW);
  digitalWrite(PIN_BIN1, LOW);
  digitalWrite(PIN_BIN2, LOW);
}

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer *pServer) {
    deviceConnected = true;
    Serial.println("Connected");
  }
  void onDisconnect(BLEServer *pServer) {
    deviceConnected = false;
    Serial.println("Disconnected");
    pServer->getAdvertising()->start();
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    String rxValue = pCharacteristic->getValue();
    
    // Bluefruit sends: !B + button + 1(press)/0(release)
    if (rxValue.length() >= 4 && rxValue[0] == '!' && rxValue[1] == 'B') {
      char button = rxValue[2];
      bool pressed = (rxValue[3] == '1');
      
      Serial.print("Button: ");
      Serial.print(button);
      Serial.println(pressed ? " PRESS" : " RELEASE");
      
      switch (button) {
        case '5':  // Up - Forward
          btnUp = pressed;
          break;
        case '6':  // Down - Backward
          btnDown = pressed;
          break;
        case '7':  // Left
          btnLeft = pressed;
          break;
        case '8':  // Right
          btnRight = pressed;
          break;
        case '3':  // Button 3 - Servo to 40
  if (pressed) {
    myServo.write(40);
    Serial.println("SERVO: 40 degrees CMD");
  }
  break;
case '4':  // Button 4 - Servo to 0  
  if (pressed) {
    myServo.write(0);
    Serial.println("SERVO: 0 degrees CMD");
  }
  break;
      }
    }
  }
};

void setup() {
  Serial.begin(115200);
  myServo.setPeriodHertz(50);           // 20ms servo standard
 myServo.attach(8, 500, 2400);
 myServo.write(40);     // Start at 40° (your button 3 position)
 delay(500);
 myServo.write(0)
  pinMode(PIN_AIN1, OUTPUT);
  pinMode(PIN_AIN2, OUTPUT);
  pinMode(PIN_BIN1, OUTPUT);
  pinMode(PIN_BIN2, OUTPUT);
  brake();

  BLEDevice::init("MyESP32");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pTxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_NOTIFY);
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR);
  pRxCharacteristic->setCallbacks(new MyCallbacks());

  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("BLE ready, waiting for connection...");
}

void loop() {
  if (btnUp) runForward();
  else if (btnDown) runBackward();
  else if (btnLeft) turnLeft();
  else if (btnRight) turnRight();
  else brake();
}
