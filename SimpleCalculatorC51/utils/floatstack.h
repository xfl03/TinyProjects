/*
 * ������ջ
 */
#ifndef _FLOAT_STACK_H
#define _FLOAT_STACK_H

#include "../type.h"

/*
 * ������ջ - �ṹ���壨����ģ�⣩
 */
typedef struct FloatStackStruct0{
    /*
     * ջ����
     */
    float arr[20];
    /*
     * ջ��ָ�룬ָ��ջ���ĺ�һ��Ԫ��
     */
    char ptr;
} *FloatStack, FloatStackStruct;

/*
 * ������ջ - �½�ջ
 */
FloatStack createFloatStack();

/*
 * ������ջ - ��ջ
 */
void pushFloatStack(FloatStack stack, float item);

/*
 * ������ջ - ��ȡջ��Ԫ�ز���ջ
 */
float popFloatStack(FloatStack stack);

/*
 * ������ջ - ���ջ
 */
void clearFloatStack(FloatStack stack);

/*
 * ������ջ - �жϿ�ջ
 */
int isEmptyFloatStack(FloatStack stack);

#endif
