#include <windows.h>
#include "resource.h"
#include <stdio.h>
LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow) {
	MSG msg;
	DialogBox(hInstance,(LPCTSTR)IDD_DLGTEST,NULL,
	          (DLGPROC)DlgProc);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK
DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	char strText[100], strText2[100], result[100], sign[2];
	float res;
	switch (message) {
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam) ) {
				case IDOK:
					PostQuitMessage(0);
					return TRUE;
				case IDCANCEL:
					PostQuitMessage(0);
					return TRUE;
				case IDC_BTN1:
					GetDlgItemText(hDlg,IDC_EDIT1,strText, 100);
					GetDlgItemText(hDlg,IDC_EDIT2,sign, 2);
					GetDlgItemText(hDlg,IDC_EDIT3,strText2, 100);
						if (sign[0] == '+') res = atoi(strText) + atoi(strText2);
						else if (sign[0] == '-') res = atoi(strText) - atoi(strText2);
						else if (sign[0] == '*')res = atoi(strText) * atoi(strText2);
						else if (sign[0] == '/' && atoi(strText2) != 0) res = (float) atoi(strText) / atoi(strText2);
						else res = 0;	
					sprintf(result, "%.2f", res);
					SetDlgItemText(hDlg,IDC_EDIT4,result);
					HWND hWnd;
					COPYDATASTRUCT data;
					hWnd=FindWindow("Host","Host");
					data.cbData=strlen(result);
					data.lpData=result;
					SendMessage (hWnd, WM_COPYDATA, (WPARAM)GetFocus(),
					            (LPARAM)&data);
					break;
			}
			break;
		default:
			return FALSE;
	}
}
