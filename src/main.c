#include "STC8G.h"
#include "config.h"

__code uint8_t ticks_us = (24000000UL / 4500 / 1000);

void DelayUs(uint16_t t)
{
    uint8_t i;
    do {
        i = ticks_us;
        while (--i)
            ;
    } while (--t);
}

void SendHigh(void)
{
    P54 = 1;
    P55 = 1;
    DelayUs(1200);
    P54 = 0;
    P55 = 0;
    DelayUs(400);
}

void SendLow(void)
{
    P54 = 1;
    P55 = 1;
    DelayUs(400);
    P54 = 0;
    P55 = 0;
    DelayUs(1200);
}

void SendSync(void)
{
    P54 = 1;
    P55 = 1;
    DelayUs(400);
    P54 = 0;
    P55 = 0;
    DelayUs(400 * 31);
}

void SendDataBit(unsigned char bit)
{
    if (bit) {
        SendHigh(); // 发送数据位 1
    } else {
        SendLow(); // 发送数据位 0
    }
}

uint32_t reverseBits(uint32_t number)
{
    uint32_t reversed = 0;
    int bit           = 0;
    int numBits       = sizeof(number) * 6 - 1; // 计算位数

    // 循环遍历每一位
    for (int i = numBits; i >= 0; --i) {
        // 将当前位移动到最低位
        reversed |= ((number >> i) & 1) << bit++;
    }

    return reversed;
}

void SendEV1527Num(uint32_t num)
{
    uint8_t i;
    uint32_t result = 24, temp;
    temp            = reverseBits(num);
    SendSync(); // 发送同步起始信号
    while (result) {
        i = temp % 2;
        SendDataBit(i);
        temp = temp / 2;
        result--;
    }
}

void main(void)
{
    P5M0 |= 0x30;
    P5M1 &= ~0x30;
    P5DR &= ~0x30;

    P54 = 0;
    P55 = 0;

    P3M0 = 0x00;
    P3M1 = 0x00;
    P3PU |= 0x09;

    P30 = 1;
    P33 = 1;

    while (1) {
        if (P30 == 0) {
            if (P33 == 0) {
                SendEV1527Num(0x350049); // 发送 EV1527 数据
            } else {
                SendEV1527Num(0x350019); // 发送 EV1527 数据
            }
        } else if (P33 == 0) {
            SendEV1527Num(0x350029); // 发送 EV1527 数据
        }
    }
}
