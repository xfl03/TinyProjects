/*
 * ���������߼�
 */
#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "../utils/chardeque.h"
#include "../utils/floatstack.h"
#include "../type.h"

/*
 * ���������߼� - ״̬����
 * ʹ��״̬���������ַ����д���
 */
void processState(char c);

/*
 * ���������߼� - �ַ�����
 */
void processChar(char c);

/*
 * ���������߼� - ��ֵ����
 * ʹ�ò�����ջ�����м���
 */
void calculateTop();

/*
 * ���������߼� - ��ֵ����
 * �������ȼ����ڵ���op�Ĳ�����
 */
void calculate(char op);

/*
 * ���������߼� - ��ȡ���������ȼ�
 */
int getPriority(char op);

/*
 * ���������߼� - ����������
 */
float parseFloat(CharDeque deque);

/*
 * ���������߼� - ���������Ϣ
 */
void handleError(string msg);

/*
 * ���������߼� - ��ʼ��������
 */
void initCalculator();

/*
 * ���������߼� - �Ƿ��Ǽ򵥲�����
 */
bool isSimpleOperator(char input);

/*
 * ���������߼� - �Ƿ�������
 */
bool isNumber(char input);

#endif
