
#include <windows.h>
// #include <iostream>
#include <stdio.h>
// using namespace std;
DWORD nCount = 0;//����һ��ȫ�ֱ�����������������һ���ж��ٴ���(��������������)

BOOL CALLBACK EnumChildProc(
    HWND hwnd,      // handle to child window
    LPARAM lParam   // application-defined value
)
{
	++nCount;
	TCHAR szCh[128];
	GetClassName(hwnd, szCh, 128);
	//GetWindowText(hwnd, szCh, sizeof(szCh));
	// cout << hwnd << endl;
	if(IsWindowVisible(hwnd))printf("%s\n", szCh);
	// cout << "============================================" << endl;
	// cout << nCount << endl;
	EnumChildWindows(hwnd, EnumChildProc, NULL);
	return TRUE;
}


int main(int argc, char* argv[])
{
	HWND hwnd = FindWindow(L"Notepad++", 0);
	EnumChildWindows(hwnd, EnumChildProc, NULL);

	return 0;
}
