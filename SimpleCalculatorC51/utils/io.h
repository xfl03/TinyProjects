/*
 * IO����
 */
#ifndef _IO_H
#define _IO_H

#include "../type.h"

/*
 * IO���� - ��ȡ�ַ�
 */
char readChar();

/*
 * IO���� - д���ַ�
 */
void writeChar(char c);

/*
 * IO���� - д���ַ���
 */
void writeString(string str);

/*
 * IO���� - д�븡����
 */
void writeFloat(float num);

/*
 * IO���� - �����Ļ����
 */
void clearScreen();

/*
 * IO���� - ��ʼ��IO
 */
void initIO();

/*
 * IO���� - ��ʱ
 */
void delay(int ms);

#endif
