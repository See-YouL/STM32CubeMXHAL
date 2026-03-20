#include "main.h"

typedef struct{
  unsigned char minute;
  unsigned char second;
  unsigned char ms100; // 百毫秒
}SW_TypeDef; // stop watch 秒表结构体

extern SW_TypeDef Clock;
extern unsigned char SW_Statue; // 秒表状态
extern unsigned char SW_Flag; // 秒表标志位, 1 : 打印时间
