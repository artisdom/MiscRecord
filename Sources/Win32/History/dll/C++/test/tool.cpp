// tool.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "tool.h"


// ���ǵ���������һ��ʾ��
TOOL_API int ntool=0;

// ���ǵ���������һ��ʾ����
TOOL_API int fntool(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� tool.h
Ctool::Ctool()
{
	return;
}
int Ctool::sub(int a,int b)
{

	return a-b;
}
int Ctool::div(int a,int b)
{

	return a/b;
}

TOOL_API int add(int a,int b)
{

	return a+b;
}

TOOL_API int mul(int a,int b)
{

	return a*b;
}
//�����dll�ǲ�֧����ĵ�����.ֻ֧��c���ĺ����ĵ���.ҪŪMFC DLL���̲���
extern "C" TOOL_API Ctool *GetCTool()
{

	return new Ctool();
}