#ifndef __BEEP_H
#define __BEEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"    // 包含主头文件

#define BEEP_TIM_CLOCK 12000000U // 定时器时钟频率 12MHz

// 定义低音音名C
#define CL1 262
#define CL2 294
#define CL3 330
#define CL4 349
#define CL5 392
#define CL6 440
#define CL7 494

// 定义中音音名C
#define CM1 523
#define CM2 587
#define CM3 659
#define CM4 698
#define CM5 784
#define CM6 880
#define CM7 988

// 定义高音音名C
#define CH1 1047
#define CH2 1175
#define CH3 1319
#define CH4 1397
#define CH5 1568
#define CH6 1760
#define CH7 1976

//定义低音音名D
#define DL1 294
#define DL2 330
#define DL3 370
#define DL4 392
#define DL5 440
#define DL6 494
#define DL7 554

//定义中音音名D
#define DM1 587
#define DM2 659
#define DM3 740
#define DM4 784
#define DM5 880
#define DM6 988
#define DM7 1109

//定义高音音名D
#define DH1 1175
#define DH2 1319
#define DH3 1480
#define DH4 1568
#define DH5 1760
#define DH6 1976
#define DH7 2217

//定义低音音名E
#define EL1 330
#define EL2 370
#define EL3 415
#define EL4 440
#define EL5 494
#define EL6 554
#define EL65 587
#define EL7 622

//定义中音音名E
#define EM1 659
#define EM2 740
#define EM3 831
#define EM4 880
#define EM5 988
#define EM6 1109
#define EM7 1245

//定义高音音名E
#define EH1 1319
#define EH2 1480
#define EH3 1661
#define EH4 1760
#define EH5 1976

//定义低音音名F
#define FL1 349
#define FL2 392
#define FL3 440
#define FL4 466
#define FL5 523
#define FL6 587
#define FL7 659

//定义中音音名F
#define FM1 698
#define FM2 784
#define FM3 880
#define FM4 932
#define FM5 1047
#define FM6 1175
#define FM7 1319

//定义高音音名F
#define FH1 1397
#define FH2 1568
#define FH3 1760
#define FH4 1865

// 定义时值单位, 每拍音符持续多少 ms
#define S1 240
#define S2 360
#define S3 600
#define S4 800
#define S5 1000 
#define S6 1200 
#define S7 1600 
#define S8 2000 
#define S9 2400 
#define S10 2800 


typedef struct 
{
    short tone; // 音名
    short time; // 时间
}Note_TypeDef; // 音符结构体，包含音名和时间

extern const Note_TypeDef TwoTigersNote[]; // 《两只老虎》乐谱数组，包含音符频率和时值
extern const Note_TypeDef PeppaPigNote[]; // 《小猪佩奇》乐谱数组，包含音符频率和时值

void BeepPlay(unsigned short tone, unsigned char volumeLevel); // 播放音符函数，参数为音符频率和音量等级
void MusicPlay(unsigned char volume_level, Note_TypeDef * Music); // 播放乐谱函数，参数为音量等级和乐谱数组

#ifdef __cplusplus
}
#endif

#endif /* __BEEP_H */
