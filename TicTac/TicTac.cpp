#include <windows.h>
#include <tchar.h>
#include "resource.h"

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
void CheckWin(HWND hWnd);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}
bool XorO = true;
TCHAR board[9] = { 0 };

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HWND hcheck;
    switch (message)
    {
    case WM_INITDIALOG:
      
        hcheck = GetDlgItem(hWnd, IDC_CHECK2);
        SendMessage(hcheck, BM_SETCHECK, WPARAM(BST_CHECKED), 0);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON2), FALSE);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON3), FALSE);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON4), FALSE);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON5), FALSE);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON6), FALSE);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON7), FALSE);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON8), FALSE);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON9), FALSE);
        EnableWindow(GetDlgItem(hWnd, IDC_BUTTON10),FALSE);



        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;

    case WM_COMMAND:
        if (wParam == IDC_BUTTON_START)
        {
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON2), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON3), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON4), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON5), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON6), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON7), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON8), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON9), TRUE);
            EnableWindow(GetDlgItem(hWnd, IDC_BUTTON10), TRUE);

            LRESULT result = SendDlgItemMessage(hWnd, IDC_RADIO4, BM_GETCHECK, 0, 0);
            if (result == BST_CHECKED)
            {
                MessageBox(0, TEXT("Человек "), 0, 0);
            }
            else
            {
                result = SendDlgItemMessage(hWnd, IDC_RADIO5, BM_GETCHECK, 0, 0);
                if (result == BST_CHECKED)
                {
                    MessageBox(0, TEXT("Компьютер "), 0, 0);
                }
            }

            result = SendDlgItemMessage(hWnd, IDC_RADIO1, BM_GETCHECK, 0, 0);
            if (result == BST_CHECKED)
            {
                MessageBox(0, TEXT("Уровень 1"), 0, 0);
            }
            else
            {
                result = SendDlgItemMessage(hWnd, IDC_RADIO2, BM_GETCHECK, 0, 0);
                if (result == BST_CHECKED)
                {
                    MessageBox(0, TEXT("Уровень 2"), 0, 0);
                }
                else
                {
                    result = SendDlgItemMessage(hWnd, IDC_RADIO3, BM_GETCHECK, 0, 0);
                    if (result == BST_CHECKED)
                    {
                        MessageBox(0, TEXT("Уровень 3"), 0, 0);
                    }
                }
            }
        }

        int index = -1;
        switch (wParam)
        {
        case IDC_BUTTON2: index = 0; break;
        case IDC_BUTTON3: index = 1; break;
        case IDC_BUTTON4: index = 2; break;
        case IDC_BUTTON5: index = 3; break;
        case IDC_BUTTON6: index = 4; break;
        case IDC_BUTTON7: index = 5; break;
        case IDC_BUTTON8: index = 6; break;
        case IDC_BUTTON9: index = 7; break;
        case IDC_BUTTON10: index = 8; break;
        }

        if (index != -1 && board[index] == 0)
        {
            board[index] = XorO ? 'X' : 'O';
            SetWindowText(GetDlgItem(hWnd, wParam), XorO ? TEXT("X") : TEXT("O"));
            XorO =! XorO;
            CheckWin(hWnd);
        }
        return TRUE;
    }
    return FALSE;
}

void CheckWin(HWND hWnd) {
    int winOrNot[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
    for (int i = 0; i < 8; i++) {
        if (board[winOrNot[i][0]] != 0 &&
            board[winOrNot[i][0]] == board[winOrNot[i][1]] &&
            board[winOrNot[i][1]] == board[winOrNot[i][2]])
        {
            MessageBox(hWnd, board[winOrNot[i][0]] == 'X' ? TEXT("X победил!") : TEXT("O победил!"), TEXT("Игра окончена"), MB_OK);
        }
    }
}
