//-----------------------------------------------------------------------------------
// ��Ȩ��scut4009����
//-----------------------------------------------------------------------------------
// �ļ�����SocketClient.cpp
// ��д�ˣ�ZP1015
// ��дʱ�䣺2015/04/7
// ���빤��: Visual Studio 2008
// ����˵��: socket���߳�ͨ��
//------------------------------------------------------------------------------------
// #include "stdafx.h"
// #include "Socket.h"
#include <stdio.h>
#include <windows.h>


//********************************************************************************************************/
//** ������ ** SocketInit()
//**  ����  ** ��
//**  ���  ** ��
//**��������** �����׽���
//********************************************************************************************************/
int SocketInit()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested=MAKEWORD(2,2);
	err = WSAStartup(wVersionRequested,&wsaData); //����0���ɹ���������Ǵ�����

	if (err!=0)
	{
		printf("WinSock DLL�汾����Ҫ��n");
		return 0;
	}

	if (LOBYTE(wsaData.wVersion)!=2||
		HIBYTE(wsaData.wVersion)!=2)
	{
		WSACleanup();
		return 0;
	}

	return 1;
}

#define MaxSize BUFSIZ

#pragma comment(lib,"WS2_32.LIB")

const char *SeverIp = "0.0.0.0";//"192.168.1.100";
HANDLE hMutex;

//------------------------------------------------------------------------------------
//��������:      Send(SOCKET sockClient)
/*��������:      ��������
/*��ڲ���:      SOCKET sockClient
//���ڲ���:
//ȫ�ֱ�������:
//����ģ��:      ��
//------------------------------------------------------------------------------------*/
void Send(SOCKET sockClient)
{
	char sendBuf[MaxSize];
	int byte = 0;

	while(1) {
		WaitForSingleObject(hMutex, INFINITE);
		gets(sendBuf);
		byte= send(sockClient,sendBuf,strlen(sendBuf)+1,0);;//�������ӿͻ��˽�������
		if (byte<=0) {
			break;
		}

		Sleep(1000);
		ReleaseMutex(hMutex);

	}
	closesocket(sockClient);//�ر�socket,һ��ͨ�����
}
//------------------------------------------------------------------------------------
//��������:     Rec()
/*��������:     ���պ���
/*��ڲ���:     SOCKET sockClient
//���ڲ���:
//ȫ�ֱ�������:
//����ģ��:      ��
//------------------------------------------------------------------------------------*/
void Rec(SOCKET sockClient)
{

	char revBuf[MaxSize];
	int byte = 0;

	while(1) {
		WaitForSingleObject(hMutex, INFINITE);

		byte= recv(sockClient,revBuf,strlen(revBuf)+1,0);//�������ӿͻ��˽�������
		if (byte<=0) {
			break;
		}

		printf("%s\n",revBuf);

		Sleep(1000);
		ReleaseMutex(hMutex);

	}
	closesocket(sockClient);//�ر�socket,һ��ͨ�����
}

int main()
{

	if (SOCKET_ERROR ==SocketInit()) {
		return -1;
	}

	while(1) {
		SOCKET sockClient=socket(AF_INET,SOCK_STREAM,0);
		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr=inet_addr(SeverIp);//�趨��Ҫ���ӵķ�������ip��ַ
		addrSrv.sin_family=AF_INET;
		addrSrv.sin_port=htons(6666);//�趨��Ҫ���ӵķ������Ķ˿ڵ�ַ
		connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));//���������������


		HANDLE hThread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Rec,(LPVOID)sockClient,0,0);

		if(hThread1!=NULL) {
			CloseHandle(hThread1);
		}

		HANDLE hThread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Send,(LPVOID)sockClient,0,0);

		if(hThread2!=NULL) {
			CloseHandle(hThread2);
		}

		Sleep(1000);

	}
	getchar();

	WSACleanup();
	return -1;
}