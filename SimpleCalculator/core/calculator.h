/*
 * 计算器主逻辑
 */
#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "../utils/chardeque.h"
#include "../utils/floatstack.h"
#include "../utils/bool.h"

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
CharDeque inputDeque;

/*
 * 操作符栈
 * 存储操作符
 */
CharDeque operatorStack;

/*
 * 操作数栈
 * 存储操作数值
 */
FloatStack numberStack;

/*
 * 计算器主逻辑 - 状态处理
 * 使用状态机对输入字符进行处理
 */
void processState(char c);

/*
 * 计算器主逻辑 - 字符处理
 */
void processChar(char c);

/*
 * 计算器主逻辑 - 数值计算
 * 使用操作符栈顶进行计算
 */
void calculateTop();

/*
 * 计算器主逻辑 - 数值计算
 * 计算优先级大于等于op的操作符
 */
void calculate(char op);

/*
 * 计算器主逻辑 - 获取操作符优先级
 */
int getPriority(char op);

/*
 * 计算器主逻辑 - 解析浮点数
 */
float parseFloat(CharDeque deque);

/*
 * 计算器主逻辑 - 处理错误信息
 */
void handleError(char* msg);

/*
 * 计算器主逻辑 - 初始化计算器
 */
void initCalculator();

/*
 * 计算器主逻辑 - 是否是简单操作符
 */
bool isSimpleOperator(char input);

/*
 * 计算器主逻辑 - 是否是数字
 */
bool isNumber(char input);

#endif
