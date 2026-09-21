// ============================================================
// MISTRA - HC-SR04 DIAGNOSTIC + SAFETY NODE
// ESP32-S3
// ============================================================
#define TRIG_PIN 18
#define ECHO_PIN 17
#define IR_PIN 16
#define LM35_PIN 15
#define GREEN_PIN 4
#define YELLOW_PIN 5
#define RED_PIN 6
#define PIEZO_PIN 7
// ------------------------------------------------------------
// HC-SR04 distance measurement
// ------------------------------------------------------------
float readDistance()
{
  // Make sure trigger starts LOW
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // 10 us trigger pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Measure HIGH duration of ECHO
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  // No echo received
  if (duration == 0)
  {
    return -1;
  }
  // Speed of sound:
  // distance = time * 0.0343 / 2
  float distance = (duration * 0.0343) / 2.0;
  return distance;
}
// ------------------------------------------------------------
// Set traffic light
// ------------------------------------------------------------
void setLight(bool green, bool yellow, bool red)
{
  digitalWrite(GREEN_PIN, green);
  digitalWrite(YELLOW_PIN, yellow);
  digitalWrite(RED_PIN, red);
}
// ------------------------------------------------------------
// Setup
// ------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(LM35_PIN, INPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(PIEZO_PIN, OUTPUT);
  setLight(false, false, false);
  digitalWrite(PIEZO_PIN, LOW);
  Serial.println();
  Serial.println("==========================================");
  Serial.println(" MISTRA - MINE VEHICLE SAFETY NODE");
  Serial.println(" ESP32-S3");
  Serial.println("==========================================");
  Serial.println("Reading sensors every 5 seconds...");
  Serial.println();
}
// ------------------------------------------------------------
// Main loop
// ------------------------------------------------------------
void loop()
{
  // ----------------------------------------------------------
  // Read HC-SR04
  // ----------------------------------------------------------
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  float distance;
  if (duration == 0)
  {
    distance = -1;
  }
  else
  {
    distance = (duration * 0.0343) / 2.0;
  }
  // ----------------------------------------------------------
  // Read IR
  // ----------------------------------------------------------
  int irState = digitalRead(IR_PIN);
  // ----------------------------------------------------------
  // Read LM35
  // ----------------------------------------------------------
  int adcValue = analogRead(LM35_PIN);
  float voltage = (adcValue / 4095.0) * 3.3;
  // LM35 = 10 mV / °C
  float temperature = voltage * 100.0;
  // ----------------------------------------------------------
  // Print complete reading
  // ----------------------------------------------------------
  Serial.println("------------------------------------------");
  Serial.print("RAW ECHO TIME   : ");
  Serial.print(duration);
  Serial.println(" us");
  Serial.print("HC-SR04 DISTANCE: ");
  if (distance < 0)
  {
    Serial.println("NO ECHO");
  }
  else
  {
    Serial.print(distance, 2);
    Serial.println(" cm");
  }
  Serial.print("IR PROXIMITY    : ");
  if (irState == HIGH)
    Serial.println("OBJECT DETECTED");
  else
    Serial.println("CLEAR");
  Serial.print("LM35 ADC        : ");
  Serial.println(adcValue);
  Serial.print("LM35 VOLTAGE    : ");
  Serial.print(voltage, 3);
  Serial.println(" V");
  Serial.print("TEMPERATURE     : ");
  Serial.print(temperature, 2);
  Serial.println(" C");
  // ----------------------------------------------------------
  // Safety decision
  // ----------------------------------------------------------
  if (distance < 0)
  {
    // No valid ultrasonic reading
    setLight(false, true, false);
    digitalWrite(PIEZO_PIN, LOW);
    Serial.println("STATUS          : SENSOR ERROR");
    Serial.println("LIGHT           : YELLOW");
  }
  else if (distance <= 5)
  {
    // CRITICAL
    setLight(false, false, true);
    digitalWrite(PIEZO_PIN, HIGH);
    Serial.println("STATUS          : CRITICAL STOP");
    Serial.println("LIGHT           : RED");
    Serial.println("PIEZO           : ON");
  }
  else if (distance <= 20)
  {
    // STOP
    setLight(false, false, true);
    digitalWrite(PIEZO_PIN, LOW);
    Serial.println("STATUS          : STOP");
    Serial.println("LIGHT           : RED");
    Serial.println("PIEZO           : OFF");
  }
  else if (distance <= 50)
  {
    // SLOW
    setLight(false, true, false);
    digitalWrite(PIEZO_PIN, LOW);
    Serial.println("STATUS          : SLOW");
    Serial.println("LIGHT           : YELLOW");
    Serial.println("PIEZO           : OFF");
  }
  else
  {
    // GO
    setLight(true, false, false);
    digitalWrite(PIEZO_PIN, LOW);
    Serial.println("STATUS          : GO");
    Serial.println("LIGHT           : GREEN");
    Serial.println("PIEZO           : OFF");
  }
  Serial.println("------------------------------------------");
  // Wait 5 seconds before next complete reading
  delay(5000);
}
