/*
 * IO控制
 */
#ifndef _IO_H
#define _IO_H

/*
 * IO控制 - 读取字符
 */
char readChar();

/*
 * IO控制 - 写入字符
 */
void writeChar(char c);

/*
 * IO控制 - 写入字符串
 */
void writeString(char *str);

/*
 * IO控制 - 写入浮点数
 */
void writeFloat(float num);

/*
 * IO控制 - 清除屏幕内容
 */
void clearScreen();

/*
 * IO控制 - 初始化IO
 */
void initIO();

#endif
