/*
 * 计算器主逻辑
 */
#include "calculator.h"
#include "../utils/io.h"

/*
 * 状态机状态
 * 0: 初态
 * 1: 已输入数字
 * 2: 已输入数字和小数点
 * 3: 已输入数字、小数点和小数点后数字
 * 4: 已输入右括号
 * 5: 终态
 */
int state;

/*
 * 输入数值双向队列
 * 存取包括小数点在内的输入数值
 */
CharDequeStruct inputDequeStruct;
CharDeque inputDeque;

/*
 * 操作符栈
 * 存储操作符
 */
CharDequeStruct operatorStackStruct;
CharDeque operatorStack;

/*
 * 操作数栈
 * 存储操作数值
 */
FloatStackStruct numberStackStruct;
FloatStack numberStack;

/*
 * 计算器主逻辑 - 状态处理
 * 使用状态机对输入字符进行处理
 */
void processState(char c) {
    //状态机，0为初态
    switch (state) {
        case 0:
            if (isNumber(c)) {
                //改变状态到1
                state = 1;

                //将输入的数值置入输入队列
                addLastCharDeque(inputDeque, c);
            } else if (c == '(') {
                //如果是左括号则置入符号栈
                addLastCharDeque(operatorStack, c);
            } else {
                //非法输入则报错
                handleError("ILLEGAL INPUT ");
            }
            break;
        case 1:
            if (isNumber(c)) {
                //将输入的数值置入输入队列
                addLastCharDeque(inputDeque, c);
            } else if (isSimpleOperator(c)) {
                //改变状态到0
                state = 0;

                //如果是简单操作符，则将数字入栈
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //计算高优先级操作符
                calculate(c);
                //操作符入栈
                addLastCharDeque(operatorStack, c);
            } else if (c == '.') {
                //改变状态到2
                state = 2;

                //如果是小数点，则置入输入队列
                addLastCharDeque(inputDeque, c);
            } else if (c == ')') {
                //改变状态到4
                state = 4;

                //如果是右括号，则将数字入栈
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //计算到左括号为止的操作符
                calculate(c);
            } else if (c == '=') {
                //改变状态到5
                state = 5;

                //如果是等号，则将数字入栈
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //计算所有操作符
                calculate(c);
            }
            break;
        case 2:
            if (isNumber(c)) {
                //改变状态到3
                state = 3;

                //将输入的数值置入输入队列
                addLastCharDeque(inputDeque, c);
            } else {
                //非法输入则报错
                handleError("ILLEGAL INPUT ");
            }
            break;
        case 3:
            if (isNumber(c)) {
                //将输入的数值置入输入队列
                addLastCharDeque(inputDeque, c);
            } else if (isSimpleOperator(c)) {
                //改变状态到0
                state = 0;

                //如果是简单操作符，则将数字入栈
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //计算高优先级操作符
                calculate(c);
                //操作符入栈
                addLastCharDeque(operatorStack, c);
            } else if (c == ')') {
                //改变状态到4
                state = 4;

                //如果是右括号，则将数字入栈
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //计算到左括号为止的操作符
                calculate(c);
            } else if (c == '=') {
                //改变状态到5
                state = 5;

                //如果是等号，则将数字入栈
                pushFloatStack(numberStack, parseFloat(inputDeque));
                //计算所有操作符
                calculate(c);
            } else {
                //非法输入则报错
                handleError("ILLEGAL INPUT ");
            }
            break;
        case 4:
            if (isSimpleOperator(c)) {
                //改变状态到0
                state = 0;

                //如果是简单操作符，计算高优先级操作符
                calculate(c);
                //则将操作符入栈
                addLastCharDeque(operatorStack, c);
            } else if (c == ')') {
                //如果是右括号，则计算到左括号为止的操作符
                calculate(c);
            } else if (c == '=') {
                //改变状态到5
                state = 5;

                //如果是等号，则计算所有操作符
                calculate(c);
            } else {
                //非法输入则报错
                handleError("ILLEGAL INPUT ");
            }
            break;
        default:
            //非法状态报错
            handleError("ILLEGAL INPUT ");
    }

    //输出输入字符
    writeChar(c);

    //终态时输出栈顶元素作为计算结果
    if (state == 5 && !isEmptyFloatStack(numberStack)) {
        writeFloat(popFloatStack(numberStack));
        //初始化计算器
        initCalculator();
    }
}

