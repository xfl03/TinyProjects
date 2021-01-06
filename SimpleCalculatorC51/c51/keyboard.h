/*
 * 键盘模块
 * 使用按钮&矩阵键盘
 */
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "../reg51.h"

/*
 * 键盘模块 - 获取实时按钮输入字符
 * 无输入 - 返回'\0'
 */
char readButton();

/*
 * 键盘模块 - 获取实时矩阵键盘字符
 * 无输入 - 返回'\0'
 */
char readMatrix();

/*
 * 键盘模块 - 等待并获取按钮&矩阵键盘输入结果
 */
char readKeyboard();

#endif
