#include "utils/io.h"
#include "core/calculator.h"

/*
 * 程序入口
 */
int main() {
    //初始化IO
    initIO();
    //初始化计算器
    initCalculator();

    //临时保存读取的字符
    char c;

    //读取字符并逐字符交由计算器进行处理
    while((c = readChar())) processChar(c);

    //返回状态码
    return 0;
}