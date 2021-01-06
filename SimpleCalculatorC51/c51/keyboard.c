/*
 * 键盘模块
 * 使用按钮&矩阵键盘
 */
#include "../reg51.h"
#include "../type.h"
#include "../utils/io.h"

/*
 * 矩阵键盘输入信号
 * 从左上角到右下角
 */
const unsigned char matrixCodes[] = {
        0xee, 0xde, 0xbe, 0x7e,
        0xed, 0xdd, 0xbd, 0x7d,
        0xeb, 0xdb, 0xbb, 0x7b,
        0xe7, 0xd7, 0xb7, 0x77,
};

/*
 * 矩阵键盘&按钮输入内容
 * 从左上角到右下角
 */
const char keyboardChars[] = {
        '7', '8', '9', '+',
        '4', '5', '6', '-',
        '1', '2', '3', '*',
        '0', '0', '.', '/',
        '(', ')', 'C', '='
};

/*
 * 暂存行列数据
 */
uchar codeKeyboard;

/*
 * 循环变量
 */
int iKeyboard;

/*
 * 临时保存读取的字符
 */
char cKeyboard;

/*
 * 键盘模块 - 获取实时矩阵键盘字符
 * 无输入 - 返回'\0'
 */
char readMatrix() {
    //置初始值
    codeKeyboard = 0;

    //检测行值
    P1 = 0x0f;
    if (P1 != 0x0f) codeKeyboard = P1;
    else return '\0';

    //等待一小段时间后再次检测
    delay(50);

    //检测列值
    P1 = 0xf0;
    if (P1 != 0xf0) codeKeyboard = P1 | codeKeyboard;
    else return '\0';

    //等待松开按钮
    while (P1 != 0xf0);

    //寻找对应数值
    for (iKeyboard = 0; iKeyboard < 16; ++iKeyboard) {
        if (codeKeyboard == matrixCodes[iKeyboard]) {
            return keyboardChars[iKeyboard];
        }
    }

    //未检测到输入返回0
    return '\0';
}

/*
 * 键盘K3，接P30
 * 映射为(
 */
sbit K1 = P3 ^0;

/*
 * 键盘K3，接P31
 * 映射为)
 */
sbit K2 = P3 ^1;

/*
 * 键盘K3，接P32
 * 映射为初始化C
 */
sbit K3 = P3 ^2;

/*
 * 键盘K4，接P33
 * 映射为=
 */
sbit K4 = P3 ^3;

/*
 * 键盘模块 - 获取实时按钮输入字符
 * 无输入 - 返回'\0'
 */
char readButton() {

    //依次检测按钮
    if (K1 == 0) {
        //等待一小段时间后再次检测
        delay(50);
        if (K1 == 0) {
            //等待松开按钮
            while (K1 == 0);
            //设输入为按下的按钮
            return keyboardChars[16];
        }
    }
    if (K2 == 0) {
        //等待一小段时间后再次检测
        delay(50);
        if (K2 == 0) {
            //等待松开按钮
            while (K2 == 0);
            //设输入为按下的按钮
            return keyboardChars[17];
        }
    }
    if (K3 == 0) {
        //等待一小段时间后再次检测
        delay(50);
        if (K3 == 0) {
            //等待松开按钮
            while (K3 == 0);
            //设输入为按下的按钮
            return keyboardChars[18];
        }
    }
    if (K4 == 0) {
        //等待一小段时间后再次检测
        delay(50);
        if (K4 == 0) {
            //等待松开按钮
            while (K4 == 0);
            //设输入为按下的按钮
            return keyboardChars[19];
        }
    }

    return 0;
}

/*
 * 键盘模块 - 等待并获取按钮&矩阵键盘输入结果
 */
char readKeyboard() {
    while (true) {
        //初始化
        cKeyboard = 0;

        //依次从按钮和矩阵中尝试读取
        if ((cKeyboard = readButton())) return cKeyboard;
        if ((cKeyboard = readMatrix())) return cKeyboard;

        //延迟100ms获得下一个输入信号
        //delay(100);
    }
}