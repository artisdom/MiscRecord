//-----------------------------------------------------------------------------------
// ��Ȩ��scut4009����
//-----------------------------------------------------------------------------------
// �ļ�����SocketSever.cpp
// ��д�ˣ�ZP1015
// ��дʱ�䣺2015/04/7
// ���빤��: Visual Studio 2008
// ����˵��: socket���߳�ͨ��,��������,����TCP
//------------------------------------------------------------------------------------
// #include "stdafx.h"
// #include "Socket.h"

#include <windows.h>
#include <stdio.h>

#define MaxSize BUFSIZ


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


//********************************************************************************************************/
//** ������ ** main()
//**  ����  ** ��
//**  ���  ** ��
//**��������** ������
//********************************************************************************************************/
int main()
{

	SOCKADDR_IN addrServer;
	int sockServer;


	if (SOCKET_ERROR ==SocketInit()) {
		return -1;
	}

	addrServer.sin_addr.S_un.S_addr=htonl(INADDR_ANY);		//htol�������ֽ���long��ת��Ϊ�����ֽ���
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(6666);						//htos�������˿�ת�����ַ���1024���ϵ����ּ���


	sockServer=socket(AF_INET,SOCK_STREAM,0);				//�������ӵĿɿ��Է���SOCK_STRAM
	bind(sockServer,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));//��socket�󶨵���Ӧ��ַ�Ͷ˿���
	listen(sockServer,5);									//�ȴ������е���󳤶�Ϊ5

	printf("Welcome,the Host %s is running!Now Wating for someone comes in!\n",inet_ntoa(addrServer.sin_addr));


	int len=sizeof(SOCKADDR);

	SOCKADDR_IN addrClient;

	while(1) {
		SOCKET sockClient=accept(sockServer,(SOCKADDR*)&addrClient,&len);//�������ý���ֱ���µ����ӳ���

		if(sockClient == INVALID_SOCKET) {
			printf("Accept Failed!\n");
			continue; //��������
		}
		HANDLE hThread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Send,(LPVOID)sockClient,0,0);//����

		if(hThread1!=NULL) {
			CloseHandle(hThread1);
		}
		HANDLE hThread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Rec,(LPVOID)sockClient,0,0);//����

		if(hThread2!=NULL) {
			CloseHandle(hThread2);
		}
		Sleep(1000);	//һ��Ҫ
	}

	getchar();
	return 0;
}
