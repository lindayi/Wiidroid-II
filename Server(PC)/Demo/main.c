#include <process.h>
#include "Demo.h"

static HANDLE sockThread;

#pragma comment (lib, "ws2_32.lib")

// �Ի�������
BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
	// ������Ϣӳ�䣬����ͬ����Ϣӳ�䵽��ͬ�Ĵ�����ȥ
	HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);		// WM_INITDIALOG �Ի��򴴽���ɵ���Ϣ
	HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);			// WM_COMMAND ��ť�Ȱ��µ���Ϣ
	HANDLE_MSG(hWnd, WM_CLOSE, Main_OnClose);				// WM_CLOSE �Ի���رյ���Ϣ

	// ֻ�ػ�������С����Ϣ
	case WM_SYSCOMMAND:
		if (wParam == SC_MINIMIZE || wParam == SC_CLOSE) {
			// ���ش��ڣ���ʵ��С�����������͵�����ʾֻ�������غ���ʾ���ڣ�
			ShowWindow(hWnd, SW_HIDE);
			// ���뷵�أ�������windows�ٴ��������Ϣ
			return TRUE;
		}
	}

    return FALSE;
}

// �Ի��򴴽�ʱִ�еĺ���
BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    // ���ó���ͼ��
    HICON hIcon = LoadIcon((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE) ,MAKEINTRESOURCE(IDI_ICONAPP));
	SendMessage(hwnd, WM_SETICON, TRUE,  (LPARAM)hIcon);

	// ��ʾ����ͼ��
	ShowTaskBar(hwnd);
    
    return TRUE;
}

// �Ի���ť��Ϣ������
void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	static BOOL threadCreate = FALSE;

	switch(id)
    {
	case IDC_SOCK_CONTRAL:
		if (threadCreate == FALSE) {
			sockThread = (HANDLE)_beginthreadex(NULL, 0, ThreadNet, 0, 0, 0);
			SendMessage(GetDlgItem(hwnd, IDC_SOCK_CONTRAL), WM_SETTEXT, 0, (LPARAM)TEXT("�رշ���"));
			threadCreate = TRUE;
		} else {
			TerminateThread(sockThread, -1);
			SendMessage(GetDlgItem(hwnd, IDC_SOCK_CONTRAL), WM_SETTEXT, 0, (LPARAM)TEXT("��������"));
			threadCreate = FALSE;
		}
		break;
	// ���������Զ�����Ϣ
	case ID_TASKBAR:
		if ((UINT)hwndCtl == WM_LBUTTONDOWN) {
			// ��ʾ������
			ShowWindow(hwnd, SW_SHOW);
			// ����ô���
			SetForegroundWindow(hwnd);
		} else if ((UINT)hwndCtl == WM_RBUTTONDOWN)	{
			// �Ҽ������Ļ���ʾ�˵�
			ShowTaskBarMenu(hwnd);
		}
		break;
		// �ָ����ڣ��Ҽ��������˵� - ���Ҵ���>.<��
	case ID_DEMO_SHOW:
			// ��ʾ������
			ShowWindow(hwnd, SW_SHOW);
			// ����ô���
			SetForegroundWindow(hwnd);
		break;
	// �˳�����
	case ID_DEMO_EXIT:
		DestroyWindow(hwnd);		// ���ٴ���
		DestroyTaskBar();			// ����������
		PostQuitMessage(0);			// �����˳���Ϣ
		break;
	default:
		break;
    }
}

// �Ի���رմ�����
void Main_OnClose(HWND hwnd)
{
	// �رղ���Ĭ���ս�Ի���
    EndDialog(hwnd, 0);

	// ��������ͼ��
	DestroyTaskBar();
}

