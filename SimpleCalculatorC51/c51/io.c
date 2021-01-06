/*
 * IO���ƣ�C51ʵ�֣�
 */
#include <stdio.h>
#include <stdlib.h>
#include "../utils/io.h"
#include "lcd1602.h"
#include "keyboard.h"

/*
 * IO���� - ��ȡ�ַ���C51ʵ�֣�
 */
char readChar() {
    //�Ӿ���&��������
    return readKeyboard();
}

int posLCD = 0;

/*
 * IO���� - д���ַ���C51ʵ�֣�
 */
void writeChar(char c) {
    //�ƶ���겢��������
    setPosLCD(posLCD++);
    writeDataLCD(c);

    //�Զ���껻��
    if(posLCD==16) setPosLCD(16);
}

/*
 * IO���� - д���ַ���
 */
void writeString(string str) {
    //���ַ�д���ַ���
    while (*str) writeChar(*(str++));
}

/*
 * IO���� - д�븡����
 */
void writeFloat(float num) {
    //��������ת��Ϊ�ַ���
    char *output = (char *) malloc(20 * sizeof(char));
    sprintf(output, "%g", num);

    //����ַ���
    writeString(output);
}


/*
 * IO���� - �����Ļ���ݣ�C51ʵ�֣�
 */
void clearScreen() {
    //��ԭ���
    posLCD = 0;
    //����
    writeCommandLCD(0x01);
}

/*
 * �ڴ�أ����ڶ�̬�����ڴ�
 */
unsigned char mempool[256];

/*
 * IO���� - ��ʼ��IO��C51ʵ�֣�
 */
void initIO() {
    //��ʼ���ڴ��
    init_mempool(&mempool, sizeof(mempool));
    //��ʼ��LCD
    initLCD();
}

/*
 * IO���� - ��ʱ��C51ʵ�֣�
 */
void delay(int ms) {
    uchar a, b;
    for (; ms > 0; ms--) {
        for (b = 199; b > 0; b--) {
            for (a = 1; a > 0; a--);
        }
    }
}