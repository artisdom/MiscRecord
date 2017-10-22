//tcc -lmpir -run gmptest.c
#include <stdio.h> //hello world ����Ĭ�ϵģ�����㽨�����ǿչ��̾Ͳ���Ҫ���
#include <gmp.h>//�ǵ�����GMP.H��ͷ�ļ�
#pragma comment(lib,"mpir")
int main(int argc, char* argv[])
{
	mpz_t t; //mpz_t ΪGMP���ô�������
	mpz_init(t); //����tʹ��ǰҪ���г�ʼ�����Ա㶯̬����ռ�
	mpz_ui_pow_ui(t, 2, 1000); //GMP���к�������������mpz��ͷ
	gmp_printf("2^100=%Zd\n", t); //��������������ĸ�ʽ����־Ϊ%Zd
	mpz_clear(t);
	return 0;
}