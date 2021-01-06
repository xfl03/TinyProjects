/*
 * LCDģ��
 * ʹ��LCD1602
 */
#ifndef _LCD1602_H
#define _LCD1602_H

#include "../type.h"

/*
 * LCDģ�� - д��ָ�������
 */
void writeLCD(bool isData, uchar dat);

/*
 * LCDģ�� - д��ָ��
 */
void writeCommandLCD(uchar command);

/*
 * LCDģ�� - д������
 */
void writeDataLCD(uchar dat);

/*
 * LCDģ�� - ���ù��λ��
 */
void setPosLCD(int pos);

/*
 * LCDģ�� - ��ʼ��
 */
void initLCD();

#endif
