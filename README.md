# STCEV1527Transmitter

基于 STC8 系列的 315/433Mhz+EV1527 发送模块。

VSCode + EIDE + SDCC

使用内部晶振，频率 24Mhz。

```
T = 400us
1 = HIGH * 3T + LOW * T
0 = HIGH * T + LOW * 3T
Sync = HIGH * T + LOW * 31T
```
