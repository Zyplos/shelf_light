#include <FastLED.h>

#define NUM_LEDS 60

#define LED_DATA_PIN 7
#define SOUND_PIN A2
// #define LIGHT_SENSOR_PIN A6
#define MOTION_SENSOR_PIN 2

#define SOUND_ABOVE_THRESHOLD 900
#define LIGHT_BELOW_THRESHOLD 100

#define BRIGHTNESS_DEFAULT 10
// #define BRIGHTNESS_NIGHT 10

int CURRENT_BRIGHTNESS = BRIGHTNESS_DEFAULT;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  pinMode(SOUND_PIN, INPUT);
  // pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);

  // Serial.begin(57600);
  // do NOT set this to RGB or all the colors will be wrong
  FastLED.addLeds<WS2812, LED_DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(CURRENT_BRIGHTNESS);
  FastLED.setTemperature(Candle);
}

CRGB redColor = CRGB::Red;
CRGB warmLight = CRGB(255, 251, 219);

int soundLevel;
int isSoundLoud;
// int lightLevel;
// int isNightTime;
bool isMotionDetected;

void loop() {
  isMotionDetected = digitalRead(MOTION_SENSOR_PIN);
  soundLevel = analogRead(SOUND_PIN);
  isSoundLoud = soundLevel > SOUND_ABOVE_THRESHOLD;
  // isNightTime = analogRead(LIGHT_SENSOR_PIN) < LIGHT_BELOW_THRESHOLD;

  // Serial.println("====================================");
  // Serial.print("Sound level: ");
  // Serial.println(soundLevel);
  // Serial.print("Light level: ");
  // Serial.println(lightLevel);
  // Serial.print("Is sound loud: ");
  // Serial.println(isSoundLoud);
  // Serial.print("Is night time: ");
  // Serial.println(isNightTime);
  // Serial.print("Is motion detected: ");
  // Serial.println(isMotionDetected);

  // if (isNightTime) {
  //   FastLED.setBrightness(BRIGHTNESS_NIGHT);
  // } else {
  //   FastLED.setBrightness(BRIGHTNESS_DEFAULT);
  // }

  // get final computed brightness value based on conditions
  int brightness;
  if (isMotionDetected) {
    brightness = isSoundLoud ? 255 : BRIGHTNESS_DEFAULT;
  } else {
    brightness = 0;
  }
  // Serial.print("Targeting brightness: ");
  Serial.println(brightness);
  CRGB color = isSoundLoud ? redColor : warmLight;
  fill_solid(leds, NUM_LEDS, color);

  // gradually change brightness this way instead of using a for loop
  // to prevent flashing and weird behavior
  if (CURRENT_BRIGHTNESS < brightness) {
    CURRENT_BRIGHTNESS += 1;
  }

  if (CURRENT_BRIGHTNESS > brightness) {
    CURRENT_BRIGHTNESS -= 1;
  }
  FastLED.setBrightness(CURRENT_BRIGHTNESS);

  FastLED.show();
  delay(50);

  // Serial.println("====================================");
}