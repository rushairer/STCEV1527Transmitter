#ifndef __CONFIG_H_
#define __CONFIG_H_
#include <stdint.h>

#define RF_PIN   P54
#define BTN_PIN  P55

#define ACTION_1 0x19
#define ACTION_2 0x29
#define ACTION_3 0x49

uint8_t HTime        = 0; // 高电平时间
uint8_t LTime        = 0; // 低电平时间
uint8_t HData        = 0; // 辅助数据交换
uint8_t LData        = 0; // 辅助数据交换
uint8_t RFCount      = 0; // 接收位数
uint8_t SyncCodeFlag = 0; // 同步码标志
uint8_t IsRFSuccess  = 0; // 接收完成标志

uint32_t EV1527Code;
uint32_t EV1527Value, EV1527Value1, EV1527Value2;
uint32_t TempValue;
uint8_t Synced = 1;

uint8_t RF433AddressHigh    = 0;
uint8_t RF433AddressLow     = 0;
uint8_t RF433AddressCommand = 0;
uint16_t RF433Address       = 65535;

#endif // !__CONFIG_H_