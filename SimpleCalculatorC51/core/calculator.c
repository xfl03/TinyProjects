/*
 * ���������߼�
 */
#include "calculator.h"
#include "../utils/io.h"

/*
 * ״̬��״̬
 * 0: ��̬
 * 1: ����������
 * 2: ���������ֺ�С����
 * 3: ���������֡�С�����С���������
 * 4: ������������
 * 5: ��̬
 */
int state;

/*
 * ������ֵ˫�����
 * ��ȡ����С�������ڵ�������ֵ
 */
CharDequeStruct inputDequeStruct;
CharDeque inputDeque;

/*
 * ������ջ
 * �洢������
 */
CharDequeStruct operatorStackStruct;
CharDeque operatorStack;

/*
 * ������ջ
 * �洢������ֵ
 */
FloatStackStruct numberStackStruct;
FloatStack numberStack;

/*
 * ���������߼� - ״̬����
 * ʹ��״̬���������ַ����д���
 */
void processState(char c) {
    //״̬����0Ϊ��̬
    switch (state) {
        case 0:
            if (isNumber(c)) {
                //�ı�״̬��1
                state = 1;

                //���������ֵ�����������
                addLastCharDeque(inputDeque, c);
            } else if (c == '(') {
                //��������������������ջ
                addLastCharDeque(operatorStack, c);
            } else {
                //�Ƿ������򱨴�
                handleError("ILLEGAL INPUT ");
            }
            break;
        case 1:
            if (isNumber(c)) {
                //���������ֵ�����������
                addLastCharDeque(inputDeque, c);
            } else if (isSimpleOperator(c)) {
                //�ı�״̬��0
                state = 0;

                //����Ǽ򵥲���������������ջ
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //��������ȼ�������
                calculate(c);
                //��������ջ
                addLastCharDeque(operatorStack, c);
            } else if (c == '.') {
                //�ı�״̬��2
                state = 2;

                //�����С���㣬�������������
                addLastCharDeque(inputDeque, c);
            } else if (c == ')') {
                //�ı�״̬��4
                state = 4;

                //����������ţ���������ջ
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //���㵽������Ϊֹ�Ĳ�����
                calculate(c);
            } else if (c == '=') {
                //�ı�״̬��5
                state = 5;

                //����ǵȺţ���������ջ
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //�������в�����
                calculate(c);
            }
            break;
        case 2:
            if (isNumber(c)) {
                //�ı�״̬��3
                state = 3;

                //���������ֵ�����������
                addLastCharDeque(inputDeque, c);
            } else {
                //�Ƿ������򱨴�
                handleError("ILLEGAL INPUT ");
            }
            break;
        case 3:
            if (isNumber(c)) {
                //���������ֵ�����������
                addLastCharDeque(inputDeque, c);
            } else if (isSimpleOperator(c)) {
                //�ı�״̬��0
                state = 0;

                //����Ǽ򵥲���������������ջ
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //��������ȼ�������
                calculate(c);
                //��������ջ
                addLastCharDeque(operatorStack, c);
            } else if (c == ')') {
                //�ı�״̬��4
                state = 4;

                //����������ţ���������ջ
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //���㵽������Ϊֹ�Ĳ�����
                calculate(c);
            } else if (c == '=') {
                //�ı�״̬��5
                state = 5;

                //����ǵȺţ���������ջ
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //�������в�����
                calculate(c);
            } else {
                //�Ƿ������򱨴�
                handleError("ILLEGAL INPUT ");
            }
            break;
        case 4:
            if (isSimpleOperator(c)) {
                //�ı�״̬��0
                state = 0;

                //����Ǽ򵥲���������������ȼ�������
                calculate(c);
                //�򽫲�������ջ
                addLastCharDeque(operatorStack, c);
            } else if (c == ')') {
                //����������ţ�����㵽������Ϊֹ�Ĳ�����
                calculate(c);
            } else if (c == '=') {
                //�ı�״̬��5
                state = 5;

                //����ǵȺţ���������в�����
                calculate(c);
            } else {
                //�Ƿ������򱨴�
                handleError("ILLEGAL INPUT ");
            }
            break;
        default:
            //�Ƿ�״̬����
            handleError("ILLEGAL INPUT ");
    }

    //��������ַ�
    writeChar(c);

    //��̬ʱ���ջ��Ԫ����Ϊ������
    if (state == 5 && !isEmptyFloatStack(numberStack)) {
        writeFloat(popFloatStack(numberStack));
        //��ʼ��������
        initCalculator();
    }
}

/*
 * ���������߼� - �ַ�����
 */
