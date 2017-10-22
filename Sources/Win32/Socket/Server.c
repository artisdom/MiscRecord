//-----------------------------------------------------------------------------------
// 版权归scut4009所有
//-----------------------------------------------------------------------------------
// 文件名：SocketSever.cpp
// 编写人：ZP1015
// 编写时间：2015/04/7
// 编译工具: Visual Studio 2008
// 程序说明: socket多线程通信,服务器端,基于TCP
//------------------------------------------------------------------------------------
// #include "stdafx.h"
// #include "Socket.h"

#include <windows.h>
#include <stdio.h>

#define MaxSize BUFSIZ


//********************************************************************************************************/
//** 函数名 ** SocketInit()
//**  输入  ** 无
//**  输出  ** 无
//**函数描述** 加载套接字
//********************************************************************************************************/
int SocketInit()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested=MAKEWORD(2,2);
	err = WSAStartup(wVersionRequested,&wsaData); //返回0，成功，否则就是错误码

	if (err!=0)
	{
		printf("WinSock DLL版本不足要求n");
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
//函数名称:      Send(SOCKET sockClient)
/*函数功能:      发送数据
/*入口参数:      SOCKET sockClient
//出口参数:
//全局变量引用:
//调用模块:      无
//------------------------------------------------------------------------------------*/

void Send(SOCKET sockClient)
{
	char sendBuf[MaxSize];
	int byte = 0;

	while(1) {
		WaitForSingleObject(hMutex, INFINITE);
		gets(sendBuf);
		byte= send(sockClient,sendBuf,strlen(sendBuf)+1,0);;//服务器从客户端接受数据
		if (byte<=0) {
			break;
		}

		Sleep(1000);
		ReleaseMutex(hMutex);

	}
	closesocket(sockClient);//关闭socket,一次通信完毕
}
//------------------------------------------------------------------------------------
//函数名称:     Rec()
/*函数功能:     接收函数
/*入口参数:     SOCKET sockClient
//出口参数:
//全局变量引用:
//调用模块:      无
//------------------------------------------------------------------------------------*/
void Rec(SOCKET sockClient)
{
	char revBuf[MaxSize];
	int byte = 0;

	while(1) {
		WaitForSingleObject(hMutex, INFINITE);

		byte= recv(sockClient,revBuf,strlen(revBuf)+1,0);//服务器从客户端接受数据
		if (byte<=0) {
			break;
		}

		printf("%s\n",revBuf);

		Sleep(1000);
		ReleaseMutex(hMutex);

	}
	closesocket(sockClient);//关闭socket,一次通信完毕
}


//********************************************************************************************************/
//** 函数名 ** main()
//**  输入  ** 无
//**  输出  ** 无
//**函数描述** 主函数
//********************************************************************************************************/
int main()
{

	SOCKADDR_IN addrServer;
	int sockServer;


	if (SOCKET_ERROR ==SocketInit()) {
		return -1;
	}

	addrServer.sin_addr.S_un.S_addr=htonl(INADDR_ANY);		//htol将主机字节序long型转换为网络字节序
	addrServer.sin_family=AF_INET;
	addrServer.sin_port=htons(6666);						//htos用来将端口转换成字符，1024以上的数字即可


	sockServer=socket(AF_INET,SOCK_STREAM,0);				//面向连接的可靠性服务SOCK_STRAM
	bind(sockServer,(SOCKADDR*)&addrServer,sizeof(SOCKADDR));//将socket绑定到相应地址和端口上
	listen(sockServer,5);									//等待队列中的最大长度为5

	printf("Welcome,the Host %s is running!Now Wating for someone comes in!\n",inet_ntoa(addrServer.sin_addr));


	int len=sizeof(SOCKADDR);

	SOCKADDR_IN addrClient;

	while(1) {
		SOCKET sockClient=accept(sockServer,(SOCKADDR*)&addrClient,&len);//阻塞调用进程直至新的连接出现

		if(sockClient == INVALID_SOCKET) {
			printf("Accept Failed!\n");
			continue; //继续监听
		}
		HANDLE hThread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Send,(LPVOID)sockClient,0,0);//发送

		if(hThread1!=NULL) {
			CloseHandle(hThread1);
		}
		HANDLE hThread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)Rec,(LPVOID)sockClient,0,0);//接收

		if(hThread2!=NULL) {
			CloseHandle(hThread2);
		}
		Sleep(1000);	//一定要
	}

	getchar();
	return 0;
}
