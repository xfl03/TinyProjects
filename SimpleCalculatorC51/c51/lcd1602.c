/*
 * LCD模块
 * 使用LCD1602
 */
#include "../reg51.h"
#include "../utils/io.h"

/*
 * 读/写选择
 * 0 - 写入
 * 1 - 读取
 */
sbit LCD_RW = P2 ^5;
/*
 * 数据/命令选择
 * 0 - 命令
 * 1 - 数据
 */
sbit LCD_RS = P2 ^6;
/*
 * 使能信号
 * 通过脉冲发送信号
 */
sbit LCD_E = P2 ^7;

void writeLCD(bool isData, uchar dat) {
    //初始化使能、选择命令或数据、选择写入
    LCD_E = 0;
    LCD_RS = isData;
    LCD_RW = 0;

    //写入内容
    P0 = dat;
    delay(1);

    //发送使能信号
    LCD_E = 1;
    delay(5);
    LCD_E = 0;
}

/*
 * LCD模块 - 写入指令
 */
void writeCommandLCD(uchar command) {
    writeLCD(false, command);
}

/*
 * LCD模块 - 写入数据
 */
void writeDataLCD(uchar dat) {
    writeLCD(true, dat);
}

/*
 * LCD模块 - 设置光标位置
 */
void setPosLCD(int pos) {
    //一行显示16个字符，第二行从0x40开始
    if (pos >= 16) pos += 0x30;
    //移动光标位置
    writeCommandLCD(0x80 + pos);
}

/*
 * LCD模块 - 初始化
 */
void initLCD() {
    //初始化LCD
    writeCommandLCD(0x38);
    //设置开显示、光标打开、闪烁
    //0000 1111
    writeCommandLCD(0x0f);
    //设置写字符后光标后移、屏幕不动
    //0000 0110
    writeCommandLCD(0x06);
    //清屏
    writeCommandLCD(0x01);
    //设置光标位置为0
    setPosLCD(0);
}
