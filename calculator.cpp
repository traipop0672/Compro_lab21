#include <windows.h>
#include <stdio.h>


#define ID_EDIT_1 1
#define ID_EDIT_2 2
#define ID_BTN_ADD 3
#define ID_BTN_SUB 4
#define ID_BTN_MUL 5
#define ID_BTN_DIV 6

HWND hEdit1, hEdit2;


void DoCalculation(HWND hwnd, int operation) {
    char str1[100], str2[100];
    GetWindowText(hEdit1, str1, 100);
    GetWindowText(hEdit2, str2, 100);

    double n1 = atof(str1);
    double n2 = atof(str2);
    double res = 0;
    char t[100];

    switch(operation) {
        case ID_BTN_ADD: res = n1 + n2; break;
        case ID_BTN_SUB: res = n1 - n2; break;
        case ID_BTN_MUL: res = n1 * n2; break;
        case ID_BTN_DIV: 
            if(n2 == 0) {
                MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                return;
            }
            res = n1 / n2; 
            break;
    }

    sprintf(t, "%f", res); 
    MessageBox(hwnd, t, "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        case WM_CREATE: {
          
            CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD | SS_CENTER, 
                         25, 10, 200, 20, hwnd, NULL, NULL, NULL);

         
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 
                                  50, 40, 150, 25, hwnd, (HMENU)ID_EDIT_1, NULL, NULL);
            
         
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 
                                  50, 75, 150, 25, hwnd, (HMENU)ID_EDIT_2, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 65, 115, 25, 25, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 95, 115, 25, 25, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 125, 115, 25, 25, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 155, 115, 25, 25, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            if (wmId >= ID_BTN_ADD && wmId <= ID_BTN_DIV) {
                DoCalculation(hwnd, wmId);
            }
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    
    wc.hbrBackground = CreateSolidBrush(RGB(50,205,50)); 
    wc.lpszClassName = "WindowClass";
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }


    hwnd = CreateWindowEx(0, "WindowClass", "My Calculator", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, 
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}