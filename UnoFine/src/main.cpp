/*
 * @Author: lav1e2nrose 3341944494@qq.com
 * @Date: 2024-07-06 11:47:18
 * @LastEditors: lav1e2nrose 3341944494@qq.com
 * @LastEditTime: 2024-07-07 10:20:52
 * @FilePath: \UnoFine\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Arduino.h>
#include "FastLED.h"
#include "defines.h"
#include "Button2.h"
#include "DHT.h"
#include <Encoder.h>

void WS2812b_setup();
void Led_Sequence();
void Led_Colorful_Sequence();
void Led_Rainbow();
void beep();
void alarm();

DHT dht;
bool lastButtonState = false; // 上一次的按键状态

Encoder myEncoder(ENCODER_PIN_A, ENCODER_PIN_B);
long oldPosition = 0;
int gear = 0;

// 存储编码器的上次位置和按键的上一个状态
bool lastButtonStateButton1 = HIGH; // 第一个按钮的状态
bool lastButtonStateButton2 = HIGH; // 第二个按钮的状态

// 设备状态标志
bool deviceOn = false;

// 存储上次读取编码器和按键的时间
unsigned long lastEncoderRead = 0;
unsigned long lastButtonRead = 0;

void setup()
{
  Serial.begin(9600);
  // 初始化编码器、按键、LED、音乐、传感器等
  myEncoder.write(0);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);

  WS2812b_setup();
  // music_setup();
  pinMode(DHTPIN, INPUT);
  dht.setup(3);

  // 初始化其他传感器和设备
}

void loop()
{

  unsigned long now = millis();
  // 读取温度和湿度
  float temperature = dht.getTemperature();
  float humidity = dht.getHumidity();

  if (temperature >= TEMP_THRESHOLD || humidity >= HUMID_THRESHOLD)
  {
    alarm();
  }
  else
  {

    if (now - lastButtonRead >= buttonDebounceTime)
    {
      bool currentButtonState = digitalRead(BUTTON_1) == LOW || digitalRead(BUTTON_2) == LOW;

      if (currentButtonState && !lastButtonState)
      {

        deviceOn = !deviceOn; // 切换设备状态
        if (deviceOn)
        {
        }
        else
        {
          FastLED.clear();
          FastLED.show();
          noTone(buzzerPin);
        }
      }

      lastButtonState = currentButtonState; // 更新上一次的按键状态
      lastButtonRead = now;                 // 更新上次读取按键的时间
    }

    if (deviceOn && now - lastEncoderRead >= encoderSamplingPeriod)
    {
      long newPosition = myEncoder.read();

      // 检查编码器是否旋转了30度
      if (newPosition - oldPosition >= 5)
      {
        Serial.println(newPosition);
        // 更新挡位
        gear = (gear + 1) % 3;                // 有3个挡位，所以使用模3运算

        switch (gear)
        {
        case 0:
          Led_Sequence(); // 灯光效果1
          break;
        case 1:

          Led_Rainbow(); // 灯光效果2

          break;
        case 2:

          Led_Colorful_Sequence(); // 灯光效果3

          break;
        }
        // 更新编码器位置
        oldPosition = newPosition;
      }
      lastEncoderRead = now;
    }
  }
}

void beep()
{
  for (int i = 0; i < 3; i++)
  {
    tone(buzzerPin, 1760, 200);
    delay(200 + 133);
  }
}

// 报警函数
void alarm()
{
  // 报警操作，例如打开报警灯或播放报警音乐
  // 这里可以添加报警相关的代码
  for (int i = 0; i < 10; i++)
  {
    beep();
    FastLED.setBrightness(255);
    FastLED.showColor(CRGB::Red);
    delay(200);
    FastLED.clear();
    FastLED.show();
    delay(200);
  }
  // 报警后可以选择关闭设备或等待用户干预
  deviceOn = false;
  FastLED.clear();
  noTone(buzzerPin);
}

CRGB leds[NUM_LEDS];

void WS2812b_setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

void Led_Sequence()
{
  // Red
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(255, 0, 0);
    FastLED.show();
    delay(40);
  }

  // Green
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0, 255, 0);
    FastLED.show();
    delay(40);
  }

  // Blue
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0, 0, 255);
    FastLED.show();
    delay(40);
  }
  delay(1000); // 每秒检查一次光强
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

void Led_Colorful_Sequence()
{
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
