/*
 * ������ջ
 */
#include <stdlib.h>
#include "floatstack.h"

/*
 * ������ջ - �½�ջ
 */
FloatStack createFloatStack() {
    //ʹ��malloc�����ڴ�ռ�
    FloatStack stack = (FloatStack) malloc(sizeof(FloatStackStruct));
    //��ʼ��ջ��ָ��
    stack->ptr = 0;
    //����ջ
    return stack;
}

/*
 * ������ջ - ��ջ
 */
void pushFloatStack(FloatStack stack, float item) {
    //����ջ�����ݣ�����ջ��ָ��
    stack->arr[stack->ptr++] = item;
}

/*
 * ������ջ - ��ȡջ��Ԫ�ز���ջ
 */
float popFloatStack(FloatStack stack){
    //ջ��ָ��ǰ�ƣ�����ջ������
    return stack->arr[--stack->ptr];
}

/*
 * ������ջ - ���ջ
 */
void clearFloatStack(FloatStack stack) {
    //ջ��ָ���ó�ʼֵ
    stack->ptr = 0;
}

/*
 * ������ջ - �жϿ�ջ
 */
int isEmptyFloatStack(FloatStack stack) {
    //�ж�ջ��ָ���Ƿ�Ϊ��ʼֵ
    return stack->ptr == 0;
}