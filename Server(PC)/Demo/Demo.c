#include "Demo.h"

// Ӧ�ó���ʵ��
HINSTANCE hInst;

INT APIENTRY WinMain(	HINSTANCE hInstance,
						HINSTANCE hPrevInstance,
						LPSTR     lpCmdLine,
						INT       nCmdShow )
{
	hInst = hInstance;

	// ������Դ�ļ���Ϣ�����Ի���
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, Main_Proc);

    return(0);
}
