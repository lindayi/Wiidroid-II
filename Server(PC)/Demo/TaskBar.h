#ifndef TASKBAR_H_
#define TASKBAR_H_

#define ID_TASKBAR	0x0401		// ������Ϣ��ǣ��û��Զ�����Ϣ��Ž���� 0x0400 - 0x07FF ��

// ��ʾ����ͼ��
VOID ShowTaskBar(HWND hWnd);

// ��������ͼ��
VOID DestroyTaskBar();

// ��ʾ���̲˵�
VOID ShowTaskBarMenu(HWND hWnd);

#endif