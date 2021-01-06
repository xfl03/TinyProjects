/*
 * 字符双向队列
 */
#ifndef _CHAR_DEQUE_H
#define _CHAR_DEQUE_H

#include "../type.h"

/*
 * 字符双向队列 - 结构定义（数组模拟）
 */
typedef struct CharDequeStruct0{
    /*
     * 双向队列数据
     */
    char arr[20];
    /*
     * 队首指针，指向队首元素
     */
    char firstPtr;
    /*
     * 队尾指针，指向队尾的后一个元素
     */
    char lastPtr;
} *CharDeque, CharDequeStruct;

/*
 * 字符双向队列 - 新建双向队列
 */
CharDeque createCharDeque();

/*
 * 字符双向队列 - 入队尾（入栈 & 入队）
 */
void addLastCharDeque(CharDeque deque, char item);

/*
 * 字符双向队列 - 获取队尾元素并移除（出栈）
 */
char removeLastCharDeque(CharDeque deque);

/*
 * 字符双向队列 - 获取队尾元素不移除（栈顶）
 */
char peekLastCharDeque(CharDeque deque);

/*
 * 字符双向队列 - 获取队首元素并移除（出队）
 */
char removeFirstCharDeque(CharDeque deque);

/*
 * 字符双向队列 - 获取队首元素不移除（队首）
 */
char peekFirstCharDeque(CharDeque deque);

/*
 * 字符双向队列 - 清空双向队列
 */
void clearCharDeque(CharDeque deque);

/*
 * 字符双向队列 - 判断空双向队列
 */
bool isEmptyCharDeque(CharDeque deque);

#endif
