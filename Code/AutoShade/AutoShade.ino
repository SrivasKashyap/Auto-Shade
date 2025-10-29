// Please fill in the dashes before uploading the code

#define BLYNK_TEMPLATE_ID "-----" // Blynk Template ID
#define BLYNK_TEMPLATE_NAME "-----"// Blynk Template Name
#define BLYNK_AUTH_TOKEN "-----" // Blynk Auth Token

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// ---- Wi-Fi ----
char ssid[] = "-----";  // Wifi ID
char pass[] = "-----"; // Wifi Password

// ---- Motor Pins ----
// Motor A → Window (Automatic + Manual)
#define ENA 25
#define IN1 26
#define IN2 27

// Motor B → Curtains (Manual only)
#define ENB 13
#define IN3 14
#define IN4 12

// ---- Sensors ----
#define MQ2_PIN 34
#define RAIN_PIN 35

// ---- Blynk Virtual Pins ----
#define VPIN_WINDOW_OPEN   V0
#define VPIN_WINDOW_CLOSE  V1
#define VPIN_CURTAIN_OPEN  V2
#define VPIN_CURTAIN_CLOSE V3
#define VPIN_MQ2_VALUE     V4
#define VPIN_RAIN_VALUE    V5

// ---- Thresholds ----
int MQ2_THRESHOLD = 1500;   // Above → gas detected
int RAIN_THRESHOLD = 2000;  // Below → rain detected

// ---- Motor Speeds (0–255) ----
int windowSpeed = 120;
int curtainSpeed = 100;

// ---- State Variables ----
bool manualWindowOpen = false;
bool manualWindowClose = false;
bool curtainOpen = false;
bool curtainClose = false;

// ---- Function Declarations ----
void windowOpen();
void windowClose();
void stopWindow();
void curtainOpenFunc();
void curtainCloseFunc();
void stopCurtain();

BLYNK_WRITE(VPIN_WINDOW_OPEN) {
  manualWindowOpen = param.asInt();
  if (manualWindowOpen) {
    Serial.println("🪟 Window: OPEN command received from app.");
    windowOpen();
  } else {
    Serial.println("🪟 Window: STOP command (open released).");
    stopWindow();
  }
}

BLYNK_WRITE(VPIN_WINDOW_CLOSE) {
  manualWindowClose = param.asInt();
  if (manualWindowClose) {
    Serial.println("🪟 Window: CLOSE command received from app.");
    windowClose();
  } else {
    Serial.println("🪟 Window: STOP command (close released).");
    stopWindow();
  }
}

BLYNK_WRITE(VPIN_CURTAIN_OPEN) {
  curtainOpen = param.asInt();
  if (curtainOpen) {
    Serial.println("🧵 Curtain: OPEN command received from app.");
    curtainOpenFunc();
  } else {
    Serial.println("🧵 Curtain: STOP command (open released).");
    stopCurtain();
  }
}

BLYNK_WRITE(VPIN_CURTAIN_CLOSE) {
  curtainClose = param.asInt();
  if (curtainClose) {
    Serial.println("🧵 Curtain: CLOSE command received from app.");
    curtainCloseFunc();
  } else {
    Serial.println("🧵 Curtain: STOP command (close released).");
    stopCurtain();
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(MQ2_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.println("✅ Connected to Blynk Cloud!");
  Serial.println("------------------------------------");
  Serial.println("SmartWindow system initialized.");
  Serial.println("Waiting for sensor data...");
  Serial.println("------------------------------------");
}

void loop() {
  Blynk.run();

  int mq2 = analogRead(MQ2_PIN);
  int rain = analogRead(RAIN_PIN);

  // ---- Send sensor data to Blynk ----
  Blynk.virtualWrite(VPIN_MQ2_VALUE, mq2);
  Blynk.virtualWrite(VPIN_RAIN_VALUE, rain);

  // ---- Serial feedback ----
  Serial.print("🌫 MQ2: ");
  Serial.print(mq2);
  Serial.print("\t🌧 Rain: ");
  Serial.println(rain);

  // ---- Status messages for thresholds ----
  if (mq2 > MQ2_THRESHOLD) {
    Serial.println("⚠️  Gas detected! (above threshold)");
  }

  if (rain < RAIN_THRESHOLD) {
    Serial.println("⚠️  Rain detected! (below threshold)");
  }

  delay(1000); // update every second
}

// ---- Window Motor (Motor A) ----
void windowOpen() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, windowSpeed);
  Serial.println("🪟 Window motor running: OPENING...");
}

void windowClose() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, windowSpeed);
  Serial.println("🪟 Window motor running: CLOSING...");
}

void stopWindow() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  Serial.println("🪟 Window motor STOPPED.");
}

// ---- Curtain Motor (Motor B) ----
void curtainOpenFunc() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, curtainSpeed);
  Serial.println("🧵 Curtain motor running: OPENING...");
}

void curtainCloseFunc() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, curtainSpeed);
  Serial.println("🧵 Curtain motor running: CLOSING...");
}

void stopCurtain() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  Serial.println("🧵 Curtain motor STOPPED.");
}
