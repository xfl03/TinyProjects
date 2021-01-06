/*
 * ����ģ��
 * ʹ�ð�ť&�������
 */
#include "../reg51.h"
#include "../type.h"
#include "../utils/io.h"

/*
 * ������������ź�
 * �����Ͻǵ����½�
 */
const unsigned char matrixCodes[] = {
        0xee, 0xde, 0xbe, 0x7e,
        0xed, 0xdd, 0xbd, 0x7d,
        0xeb, 0xdb, 0xbb, 0x7b,
        0xe7, 0xd7, 0xb7, 0x77,
};

/*
 * �������&��ť��������
 * �����Ͻǵ����½�
 */
const char keyboardChars[] = {
        '7', '8', '9', '+',
        '4', '5', '6', '-',
        '1', '2', '3', '*',
        '0', '0', '.', '/',
        '(', ')', 'C', '='
};

/*
 * �ݴ���������
 */
uchar codeKeyboard;

/*
 * ѭ������
 */
int iKeyboard;

/*
 * ��ʱ�����ȡ���ַ�
 */
char cKeyboard;

/*
 * ����ģ�� - ��ȡʵʱ��������ַ�
 * ������ - ����'\0'
 */
char readMatrix() {
    //�ó�ʼֵ
    codeKeyboard = 0;

    //�����ֵ
    P1 = 0x0f;
    if (P1 != 0x0f) codeKeyboard = P1;
    else return '\0';

    //�ȴ�һС��ʱ����ٴμ��
    delay(50);

    //�����ֵ
    P1 = 0xf0;
    if (P1 != 0xf0) codeKeyboard = P1 | codeKeyboard;
    else return '\0';

    //�ȴ��ɿ���ť
    while (P1 != 0xf0);

    //Ѱ�Ҷ�Ӧ��ֵ
    for (iKeyboard = 0; iKeyboard < 16; ++iKeyboard) {
        if (codeKeyboard == matrixCodes[iKeyboard]) {
            return keyboardChars[iKeyboard];
        }
    }

    //δ��⵽���뷵��0
    return '\0';
}

/*
 * ����K3����P30
 * ӳ��Ϊ(
 */
sbit K1 = P3 ^0;

/*
 * ����K3����P31
 * ӳ��Ϊ)
 */
sbit K2 = P3 ^1;

/*
 * ����K3����P32
 * ӳ��Ϊ��ʼ��C
 */
sbit K3 = P3 ^2;

/*
 * ����K4����P33
 * ӳ��Ϊ=
 */
sbit K4 = P3 ^3;

/*
 * ����ģ�� - ��ȡʵʱ��ť�����ַ�
 * ������ - ����'\0'
 */
char readButton() {

    //���μ�ⰴť
    if (K1 == 0) {
        //�ȴ�һС��ʱ����ٴμ��
        delay(50);
        if (K1 == 0) {
            //�ȴ��ɿ���ť
            while (K1 == 0);
            //������Ϊ���µİ�ť
            return keyboardChars[16];
        }
    }
    if (K2 == 0) {
        //�ȴ�һС��ʱ����ٴμ��
        delay(50);
        if (K2 == 0) {
            //�ȴ��ɿ���ť
            while (K2 == 0);
            //������Ϊ���µİ�ť
            return keyboardChars[17];
        }
    }
    if (K3 == 0) {
        //�ȴ�һС��ʱ����ٴμ��
        delay(50);
        if (K3 == 0) {
            //�ȴ��ɿ���ť
            while (K3 == 0);
            //������Ϊ���µİ�ť
            return keyboardChars[18];
        }
    }
    if (K4 == 0) {
        //�ȴ�һС��ʱ����ٴμ��
        delay(50);
        if (K4 == 0) {
            //�ȴ��ɿ���ť
            while (K4 == 0);
            //������Ϊ���µİ�ť
            return keyboardChars[19];
        }
    }

    return 0;
}

/*
 * ����ģ�� - �ȴ�����ȡ��ť&�������������
 */
char readKeyboard() {
    while (true) {
        //��ʼ��
        cKeyboard = 0;

        //���δӰ�ť�;����г��Զ�ȡ
        if ((cKeyboard = readButton())) return cKeyboard;
        if ((cKeyboard = readMatrix())) return cKeyboard;

        //�ӳ�100ms�����һ�������ź�
        //delay(100);
    }
}