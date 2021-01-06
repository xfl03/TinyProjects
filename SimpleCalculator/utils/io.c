/*
 * IO控制（控制台实现）
 */
#include <stdio.h>
#include <stdlib.h>
#include "io.h"

/*
 * IO控制 - 读取字符（控制台实现）
 */
char readChar() {
    //暂存读取的字符
    char input;

    //从控制台读取字符，忽略空白字符
    while ((input = (char) getchar()) && (input == '\n' || input == '\r' || input == ' '));

    //返回读取的字符
    return (char) input;
}

/*
 * IO控制 - 写入字符（控制台实现）
 */
void writeChar(char c) {
    //向控制台写入字符
    putchar(c);
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
 * IO控制 - 清除屏幕内容（控制台实现）
 */
void clearScreen() {
    //换行
    putchar('\n');
}

/*
 * IO控制 - 初始化IO（控制台实现）
 */
void initIO() {
    //无需做任何操作
}

/*
 * IO控制 - 延时（控制台实现）
 */
void delay(int ms) {
    //无需做任何操作
}