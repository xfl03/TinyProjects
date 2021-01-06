/*
 * 浮点数栈
 */
#include <stdlib.h>
#include "floatstack.h"

/*
 * 浮点数栈 - 新建栈
 */
FloatStack createFloatStack() {
    //使用malloc分配内存空间
    FloatStack stack = (FloatStack) malloc(sizeof(FloatStackStruct));
    //初始化栈顶指针
    stack->ptr = 0;
    //返回栈
    return stack;
}

/*
 * 浮点数栈 - 入栈
 */
void pushFloatStack(FloatStack stack, float item) {
    //置入栈顶数据，后移栈顶指针
    stack->arr[stack->ptr++] = item;
}

/*
 * 浮点数栈 - 获取栈顶元素并出栈
 */
float popFloatStack(FloatStack stack){
    //栈顶指针前移，返回栈顶数据
    return stack->arr[--stack->ptr];
}

/*
 * 浮点数栈 - 清空栈
 */
void clearFloatStack(FloatStack stack) {
    //栈顶指针置初始值
    stack->ptr = 0;
}

/*
 * 浮点数栈 - 判断空栈
 */
int isEmptyFloatStack(FloatStack stack) {
    //判断栈顶指针是否为初始值
    return stack->ptr == 0;
}