/*
 * ����ģ��
 * ʹ�ð�ť&�������
 */
#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "../reg51.h"

/*
 * ����ģ�� - ��ȡʵʱ��ť�����ַ�
 * ������ - ����'\0'
 */
char readButton();

/*
 * ����ģ�� - ��ȡʵʱ��������ַ�
 * ������ - ����'\0'
 */
char readMatrix();

/*
 * ����ģ�� - �ȴ�����ȡ��ť&�������������
 */
char readKeyboard();

#endif
