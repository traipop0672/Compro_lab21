#include <windows.h>
#include <stdio.h>



HWND textfield1, textfield2;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE: {
            CreateWindow("STATIC", "Please input two numbers", 
                WS_VISIBLE | WS_CHILD | SS_CENTER, 
                20, 20, 200, 25, hwnd, NULL, NULL, NULL);

            textfield1 = CreateWindow("EDIT", "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER, 
                45, 55, 150, 25, hwnd, NULL, NULL, NULL);

            textfield2 = CreateWindow("EDIT", "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER, 
                45, 90, 150, 25, hwnd, NULL, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 60, 130, 30, 30, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 95, 130, 30, 30, hwnd, (HMENU)2, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 130, 130, 30, 30, hwnd, (HMENU)3, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 165, 130, 30, 30, hwnd, (HMENU)4, NULL, NULL);
            break;
        }
		case WM_COMMAND: {
			int wmId = LOWORD(wParam);
            if (wmId >= 1 && wmId <= 4) {
                char t1[100], t2[100], resStr[100];
                double num1, num2, result = 0;

                GetWindowText(textfield1, t1, 100);
                GetWindowText(textfield2, t2, 100);

                num1 = atof(t1);
                num2 = atof(t2);

                if (wmId == 1) result = num1 + num2;
                else if (wmId == 2) result = num1 - num2;
                else if (wmId == 3) result = num1 * num2;
                else if (wmId == 4) {
                    if (num2 != 0) result = num1 / num2;
                    else {
                        MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                }
                sprintf(resStr, "%f", result);
                MessageBox(hwnd, resStr, "Result", MB_OK);
            }
            break;
		}
		/* Upon destruction, tell the main thread to stoxp */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(50,205,50));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU|WS_CAPTION,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}