void processChar(char c) {
    //�������ΪC���ʼ�����������������״̬����
    if (c == 'C') {
        initCalculator();
        clearScreen();
    }
    else processState(c);
}

/*
 * ���������߼� - ��ֵ����
 * ʹ�ò�����ջ�����м���
 */
void calculateTop() {
    //��ȡ������
    char op = removeLastCharDeque(operatorStack);

    //��ȡ������
    float num2 = popFloatStack(numberStack);
    float num1 = popFloatStack(numberStack);

    //������
    float result = 0;
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            //�������0�򱨴�
            if (num2 == 0) {
                handleError("DIV 0 WHEN ");
                return;
            }
            result = num1 / num2;
            break;
        default:
            //�Ƿ�����������
            handleError("ILLEGAL OP WHEN ");
            return;
    }

    //��������ѹ��ջ
    pushFloatStack(numberStack, result);
}

/*
 * ���������߼� - ��ֵ����
 * �������ȼ����ڵ���op�Ĳ�����
 */
void calculate(char op) {
    //���op�����ȼ�
    int priority = getPriority(op);

    //�����Ĳ�����
    char opTop = op;

    //����������ջ
    while (!isEmptyCharDeque(operatorStack)) {
        //��ȡջ��������
        opTop = peekLastCharDeque(operatorStack);

        //�ж����ȼ�
        if (getPriority(opTop) < priority) break;

        if (opTop == '(') {
            //���ջ���������ţ����Ƴ�
            removeLastCharDeque(operatorStack);

            //�������δ���루ȱ�������ţ����򱨴�
            if (op == '=') handleError("MISS ) WHEN ");

            //��������
            break;
        } else {
            //ʹ��ջ�����������м���
            calculateTop();
        }
    }

    //�������δ���루ȱ�������ţ����򱨴�
    if (op == ')' && opTop != '(') handleError("MISS ( WHEN ");
}

/*
 * ���������߼� - ����������
 */
float parseFloat(CharDeque deque) {
    //�������������
    float number = 0;
    //�Ƿ���С������
    bool hasRight = false;
    //clearScreen();

    //��ͷ��β�������л�ȡ����ֵ
    while (!isEmptyCharDeque(deque)) {
        //��ȡ����Ԫ��
        char num = removeFirstCharDeque(deque);
        //writeChar(num);
        //writeChar('L');

        //�����ȡ��С���㣬��ı��־����������
        if (num == '.') {
            hasRight = true;
            break;
        }

        //����ֵ������
        number = number * 10 + (float) (num - '0');
    }

    //�����С�����֣����β��ͷ������ȡС��ֵ
    if (hasRight) {
        //��ʱ�洢С������
        float right = 0;

        //��β��ͷ����
        while (!isEmptyCharDeque(deque)) {
            //��ȡ��βԪ��
            char num = removeLastCharDeque(deque);
            //writeChar(num);
            //writeChar('R');

            //����ֵ����С������
            right = right / 10 + (float) (num - '0');
        }

        //��С�����ִ�����
        number += right / 10;
    }

    //��ʼ�����������У��Ա��ٴ�����
    clearCharDeque(deque);
    //writeFloat(number);

    //���ؽ���ֵ
    return number;
}

/*
 * ���������߼� - ��ȡ���������ȼ�
 */
int getPriority(char op) {
    /*
     * ���ȼ�
     * 0: =
     * 1: ( )
     * 2: + -
     * 3: * /
     */
    switch (op) {
        case '=':
            return 0;
        case '(':
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        default:
            return 4;
    }
}

/*
 * ���������߼� - ���������Ϣ
 */
void handleError(string msg) {
    //��ʼ��������
    initCalculator();
    //����
    clearScreen();
    //���������Ϣ
    writeString(msg);
}

/*
 * ���������߼� - ��ʼ��������
 */
void initCalculator() {
    //״̬��״̬��Ϊ��̬
    state = 0;

    //��ʼ��������ֵ˫�����
    inputDeque = &inputDequeStruct;
    clearCharDeque(inputDeque);
    //��ʼ��������ջ
    operatorStack = &operatorStackStruct;
    clearCharDeque(operatorStack);
    //��ʼ��������ջ
    numberStack = &numberStackStruct;
    clearFloatStack(numberStack);
}

/*
 * ���������߼� - �Ƿ�򵥲�����
 */
bool isSimpleOperator(char input) {
    return input == '+' || input == '-' || input == '*' || input == '/';
}

/*
 * ���������߼� - �Ƿ�������
 */
bool isNumber(char input) {
    return input >= '0' && input <= '9';
}