/*
 * 计算器主逻辑 - 字符处理
 */
void processChar(char c) {
    //如果输入为C则初始化计算器，否则进行状态处理
    if (c == 'C') {
        initCalculator();
        clearScreen();
    }
    else processState(c);
}

/*
 * 计算器主逻辑 - 数值计算
 * 使用操作符栈顶进行计算
 */
void calculateTop() {
    //获取操作符
    char op = removeLastCharDeque(operatorStack);

    //获取操作数
    float num2 = popFloatStack(numberStack);
    float num1 = popFloatStack(numberStack);

    //计算结果
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
            //如果除以0则报错
            if (num2 == 0) {
                handleError("DIV 0 WHEN ");
                return;
            }
            result = num1 / num2;
            break;
        default:
            //非法操作数报错
            handleError("ILLEGAL OP WHEN ");
            return;
    }

    //将计算结果压入栈
    pushFloatStack(numberStack, result);
}

/*
 * 计算器主逻辑 - 数值计算
 * 计算优先级大于等于op的操作符
 */
void calculate(char op) {
    //获得op的优先级
    int priority = getPriority(op);

    //最后处理的操作符
    char opTop = op;

    //遍历操作符栈
    while (!isEmptyCharDeque(operatorStack)) {
        //获取栈顶操作符
        opTop = peekLastCharDeque(operatorStack);

        //判断优先级
        if (getPriority(opTop) < priority) break;

        if (opTop == '(') {
            //如果栈顶是左括号，则移除
            removeLastCharDeque(operatorStack);

            //如果括号未对齐（缺少右括号），则报错
            if (op == '=') handleError("MISS ) WHEN ");

            //结束遍历
            break;
        } else {
            //使用栈顶操作符进行计算
            calculateTop();
        }
    }

    //如果括号未对齐（缺少左括号），则报错
    if (op == ')' && opTop != '(') handleError("MISS ( WHEN ");
}

/*
 * 计算器主逻辑 - 解析浮点数
 */
float parseFloat(CharDeque deque) {
    //浮点数解析结果
    float number = 0;
    //是否含有小数部分
    bool hasRight = false;
    //clearScreen();

    //从头到尾遍历队列获取整数值
    while (!isEmptyCharDeque(deque)) {
        //获取队首元素
        char num = removeFirstCharDeque(deque);
        //writeChar(num);
        //writeChar('L');

        //如果读取到小数点，则改变标志并结束遍历
        if (num == '.') {
            hasRight = true;
            break;
        }

        //将数值存入结果
        number = number * 10 + (float) (num - '0');
    }

    //如果有小数部分，则从尾到头遍历获取小数值
    if (hasRight) {
        //临时存储小数部分
        float right = 0;

        //从尾到头遍历
        while (!isEmptyCharDeque(deque)) {
            //获取队尾元素
            char num = removeLastCharDeque(deque);
            //writeChar(num);
            //writeChar('R');

            //将数值存入小数部分
            right = right / 10 + (float) (num - '0');
        }

        //将小数部分存入结果
        number += right / 10;
    }

    //初始化输入数队列，以便再次输入
    clearCharDeque(deque);
    //writeFloat(number);

    //返回解析值
    return number;
}

/*
 * 计算器主逻辑 - 获取操作符优先级
 */
int getPriority(char op) {
    /*
     * 优先级
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
 * 计算器主逻辑 - 处理错误信息
 */
void handleError(string msg) {
    //初始化计算器
    initCalculator();
    //清屏
    clearScreen();
    //输出错误信息
    writeString(msg);
}

/*
 * 计算器主逻辑 - 初始化计算器
 */
void initCalculator() {
    //状态机状态设为初态
    state = 0;

    //初始化输入数值双向队列
    inputDeque = &inputDequeStruct;
    clearCharDeque(inputDeque);
    //初始化操作符栈
    operatorStack = &operatorStackStruct;
    clearCharDeque(operatorStack);
    //初始化操作数栈
    numberStack = &numberStackStruct;
    clearFloatStack(numberStack);
}

/*
 * 计算器主逻辑 - 是否简单操作符
 */
bool isSimpleOperator(char input) {
    return input == '+' || input == '-' || input == '*' || input == '/';
}

/*
 * 计算器主逻辑 - 是否是数字
 */
bool isNumber(char input) {
    return input >= '0' && input <= '9';
}