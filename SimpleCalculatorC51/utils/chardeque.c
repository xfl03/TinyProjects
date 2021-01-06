/*
 * 字符双向队列
 */
#include <stdlib.h>
#include "chardeque.h"
#include "io.h"

/*
 * 字符双向队列 - 新建双向队列
 */
CharDeque createCharDeque() {
    //使用malloc分配空间
    CharDeque deque = (CharDeque) malloc(sizeof(CharDequeStruct));
    //初始化队头、队尾指针
    deque->firstPtr = 0;
    deque->lastPtr = 0;
    //返回deque
    return deque;
}

/*
 * 字符双向队列 - 入队尾（入栈 & 入队）
 */
void addLastCharDeque(CharDeque deque, char item) {
    //writeChar('P');
    //writeFloat(deque->lastPtr);
    //置入队尾数据，队尾指针后移
    deque->arr[deque->lastPtr++] = item;
}

/*
 * 字符双向队列 - 获取队尾元素并移除（出栈）
 */
char removeLastCharDeque(CharDeque deque) {
    //队尾指针前移，返回队尾数据
    return deque->arr[--deque->lastPtr];
}

/*
 * 字符双向队列 - 获取队尾元素不移除（栈顶）
 */
char peekLastCharDeque(CharDeque deque) {
    //返回队尾数据
    return deque->arr[deque->lastPtr - 1];
}

/*
 * 字符双向队列 - 获取队首元素并移除（出队）
 */
char removeFirstCharDeque(CharDeque deque) {
    //返回队首数据，队首指针后移
    return deque->arr[deque->firstPtr++];
}

/*
 * 字符双向队列 - 获取队首元素不移除（队首）
 */
char peekFirstCharDeque(CharDeque deque){
    //返回队首数据
    return deque->arr[deque->firstPtr];
}

/*
 * 字符双向队列 - 清空双向队列
 */
void clearCharDeque(CharDeque deque) {
    //队首与队尾指针置初始值
    deque->firstPtr = 0;
    deque->lastPtr = 0;
}

/*
 * 字符双向队列 - 判断空双向队列
 */
int isEmptyCharDeque(CharDeque deque) {
    //判断队首和队尾指针是否指向同一个元素
    return deque->firstPtr == deque->lastPtr;
}