#include <Arduino.h>
#include <Wire.h>

const int PIN_DIR = 17;
const int PIN_PWM = 18;
const int PWM_CH = 0;
const int PWM_FREQ = 20000;
const int PWM_RES = 8;

const uint8_t INA226_ADDR = 0x40;
const float SHUNT_RESISTOR = 0.1;
const float MAX_EXPECTED_CURRENT = 30.0;

const uint8_t REG_CONFIG = 0x00;
const uint8_t REG_SHUNT_VOLTAGE = 0x01;
const uint8_t REG_BUS_VOLTAGE = 0x02;
const uint8_t REG_POWER = 0x03;
const uint8_t REG_CURRENT = 0x04;
const uint8_t REG_CALIBRATION = 0x05;

enum MotorState {
  NORMAL,
  STALLED,
  IMPACT
};

const float STALL_CURRENT = 15.0;
const float STALL_TIME_MS = 250;
const float IMPACT_THRESHOLD = 20.0;
const float NORMAL_CURRENT = 8.0;

MotorState currentState = NORMAL;
unsigned long stallStartTime = 0;
float lastCurrent = 0.0;
unsigned long lastImpactTime = 0;
const unsigned long IMPACT_COOLDOWN = 500;

void setMotor(int speed) {
  bool dir = (speed >= 0);
  int duty = abs(speed);
  digitalWrite(PIN_DIR, dir ? HIGH : LOW);
  ledcWrite(PWM_CH, duty);
}

void brake() {
  ledcWrite(PWM_CH, 0);
}

void writeRegister(uint8_t reg, uint16_t value) {
  Wire.beginTransmission(INA226_ADDR);
  Wire.write(reg);
  Wire.write((value >> 8) & 0xFF);
  Wire.write(value & 0xFF);
  Wire.endTransmission();
}

uint16_t readRegister(uint8_t reg) {
  Wire.beginTransmission(INA226_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  
  Wire.requestFrom(INA226_ADDR, (uint8_t)2);
  uint16_t value = Wire.read() << 8;
  value |= Wire.read();
  return value;
}

void setupINA226() {
  writeRegister(REG_CONFIG, 0x4427);
  float currentLSB = MAX_EXPECTED_CURRENT / 32768.0;
  uint16_t calibration = (uint16_t)(0.00512 / (currentLSB * SHUNT_RESISTOR));
  writeRegister(REG_CALIBRATION, calibration);
  Serial.printf("INA226 initialized. Current LSB: %.6f A/bit\n", currentLSB);
}

float readCurrent() {
  int16_t raw = (int16_t)readRegister(REG_CURRENT);
  float currentLSB = MAX_EXPECTED_CURRENT / 32768.0;
  float current = abs(raw * currentLSB);
  return current;
}

float readVoltage() {
  uint16_t raw = readRegister(REG_BUS_VOLTAGE);
  return raw * 0.00125;
}

MotorState detectState(float current, int motorSpeed) {
  if (motorSpeed == 0) {
    stallStartTime = 0;
    return NORMAL;
  }
  
  float currentDelta = current - lastCurrent;
  if (currentDelta > 5.0 && current > IMPACT_THRESHOLD) {
    if (millis() - lastImpactTime > IMPACT_COOLDOWN) {
      lastImpactTime = millis();
      return IMPACT;
    }
  }
  
  if (current > STALL_CURRENT) {
    if (stallStartTime == 0) {
      stallStartTime = millis();
    } else if (millis() - stallStartTime > STALL_TIME_MS) {
      return STALLED;
    }
  } else {
    stallStartTime = 0;
  }
  
  return NORMAL;
}

int handleState(MotorState state, int requestedSpeed) {
  if (state != currentState) {
    const char* stateNames[] = {"NORMAL", "STALLED", "IMPACT"};
    Serial.printf("State: %s -> %s\n", 
                  stateNames[currentState], stateNames[state]);
    currentState = state;
  }
  
  int outputSpeed = requestedSpeed;
  
  switch(state) {
    case NORMAL:
      break;
    case STALLED:
      Serial.println("STALL DETECTED - Cutting power!");
      outputSpeed = 0;
      break;
    case IMPACT:
      Serial.println("IMPACT DETECTED!");
      break;
  }
  
  return outputSpeed;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(PIN_DIR, OUTPUT);
  ledcSetup(PWM_CH, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_PWM, PWM_CH);
  setMotor(0);
  delay(100);
  setupINA226();
  Serial.println("Battlebot Motor Online - INA226 System");
}

void loop() {
  int requestedSpeed = 200;
  float current = readCurrent();
  float voltage = readVoltage();
  MotorState state = detectState(current, requestedSpeed);
  int outputSpeed = handleState(state, requestedSpeed);
  setMotor(outputSpeed);
  lastCurrent = current;
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 200) {
    Serial.printf("Current: %.2fA | Voltage: %.2fV | Speed: %d | State: %d\n", 
                  current, voltage, outputSpeed, state);
    lastPrint = millis();
  }
  delay(10);
}