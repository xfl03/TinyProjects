/*
 * IO���ƣ�����̨ʵ�֣�
 */
#include <stdio.h>
#include <stdlib.h>
#include "io.h"

/*
 * IO���� - ��ȡ�ַ�������̨ʵ�֣�
 */
char readChar() {
    //�ݴ��ȡ���ַ�
    char input;

    //�ӿ���̨��ȡ�ַ������Կհ��ַ�
    while ((input = (char) getchar()) && (input == '\n' || input == '\r' || input == ' '));

    //���ض�ȡ���ַ�
    return (char) input;
}

/*
 * IO���� - д���ַ�������̨ʵ�֣�
 */
void writeChar(char c) {
    //�����̨д���ַ�
    putchar(c);
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
 * IO���� - �����Ļ���ݣ�����̨ʵ�֣�
 */
void clearScreen() {
    //����
    putchar('\n');
}

/*
 * IO���� - ��ʼ��IO������̨ʵ�֣�
 */
void initIO() {
    //�������κβ���
}

/*
 * IO���� - ��ʱ������̨ʵ�֣�
 */
void delay(int ms) {
    //�������κβ���
}