#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int ldrPin = 25;
const int relayPin = 5;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 33, 32, 15};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool isAutoMode = true;
bool manualLightOn = false;

void setup() {
  Serial.begin(115200);
  pinMode(ldrPin, INPUT);
  pinMode(relayPin, OUTPUT);

  keypad.setDebounceTime(50);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (true);
  }
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == 'A') {
      isAutoMode = true;
      Serial.println("Switched to AUTO mode");
    } else if (key == 'B') {
      isAutoMode = false;
      Serial.println("Switched to MANUAL mode");
    } else if (!isAutoMode && key == '1') {
      manualLightOn = true;
      Serial.println("Manual: Light ON");
    } else if (!isAutoMode && key == '0') {
      manualLightOn = false;
      Serial.println("Manual: Light OFF");
    }
  }

  int ldrState = digitalRead(ldrPin);
  String lightStatus;

  if (isAutoMode) {
    if (ldrState == 1) {
      digitalWrite(relayPin, LOW);
      lightStatus = "ON";
    } else {
      digitalWrite(relayPin, HIGH);
      lightStatus = "OFF";
    }
  } else {
    if (manualLightOn) {
      digitalWrite(relayPin, LOW);
      lightStatus = "ON";
    } else {
      digitalWrite(relayPin, HIGH);
      lightStatus = "OFF";
    }
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("Mode: ");
  display.println(isAutoMode ? "AUTO" : "MANUAL");

  display.setCursor(0, 20);
  display.print("Light: ");
  display.println(lightStatus);

  display.setCursor(0, 40);
  display.print("LDR Value: ");
  display.println(ldrState);

  display.display();

  delay(100);
}