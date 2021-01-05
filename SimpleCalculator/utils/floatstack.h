/*
 * 浮点数栈
 */
#ifndef _FLOAT_STACK_H
#define _FLOAT_STACK_H

#include "bool.h"

/*
 * 浮点数栈 - 结构定义（数组模拟）
 */
typedef struct {
    /*
     * 栈数据
     */
    float data[20];
    /*
     * 栈顶指针，指向栈顶的后一个元素
     */
    char ptr;
} *FloatStack, FloatStackStruct;

/*
 * 浮点数栈 - 新建栈
 */
FloatStack createFloatStack();

/*
 * 浮点数栈 - 入栈
 */
void pushFloatStack(FloatStack stack, float item);

/*
 * 浮点数栈 - 获取栈顶元素并出栈
 */
float popFloatStack(FloatStack stack);

/*
 * 浮点数栈 - 清空栈
 */
void clearFloatStack(FloatStack stack);

/*
 * 浮点数栈 - 判断空栈
 */
int isEmptyFloatStack(FloatStack stack);

#endif
