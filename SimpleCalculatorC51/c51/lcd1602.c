/*
 * LCDģ��
 * ʹ��LCD1602
 */
#include "../reg51.h"
#include "../utils/io.h"

/*
 * ��/дѡ��
 * 0 - д��
 * 1 - ��ȡ
 */
sbit LCD_RW = P2 ^5;
/*
 * ����/����ѡ��
 * 0 - ����
 * 1 - ����
 */
sbit LCD_RS = P2 ^6;
/*
 * ʹ���ź�
 * ͨ�����巢���ź�
 */
sbit LCD_E = P2 ^7;

void writeLCD(bool isData, uchar dat) {
    //��ʼ��ʹ�ܡ�ѡ����������ݡ�ѡ��д��
    LCD_E = 0;
    LCD_RS = isData;
    LCD_RW = 0;

    //д������
    P0 = dat;
    delay(1);

    //����ʹ���ź�
    LCD_E = 1;
    delay(5);
    LCD_E = 0;
}

/*
 * LCDģ�� - д��ָ��
 */
void writeCommandLCD(uchar command) {
    writeLCD(false, command);
}

/*
 * LCDģ�� - д������
 */
void writeDataLCD(uchar dat) {
    writeLCD(true, dat);
}

/*
 * LCDģ�� - ���ù��λ��
 */
void setPosLCD(int pos) {
    //һ����ʾ16���ַ����ڶ��д�0x40��ʼ
    if (pos >= 16) pos += 0x30;
    //�ƶ����λ��
    writeCommandLCD(0x80 + pos);
}

/*
 * LCDģ�� - ��ʼ��
 */
void initLCD() {
    //��ʼ��LCD
    writeCommandLCD(0x38);
    //���ÿ���ʾ�����򿪡���˸
    //0000 1111
    writeCommandLCD(0x0f);
    //����д�ַ�������ơ���Ļ����
    //0000 0110
    writeCommandLCD(0x06);
    //����
    writeCommandLCD(0x01);
    //���ù��λ��Ϊ0
    setPosLCD(0);
}
