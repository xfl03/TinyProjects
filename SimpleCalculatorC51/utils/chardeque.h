/*
 * �ַ�˫�����
 */
#ifndef _CHAR_DEQUE_H
#define _CHAR_DEQUE_H

#include "../type.h"

/*
 * �ַ�˫����� - �ṹ���壨����ģ�⣩
 */
typedef struct CharDequeStruct0{
    /*
     * ˫���������
     */
    char arr[20];
    /*
     * ����ָ�룬ָ�����Ԫ��
     */
    char firstPtr;
    /*
     * ��βָ�룬ָ���β�ĺ�һ��Ԫ��
     */
    char lastPtr;
} *CharDeque, CharDequeStruct;

/*
 * �ַ�˫����� - �½�˫�����
 */
CharDeque createCharDeque();

/*
 * �ַ�˫����� - ���β����ջ & ��ӣ�
 */
void addLastCharDeque(CharDeque deque, char item);

/*
 * �ַ�˫����� - ��ȡ��βԪ�ز��Ƴ�����ջ��
 */
char removeLastCharDeque(CharDeque deque);

/*
 * �ַ�˫����� - ��ȡ��βԪ�ز��Ƴ���ջ����
 */
char peekLastCharDeque(CharDeque deque);

/*
 * �ַ�˫����� - ��ȡ����Ԫ�ز��Ƴ������ӣ�
 */
char removeFirstCharDeque(CharDeque deque);

/*
 * �ַ�˫����� - ��ȡ����Ԫ�ز��Ƴ������ף�
 */
char peekFirstCharDeque(CharDeque deque);

/*
 * �ַ�˫����� - ���˫�����
 */
void clearCharDeque(CharDeque deque);

/*
 * �ַ�˫����� - �жϿ�˫�����
 */
bool isEmptyCharDeque(CharDeque deque);

#endif