//����ģʽ
void TypeKeyboard(char recvBuf[])
{
//	POINT curpos;
	HWND hWnd = NULL;
	INT KeyCode;//���������Ϣ����
	CHAR trans[4];//��ʱת��char_to_int�ı���
	INPUT Input;//SendInput()�������¼�����

	//GetCursorPos(&curpos);//��ȡ��ǰ����λ�ã�λ�ý�������curpos�
	//hWnd = WindowFromPoint(curpos);//����curpos��ָ��������ȡ���ھ��
	/*hWnd = FindWindow(NULL, TEXT("�ޱ��� - ���±�"));
	if (hWnd) {
		ShowWindow(hWnd, SW_NORMAL);
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		SetForegroundWindow(hWnd);
	} else {
		MessageBox(NULL, TEXT("Cannot find!"), TEXT("Error"), MB_OK | MB_ICONERROR);
	}*/
	strncpy(trans,&recvBuf[6],3);
	trans[3] = '\0';
	//��recvBuf�ļ�����Ϣ��ֵ��KeyCode
	KeyCode = atoi(trans);
	switch(recvBuf[4])//�ж�KeyDown��KeyUpss
	{
		case '0':
			//��SendMessage()���У�����SendInput()����
			keybd_event(KeyCode, 0, 0, 0);
			//keybd_event(KeyCode, 0, KEYEVENTF_KEYUP, 0);
			break;
		case '1':
			keybd_event(KeyCode, 0, KEYEVENTF_KEYUP, 0);
			break;
	}
}

//���ģʽ
void TypeMouse(char recvBuf[])
{
	POINT curpos;
	HWND hWnd;
	INT fMouse;

	GetCursorPos(&curpos);//��ȡ��ǰ����λ�ã�λ�ý�������curpos�
	hWnd = WindowFromPoint(curpos);//����curpos��ָ��������ȡ���ھ��
	fMouse = GetSystemMetrics (SM_MOUSEPRESENT) ;//�������Ƿ����
	if(fMouse == 0);
}

//��̨������������socket��������Ϣ
//recvBuf[]��ʽ��ģʽ(1,2)_��Ϣ����(KeyDown,KeyUp)_������
void InspectMsg(char recvBuf[])
{
	switch(recvBuf[2])
	{
		case '1': 
			TypeKeyboard(recvBuf);
			break;
		case '2':
			TypeMouse(recvBuf);
			break;
	}
}

//��̨������(����socket���������ַ�)
/*void SendMsg(char recvBuf[])
{
	POINT curpos;//һ���ɴ��������Ľṹ�������x�����꣬y,�����꣬��curpos.x   curpos.y
	HWND hWnd;

	while(TRUE)
	{
		GetCursorPos(&curpos);//��ȡ��ǰ����λ�ã�λ�ý�������curpos�
		hWnd = WindowFromPoint(curpos);//����curpos��ָ��������ȡ���ھ��
		InspectMsg(recvBuf);//�����ַ���
		//SendMessage(hWnd,WM_CHAR,(WPARAM)recvBuf,0);//����һ���ַ�����������Ϣ����ǰ�����ָ��Ĵ��ھ��
	}
}*/

// �����̺߳���
UINT WINAPI ThreadNet(LPVOID lpParam)
{
	WSADATA				WSADa;
	SOCKADDR_IN			SockAddrIn;
	SOCKET				CSocket, SSocket;		
	INT					iAddrSize;
	CHAR				recvBuf[50];

	// ��ʼ����������
	ZeroMemory( &WSADa, sizeof(WSADATA) );

	// ���� ws2_32.dll
	WSAStartup(MAKEWORD(2, 2), &WSADa);

	// ���ñ�����Ϣ�Ͱ�Э��
	SockAddrIn.sin_family		=  AF_INET;
	SockAddrIn.sin_port			=  htons(12345);
	SockAddrIn.sin_addr.s_addr	=  INADDR_ANY;

	// ���� Socket
	CSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

	// ���ð󶨶˿�
	bind(CSocket, (SOCKADDR *)&SockAddrIn, sizeof(SockAddrIn));

	// ���÷����������˿�
	listen(CSocket, 1);

	iAddrSize = sizeof(SockAddrIn);
	

	while (TRUE)
	{

		// �ȴ�����
		SSocket = accept(CSocket, (SOCKADDR *)&SockAddrIn, &iAddrSize);
		ZeroMemory(recvBuf, sizeof(recvBuf));
		recv(SSocket, recvBuf, 50, 0);
		// �յ��˴���ͺ�
		// .....
		//��̨������
		InspectMsg(recvBuf);
		closesocket(SSocket);
		//closesocket(CSocket);
	}

	return TRUE;
}
