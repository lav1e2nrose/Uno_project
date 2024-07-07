/*
 * @Author: lav1e2nrose 3341944494@qq.com
 * @Date: 2024-07-06 11:47:18
 * @LastEditors: lav1e2nrose 3341944494@qq.com
 * @LastEditTime: 2024-07-07 10:23:31
 * @FilePath: \UnoFine\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Arduino.h>
#include "FastLED.h"
#include "defines.h"

CRGB leds[NUM_LEDS];

void WS2812b_setup();
void Led_Rainbow();
void music_setup();
void loop_dyht();

void setup()
{
  Serial.begin(9600);
  // 初始化编码器、按键、LED、音乐、传感器等
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  WS2812b_setup();
  music_setup();

  // 初始化其他传感器和设备
}

void loop()
{

  int lightLevel = analogRead(LDR_Pin); // 读取光强值

  if (lightLevel < 500)
  {
    Led_Rainbow(); // 灯光效果1
  }
  else
  {
    loop_dyht(); // 音乐1
  }
}

void WS2812b_setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

void Led_Rainbow()
{
  /* Raibow Effect */
  // 红色→橙色→黄色
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 7 * i + 31, 0);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 黄色→绿色
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(224 - 7 * i, 255, 0);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 绿色→青色→蓝色
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0, 224 - 7 * i, 7 * i + 31);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 蓝色→紫色
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(7 * i, 0, 255);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 紫色→红色
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 0, 224 - 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 深色，红色→绿色，顺时针
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255 - 7 * i, 7 * i, 0);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 深色，绿色→蓝色，顺时针
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0, 255 - 7 * i, 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 深色，蓝色→红色，顺时针
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(7 * i, 0, 255 - 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 浅色，红色→绿色，顺时针
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255 - 7 * i, 7 * i, 255);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 浅色，绿色→蓝色，顺时针
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 255 - 7 * i, 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 浅色，蓝色→红色，顺时针
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(7 * i, 255, 255 - 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 深色，红色→蓝色，逆时针
  for (int i = NUM_LEDS - 1; i >= 0; i--)
  {
    leds[i] = CRGB(255 - 7 * i, 0, 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 深色，蓝色→绿色，逆时针
  for (int i = NUM_LEDS - 1; i >= 0; i--)
  {
    leds[i] = CRGB(0, 7 * i, 255 - 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 深色，绿色→红色，逆时针
  for (int i = NUM_LEDS - 1; i >= 0; i--)
  {
    leds[i] = CRGB(7 * i, 255 - 7 * i, 0);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 浅色，红色→蓝色，逆时针
  for (int i = NUM_LEDS - 1; i >= 0; i--)
  {
    leds[i] = CRGB(255 - 7 * i, 255, 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 浅色，蓝色→绿色，逆时针
  for (int i = NUM_LEDS - 1; i >= 0; i--)
  {
    leds[i] = CRGB(255, 7 * i, 255 - 7 * i);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }

  // 浅色，绿色→红色，逆时针
  for (int i = NUM_LEDS - 1; i >= 0; i--)
  {
    leds[i] = CRGB(7 * i, 255 - 7 * i, 255);
    FastLED.setBrightness(20);
    FastLED.show();
    delay(50);
  }
}

void music_setup()
{
  int tonepin = 10;
  pinMode(tonepin, OUTPUT);
}

void loop_dyht()
{
  int tune[] =
      {
          NTC3,
          NTC2,
          NTC3,
          NTC6,
          NTC3,
          NTC2,
          NTC3,
          NTC7,
          NTC3,
          NTC2,
          NTC3,
          NTCH1,
          NTC7,
          NTC5,
          NTC3,
          NTC2,
          NTC3,
          NTC6,
          NTC3,
          NTC2,
          NTC3,
          NTC7,
          NTC5,
          NTC2,
          NTCL7,
          NTC3,
          NTC2,
          NTC3,
          NTC6,
          NTC3,
          NTC2,
          NTC3,
          NTC7,
          NTC3,
          NTC2,
          NTC3,
          NTCH1,
          NTC7,
          NTC5,
          NTC2,
          NTC3,
          NTCL6,
          NTC2,
          NTC3,
          NTCL6,
          NTCL5,
          NTCL6,
          NTC1,
          NTCL7,

          NTCL6,
          NTC1,
          NTC1,
          NTC2,
          NTC2,
          NTC3,
          NTC3,
          NTC5,
          NTC6,
          NTC5,
          NTC3,
          NTC2,
          NTCL6,
          NTC1,
          NTC1,
          NTC2,
          NTC2,
          NTC3,
          NTC3,
          NTCL6,
          NTCL5,
          NTCL6,
          NTC1,
          NTC1,
          NTC2,
          NTC2,
          NTC3,
          NTC3,
          NTC5,
          NTC6,
          NTC5,
          NTC3,
          NTC2,
          NTC2,
          NTC3,
          NTCL6,
          NTC2,
          NTC3,
          NTCL6,
          NTCL5,
          NTCL6,

          NTCL6,
          NTC1,
          NTC2,
          NTC1,
          NTCL6,
          NTCL6,
          NTC1,
          NTC2,
          NTC1,
          NTC3,
          NTC3,
          NTC5,
          NTC6,
          NTC6,
          NTC5,
          NTC3,
          NTC2,
          NTC1,
          NTC2,
          NTC3,
          NTCL6,
          NTC1,
          NTC2,
          NTC1,
          NTCL6,
          NTCL6,
          NTC1,
          NTC2,
          NTC1,
          NTC3,
          NTC2,
          NTC3,
          NTCL6,
          NTC2,
          NTC3,
          NTCL6,
          NTCL5,
          NTCL6,

          NTC3,
          NTC5,
          NTCH1,
          NTC7,
          NTC3,
          NTC3,
          NTC2,
          NTC1,
          NTC1,
          NTC2,
          NTC3,
          NTC3,
          NTC2,
          NTC1,
          NTC6,
          NTCH1,
          NTC7,
          NTC6,
          NTC5,
          NTC2,
          NTC3,
          NTC3,
          NTC5,
          NTCH1,
          NTC7,
          NTC3,
          NTC3,
          NTC2,
          NTC1,
          NTC1,
          NTC2,
          NTC3,
          NTC2,
          NTC3,
          NTCL6,
          NTC2,
          NTC3,
          NTCL6,
          NTCL5,
          NTCL6,
      };
  // 节拍
  int durt[] =
      {
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          500,
          500,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          500,
          500,
          1000,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          500,
          500,
          250,
          250,
          500,
          250,
          250,
          250,
          250,
          500,
          500,
          1000,

          250,
          250,
          250,
          250,
          250,
          250,
          250,
          125,
          125,
          750,
          250,
          1000,
          250,
          250,
          250,
          250,
          250,
          250,
          500,
          500,
          1500,
          250,
          250,
          250,
          250,
          250,
          250,
          250,
          125,
          125,
          750,
          250,
          1000,
          250,
          250,
          500,
          250,
          250,
          250,
          250,
          1500,

          250,
          250,
          750,
          250,
          500,
          250,
          250,
          750,
          250,
          500,
          250,
          250,
          500,
          250,
          250,
          250,
          250,
          500,
          500,
          1000,
          250,
          250,
          875,
          125,
          500,
          250,
          250,
          500,
          500,
          1000,
          250,
          250,
          500,
          250,
          250,
          250,
          250,
          1500,

          250,
          250,
          750,
          250,
          500,
          250,
          250,
          500,
          250,
          250,
          500,
          250,
          250,
          500,
          250,
          250,
          250,
          250,
          250,
          250,
          1500,
          250,
          250,
          750,
          250,
          500,
          250,
          250,
          500,
          250,
          250,
          1000,
          250,
          250,
          500,
          250,
          250,
          250,
          250,
          2000,

      };
  int length;
  int tonepin = 10;
  length = sizeof(tune) / sizeof(tune[0]);
  for (int x = 0; x < length; x++)
  {
    tone(tonepin, 4 * tune[x]);
    delay(durt[x]);
    noTone(tonepin);
  }
  delay(2000);
}
