#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<iostream>
HANDLE hSerial; //处理串口的句柄
HANDLE th;      //处理线程的句柄
DCB dcb;        //存储串口的设置
HWND hwnd;      //处理窗口的句柄
DWORD error;    //发送和接收的时候有用
COMSTAT status;  //发送和接收的时候有用
void Serialreceive();
DWORD WINAPI ThreadProc1(LPVOID lpPraraneter)  //线程函数，不停地读
{
	while (true)
	{
		Serialreceive();
	}
	return  1;
}


void ShutDown()  //关机
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return;
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
}


int SerialBegin()  //打开串口
{
	hSerial = CreateFile("com4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);  //打开
																								   //在设备管理器中查询串口号并更改参数，串口号不能超过10！！！若超过10请更改串口号，方法自行百度
	if (hSerial == INVALID_HANDLE_VALUE)  //如果打开失败
	{
		printf("error");
		return 0;
	}
	return 1;

}


void Serialsetting()
{
	SetupComm(hSerial, 1024, 1024);  //设置TX,RX的缓存区大小都为1024
	GetCommState(hSerial, &dcb);    //得到hSerial中的初始数据给dcb
	dcb.BaudRate = 9600;           //波特率
	dcb.ByteSize = 8;              //字节
	dcb.Parity = NOPARITY;         //奇偶校验
	dcb.StopBits = ONESTOPBIT;     //停止位
	SetCommState(hSerial, &dcb);   //把dcb中的数据给hSerial
	PurgeComm(hSerial, PURGE_TXCLEAR | PURGE_RXCLEAR);  //清空Tx和Rx的缓存区
	printf("打开成功!\n");
}


int Serialwrite(char *write)  //写入
{
	DWORD bytesend = 0;//要写入多少字
	while (write[bytesend] != '\0')  //得到字符串*write的大小
	{
		bytesend++;
	}
	if (!WriteFile(hSerial, write, bytesend, &bytesend, NULL))  //如果写入不成功
	{
		ClearCommError(hSerial, &error, &status);  //清除错误
		return 0;
	}
	else { printf("写入成功\n"); return 1; }
}


void Serialreceive()
{
	char str[50];
	DWORD wcount = 5;  //要读入多少字节
	memset(str, '\0', 50);  //str初始化
	BOOL read;
	ClearCommError(hSerial, &error, &status);
	if (status.cbInQue > 0)  //如果读取有效值大于0
	{
		wcount = status.cbInQue;
		read = ReadFile(hSerial, str, wcount, &wcount, NULL); //读取
		printf("收到%s\n", str);
		/*以下是需要添加代码的地方*/
        printf("\n***Attention! Your computer will shut down in 5 secends!!!***\n");
		/*以上是需要添加代码的地方*/
		ClearCommError(hSerial, &error, &status);  //清空错误
		PurgeComm(hSerial, PURGE_TXABORT | PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXCLEAR);  //清空
    }
}


int main()
{
	SerialBegin();
	Serialsetting();
	DWORD tid;
	th = CreateThread(NULL, 0, ThreadProc1, 0, CREATE_SUSPENDED, &tid);   //创建线程
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);    //设置线程优先级
	SetThreadAffinityMask(th, 1);                                     //自己百度
	ResumeThread(th);                                                //线程开始运作
	while (1)
	{
		char a[50] = { 0 };
		std::cin >> a;   //c++语法,其实就是scanf();
		Serialwrite(a);
        Serialreceive();
	}
}
