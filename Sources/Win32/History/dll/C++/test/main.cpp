#include <windows.h>
#include <stdio.h>
#include "tool.h"
/** ��ʽ����,����lib�Ǳ����*/
//#pragma comment(lib,"tool.lib")
//Ҫô�Լ�ʹ��ͷ�ļ�
//extern int add(int a,int b);

//_declspec(dllimport) int mul(int a,int b);


int main()
{
	//��̬����
	HINSTANCE hInst;
	hInst=LoadLibrary("tool.dll");
	typedef int (*ADDPROC)(int a,int b);
	ADDPROC Add=(ADDPROC)GetProcAddress(hInst,"_Z3addii");
	if(!Add) {
		return 0;
	}

	printf("5+3=%d",Add(5,3));
	
	//ͨ����ŷ���
	typedef int (*MULPROC)(int a,int b);
	MULPROC Mul=(MULPROC)GetProcAddress(hInst,reinterpret_cast<LPCSTR>(MAKEINTRESOURCE(6)));
	if(!Mul) {
		return 0;

	}
	printf("5*3=%d",Mul(5,3));
	//����c++���г�Ա,dll�����಻����ʾ���ӣ�Ҫʹ����ʽ����
	//http://blog.csdn.net/l460602540/article/details/7394593
	typedef Ctool * (*GetCTool)();//���庯��ָ��,��ȡ��TestDLL����
	GetCTool getCtool=(GetCTool)GetProcAddress(hInst,"GetCTool");
	if(!getCtool) {
		return 0;

	}
	Ctool *tool=getCtool();
	typedef int (*MULPROC)(int a,int b);
	MULPROC sub=(MULPROC)GetProcAddress(hInst,"_ZN5Ctool3subEii");
	printf("5-3=%d",sub(5,3));
	//printf("15/3=%d",tool->div(15,3)); 

	if(hInst) {
		FreeLibrary(hInst);
	}
}

