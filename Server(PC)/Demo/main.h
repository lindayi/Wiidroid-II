#ifndef _MAIN_H
#define _MAIN_H

extern HINSTANCE hInst;

// �Ի�������
BOOL WINAPI Main_Proc(HWND, UINT, WPARAM, LPARAM);

// �Ի��򴴽�ʱִ�еĺ���
BOOL Main_OnInitDialog (HWND, HWND, LPARAM);

// �Ի���ť��Ϣ������
void Main_OnCommand(HWND, INT, HWND, UINT);

// �Ի���رմ�����
void Main_OnClose(HWND);

// �����̺߳���
UINT WINAPI ThreadNet(LPVOID lpParam);

#endif
