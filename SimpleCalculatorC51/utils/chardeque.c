/*
 * �ַ�˫�����
 */
#include <stdlib.h>
#include "chardeque.h"
#include "io.h"

/*
 * �ַ�˫����� - �½�˫�����
 */
CharDeque createCharDeque() {
    //ʹ��malloc����ռ�
    CharDeque deque = (CharDeque) malloc(sizeof(CharDequeStruct));
    //��ʼ����ͷ����βָ��
    deque->firstPtr = 0;
    deque->lastPtr = 0;
    //����deque
    return deque;
}

/*
 * �ַ�˫����� - ���β����ջ & ��ӣ�
 */
void addLastCharDeque(CharDeque deque, char item) {
    //writeChar('P');
    //writeFloat(deque->lastPtr);
    //�����β���ݣ���βָ�����
    deque->arr[deque->lastPtr++] = item;
}

/*
 * �ַ�˫����� - ��ȡ��βԪ�ز��Ƴ�����ջ��
 */
char removeLastCharDeque(CharDeque deque) {
    //��βָ��ǰ�ƣ����ض�β����
    return deque->arr[--deque->lastPtr];
}

/*
 * �ַ�˫����� - ��ȡ��βԪ�ز��Ƴ���ջ����
 */
char peekLastCharDeque(CharDeque deque) {
    //���ض�β����
    return deque->arr[deque->lastPtr - 1];
}

/*
 * �ַ�˫����� - ��ȡ����Ԫ�ز��Ƴ������ӣ�
 */
char removeFirstCharDeque(CharDeque deque) {
    //���ض������ݣ�����ָ�����
    return deque->arr[deque->firstPtr++];
}

/*
 * �ַ�˫����� - ��ȡ����Ԫ�ز��Ƴ������ף�
 */
char peekFirstCharDeque(CharDeque deque){
    //���ض�������
    return deque->arr[deque->firstPtr];
}

/*
 * �ַ�˫����� - ���˫�����
 */
void clearCharDeque(CharDeque deque) {
    //�������βָ���ó�ʼֵ
    deque->firstPtr = 0;
    deque->lastPtr = 0;
}

/*
 * �ַ�˫����� - �жϿ�˫�����
 */
int isEmptyCharDeque(CharDeque deque) {
    //�ж϶��׺Ͷ�βָ���Ƿ�ָ��ͬһ��Ԫ��
    return deque->firstPtr == deque->lastPtr;
}