#include "utils/io.h"
#include "core/calculator.h"

/*
 * ��ʱ�����ȡ���ַ�
 */
char cMain;

/*
 * �������
 */
int main() {
    //��ʼ��IO
    initIO();
    //��ʼ��������
    initCalculator();

    //��ȡ�ַ������ַ����ɼ��������д���
    while((cMain = readChar())) processChar(cMain);
    //while ((cMain = readChar())) writeChar(cMain);

    //����״̬��
    return 0;
}