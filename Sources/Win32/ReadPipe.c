#include <windows.h>
#include <stdio.h>
int main()
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead,&hWrite,&sa,0)) {
		return;
	}
	char command[1024]; //����1K�������У������˰�
	strcpy(command,"cmd /c dir /b"); //ע��dir����һ����ִ���ļ�
	// strcpy(command,"cmd /c dir /b");
	// strcat(command,para_sys);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite; //�Ѵ������̵ı�׼��������ض��򵽹ܵ�����
	si.hStdOutput = hWrite; //�Ѵ������̵ı�׼����ض��򵽹ܵ�����
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//�ؼ����裬CreateProcess�����������������MSDN
	if (!CreateProcess(NULL,command,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi)) {
		CloseHandle(hWrite);
		CloseHandle(hRead);
		MessageBox(0,0,"Feature Detection Failed!",0);
		return;
	}
	CloseHandle(hWrite);
	char buffer[4096] = {0}; //��4K�Ŀռ����洢��������ݣ�ֻҪ������ʾ�ļ����ݣ�һ��������ǹ����ˡ�
	DWORD bytesRead;
	while (1) {
		if (ReadFile(hRead,buffer,4095,&bytesRead,NULL) == NULL)
			break;
		//buffer�о���ִ�еĽ�������Ա��浽�ı���Ҳ����ֱ�����
		printf(buffer);
	}
	CloseHandle(hRead);
}