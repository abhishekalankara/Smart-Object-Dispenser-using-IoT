#include <WiFi.h>
#include <HTTPClient.h>
#include <ESP32Servo.h>
#include <ArduinoJson.h>

// -------------------------
// 1. WiFi + Firebase config
// -------------------------
const char* WIFI_SSID     = "abhi";      // your hotspot name (exact)
const char* WIFI_PASSWORD = "12345678";     // your hotspot password

// Your database root URL (no trailing /)
const char* FIREBASE_HOST =
  "https://smartvending-8f01d-default-rtdb.firebaseio.com";

// -------------------------
// 2. Hardware pin mapping
// -------------------------
const int SERVO_KOPIKO_PIN     = 13;
const int SERVO_MELODY_PIN     = 12;
const int SERVO_ALPENLIEBE_PIN = 14;

const int MOTOR_IN1_PIN   = 25;    // L298N IN1
const int MOTOR_IN2_PIN   = 26;    // L298N IN2
const int RELAY_PIN       = 33;    // Relay control pin

Servo servoKopiko;
Servo servoMelody;
Servo servoAlpenliebe;

// Track last status to avoid repeating
String lastStatus = "";

// -------------------------
// 3. Helper: WiFi connect
// -------------------------
void connectWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi connected!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ WiFi connection failed");
  }
}

// -------------------------
// 4. HTTP helper: GET
// -------------------------
String httpGet(const String& path) {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
    if (WiFi.status() != WL_CONNECTED) return "";
  }

  HTTPClient http;
  String url = String(FIREBASE_HOST) + path;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode != 200) {
    Serial.print("❌ GET failed, code: ");
    Serial.println(httpCode);
    http.end();
    return "";
  }

  String payload = http.getString();
  http.end();
  return payload;
}

// -------------------------
// 5. HTTP helper: PATCH
//    (for updating JSON fields)
// -------------------------
bool httpPatch(const String& path, const String& jsonBody) {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
    if (WiFi.status() != WL_CONNECTED) return false;
  }

  HTTPClient http;
  String url = String(FIREBASE_HOST) + path;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  int httpCode = http.PATCH(jsonBody);
  if (httpCode != 200) {
    Serial.print("❌ PATCH failed, code: ");
    Serial.println(httpCode);
    http.end();
    return false;
  }

  String payload = http.getString();
  Serial.print("PATCH response: ");
  Serial.println(payload);

  http.end();
  return true;
}

// -------------------------
// 6. Motor + Servo helpers
// -------------------------
void motorStop() {
  digitalWrite(MOTOR_IN1_PIN, LOW);
  digitalWrite(MOTOR_IN2_PIN, LOW);
}

void motorForward() {
  digitalWrite(MOTOR_IN1_PIN, HIGH);
  digitalWrite(MOTOR_IN2_PIN, LOW);
}

void dispenseServo(Servo& s) {
  // Simple 0 -> 90 -> 0 movement
  s.write(0);
  delay(300);
  s.write(90);
  delay(700);   // adjust for your mechanism
  s.write(0);
  delay(300);
}

// -------------------------
// 7. Main dispense function
// -------------------------
void dispenseProduct(const String& productName) {
  Serial.print("🚚 Dispensing: ");
  Serial.println(productName);

  // Turn ON relay (power to motor/servos if used that way)
  digitalWrite(RELAY_PIN, HIGH);
  delay(100); // small delay for relay

  // Run conveyor motor for a short time
  motorForward();

  // Choose which servo based on product name text
  if (productName.indexOf("Kopiko") != -1 || productName.indexOf("kopiko") != -1) {
    dispenseServo(servoKopiko);
  } else if (productName.indexOf("Melody") != -1 || productName.indexOf("melody") != -1) {
    dispenseServo(servoMelody);
  } else if (productName.indexOf("Alpenliebe") != -1 || productName.indexOf("alpenliebe") != -1) {
    dispenseServo(servoAlpenliebe);
  } else {
    // If multiple products in cart, or unknown name, just move all once
    dispenseServo(servoKopiko);
    dispenseServo(servoMelody);
    dispenseServo(servoAlpenliebe);
  }

  // Keep motor running briefly to push item out
  delay(1500);
  motorStop();

  // Turn OFF relay
  digitalWrite(RELAY_PIN, LOW);
}

// -------------------------
// 8. Check Firebase payment
// -------------------------
void checkPaymentAndDispense() {
  // 1) GET status
  String statusRaw = httpGet("/payments/latest/status.json");
  if (statusRaw == "") {
    Serial.println("⚠ Empty status response");
    return;
  }
  Serial.print("Raw status JSON: ");
  Serial.println(statusRaw);

  // statusRaw is something like: " \"Pending\" " or " \"Completed\" "
  // remove quotes:
  statusRaw.trim();
  if (statusRaw.startsWith("\"")) statusRaw.remove(0, 1);
  if (statusRaw.endsWith("\"")) statusRaw.remove(statusRaw.length() - 1, 1);
  String status = statusRaw;

  Serial.print("Current status: ");
  Serial.println(status);

  // If status didn't change, do nothing
  if (status == lastStatus) return;
  lastStatus = status;

  // Only act when it becomes "Completed"
  if (status == "Completed") {
    // 2) Read product name
    String productRaw = httpGet("/payments/latest/product.json");
    productRaw.trim();
    if (productRaw.startsWith("\"")) productRaw.remove(0, 1);
    if (productRaw.endsWith("\"")) productRaw.remove(productRaw.length() - 1, 1);
    String productName = productRaw;

    Serial.print("Product to dispense: ");
    Serial.println(productName);

    // 3) Dispense
    dispenseProduct(productName);

    // 4) Update status to "Dispensed"
    String body = "{\"status\":\"Dispensed\"}";
    httpPatch("/payments/latest.json", body);
    Serial.println("✅ Updated status to Dispensed");
  }
}

// -------------------------
// 9. Setup & Loop
// -------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  connectWiFi();

  // Attach servos
  servoKopiko.attach(SERVO_KOPIKO_PIN);
  servoMelody.attach(SERVO_MELODY_PIN);
  servoAlpenliebe.attach(SERVO_ALPENLIEBE_PIN);

  // Set initial positions
  servoKopiko.write(0);
  servoMelody.write(0);
  servoAlpenliebe.write(0);

  // Motor + relay pins
  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  motorStop();
  digitalWrite(RELAY_PIN, LOW);

  Serial.println("🚀 ESP32 Smart Vending firmware started (Kopiko / Melody / Alpenliebe)");
}

void loop() {
  checkPaymentAndDispense();
  delay(3000);  // check every 3 seconds
}
