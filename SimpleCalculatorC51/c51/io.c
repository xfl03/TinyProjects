/*
 * IO控制（C51实现）
 */
#include <stdio.h>
#include <stdlib.h>
#include "../utils/io.h"
#include "lcd1602.h"
#include "keyboard.h"

/*
 * IO控制 - 读取字符（C51实现）
 */
char readChar() {
    //从矩阵&键盘输入
    return readKeyboard();
}

int posLCD = 0;

/*
 * IO控制 - 写入字符（C51实现）
 */
void writeChar(char c) {
    //移动光标并输入内容
    setPosLCD(posLCD++);
    writeDataLCD(c);

    //自动光标换行
    if(posLCD==16) setPosLCD(16);
}

/*
 * IO控制 - 写入字符串
 */
void writeString(string str) {
    //逐字符写入字符串
    while (*str) writeChar(*(str++));
}

/*
 * IO控制 - 写入浮点数
 */
void writeFloat(float num) {
    //将浮点数转换为字符串
    char *output = (char *) malloc(20 * sizeof(char));
    sprintf(output, "%g", num);

    //输出字符串
    writeString(output);
}


/*
 * IO控制 - 清除屏幕内容（C51实现）
 */
void clearScreen() {
    //还原光标
    posLCD = 0;
    //清屏
    writeCommandLCD(0x01);
}

/*
 * 内存池，用于动态分配内存
 */
unsigned char mempool[256];

/*
 * IO控制 - 初始化IO（C51实现）
 */
void initIO() {
    //初始化内存池
    init_mempool(&mempool, sizeof(mempool));
    //初始化LCD
    initLCD();
}

/*
 * IO控制 - 延时（C51实现）
 */
void delay(int ms) {
    uchar a, b;
    for (; ms > 0; ms--) {
        for (b = 199; b > 0; b--) {
            for (a = 1; a > 0; a--);
        }
    }
}