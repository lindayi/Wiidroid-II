#include "Demo.h"

static NOTIFYICONDATA nid;

// ��ʾ����ͼ��
VOID ShowTaskBar(HWND hWnd)
{
	nid.cbSize = sizeof(nid);
	nid.hWnd = hWnd;
	nid.uID = ID_TASKBAR;
	nid.uCallbackMessage = WM_COMMAND;
	nid.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICONAPP)); 
	lstrcpy(nid.szTip, TEXT("Demo"));
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &nid);
}

// ��������ͼ��
VOID DestroyTaskBar()
{
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

// ��ʾ���̲˵�
VOID ShowTaskBarMenu(HWND hWnd)
{
	HMENU		hmenu;				// �����˵�
	HMENU		hmenuTrackPopup;	// �����˵�	
	POINT		pt;

	// ��ȡ��굱ǰλ���Թ������˵�������λ
	GetCursorPos(&pt);

	//����ڲ˵��ⵥ������˵�����ʧ������
	SetForegroundWindow(hWnd);

	// ���ز˵���Դ����ò˵����
	if ((hmenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_BAR))) == NULL) {
		return;
	}

	// ��ȡ�Ӳ˵����
	hmenuTrackPopup = GetSubMenu(hmenu, 0);

	// �����˵�
	TrackPopupMenuEx(hmenuTrackPopup, TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		pt.x, pt.y, hWnd, NULL);

	// ��ɺ���Ҫ�ͷ������Դ
	DestroyMenu(hmenu);
}