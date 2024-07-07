#define BUTTON_1 6
#define BUTTON_2 7
#define BUTTON_PIN 6

#define DHTPIN 3
#define DHTTYPE DHT11

#define buzzerPin 10

#define LED_PIN 4
#define NUM_LEDS 5

// #define oldPosition = -999;

#define ENCODER_PIN_A 8
#define ENCODER_PIN_B 9
#define LDR_Pin  A1 // 光敏电阻连接的引脚

//音符
#define NTC0 -1
#define NTC1 262
#define NTC2 294
#define NTC3 330
#define NTC4 350
#define NTC5 393
#define NTC6 441
#define NTC7 495
#define NTCL5 196
#define NTCL6 221
#define NTCL7 248   
#define NTCH1 525

// 定义温度和湿度的报警阈值
#define TEMP_THRESHOLD  50  // 温度报警阈值，摄氏度
#define HUMID_THRESHOLD  80 // 湿度报警阈值，百分比

// 存储编码器的最小采样周期和按键的防抖时间
#define encoderSamplingPeriod 100 // 假设编码器的最小采样周期是100毫秒
#define buttonDebounceTime 10 // 假设按键的防抖时间是50毫秒