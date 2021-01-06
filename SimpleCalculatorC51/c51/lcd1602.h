/*
 * LCD模块
 * 使用LCD1602
 */
#ifndef _LCD1602_H
#define _LCD1602_H

#include "../type.h"

/*
 * LCD模块 - 写入指令或数据
 */
void writeLCD(bool isData, uchar dat);

/*
 * LCD模块 - 写入指令
 */
void writeCommandLCD(uchar command);

/*
 * LCD模块 - 写入数据
 */
void writeDataLCD(uchar dat);

/*
 * LCD模块 - 设置光标位置
 */
void setPosLCD(int pos);

/*
 * LCD模块 - 初始化
 */
void initLCD();

#endif
