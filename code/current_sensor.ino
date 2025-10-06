// ESP32-WROOM-32 + INA226 test using Rob Tillaart's library
// Works on Arduino-ESP32 & PlatformIO
// Adjust SHUNT_OHM and MAX_CURRENT_A to your setup

#include <Wire.h>
#include <INA226.h>

// ---------- USER SETTINGS ----------
const uint8_t INA_ADDR     = 0x40;     // change if A0/A1 not both grounded
const float   SHUNT_OHM    = 0.005f;   // e.g. 5 milliohms
const float   MAX_CURRENT_A = 10.0f;   // expected peak current
const bool    NORMALIZE_LSB = true;    // improves accuracy, see README

// I2C pins (ESP32 defaults)
const int SDA_PIN = 21;
const int SCL_PIN = 22;
// -----------------------------------

INA226 ina(INA_ADDR);

void die(const char* msg) {
  Serial.println(msg);
  while (true) delay(1000);  // hang here if something's broken
}

void setup()
{
  Serial.begin(115200);
  delay(100);
  
  // ESP32 requires explicit Wire init (changed in lib v0.5.0+)
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);  // 400 kHz fast mode
  
  if (!ina.begin()) die("INA226 not found - check wiring and address");
  
  // Configure conversion times and averaging
  // Longer times help smooth out noisy PWM loads
  ina.setBusVoltageConversionTime(INA226_1100_us);
  ina.setShuntVoltageConversionTime(INA226_1100_us);
  ina.setAverage(INA226_16_SAMPLES);
  
  // Measure both shunt and bus continuously
  ina.setModeShuntBusContinuous();
  
  // Calibrate using your shunt resistor and max expected current
  int err = ina.setMaxCurrentShunt(MAX_CURRENT_A, SHUNT_OHM, NORMALIZE_LSB);
  if (err != INA226_ERR_NONE) {
    Serial.print("Calibration error 0x"); Serial.println(err, HEX);
    if (err == 0x8000) Serial.println("Hint: Imax * Rshunt exceeds 81.9 mV");
    die("Fix calibration settings");
  }
  
  // Show some info
  Serial.print("Current LSB = "); Serial.print(ina.getCurrentLSB(), 9); Serial.println(" A/bit");
  Serial.print("Manufacturer ID = 0x"); Serial.println(ina.getManufacturerID(), HEX);
  Serial.print("Die ID          = 0x"); Serial.println(ina.getDieID(), HEX);
  Serial.println("\nReady. Reading every 500 ms...\n");
}

void loop()
{
  // Wait for conversion to finish
  if (!ina.waitConversionReady(600)) {
    Serial.println("Timeout waiting for conversion");
    delay(200);
    return;
  }
  
  // Read measurements
  const float vbus   = ina.getBusVoltage();        // volts
  const float vshunt = ina.getShuntVoltage();      // volts across shunt
  const float current= ina.getCurrent();           // amps
  const float power  = ina.getPower();             // watts
  
  // Display results
  Serial.print("Bus: ");   Serial.print(vbus,   3); Serial.print(" V   ");
  Serial.print("Shunt: "); Serial.print(vshunt*1e3,2); Serial.print(" mV   ");
  Serial.print("I: ");     Serial.print(current,3); Serial.print(" A   ");
  Serial.print("P: ");     Serial.print(power,  3); Serial.println(" W");
  
  // Optional: check for overflow
  // uint16_t flags = ina.getAlertFlag();
  // if (flags & INA226_MATH_OVERFLOW_FLAG) Serial.println("Math overflow!");
  
  delay(500);
}