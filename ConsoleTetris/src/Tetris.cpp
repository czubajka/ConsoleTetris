#include <iostream>
#include <windows.h>

constexpr int screenWidth { 80 };
constexpr int screenHeight { 30 };

std::wstring tetromino[7];
constexpr int fieldWidth { 12 };
constexpr int fieldHeight { 18 };
unsigned char *playField { nullptr };		// to be allocated dynamically
											// unsigned char for 0 to represent white space


int Rotate(int px, int py, int rotation)
{
	switch (rotation % 4)
	{
	case 0: return py * 4 + px;				// 0 degrees
	case 1: return 12 + py - (px * 4);		// 90 degrees
	case 2: return 15 - (py * 4) - px;		// 180 degrees
	case 3: return 3 - py + (px * 4);		// 270 degrees
	}	
	return 0;
}

int main()
{
	//HWND console = GetConsoleWindow();
	//RECT r;
	//GetWindowRect(console, &r); //stores the console's current dimensions
	//MoveWindow(console, r.left, r.top, screenWidth*10, screenHeight*10, TRUE); // 800 width, 100 height
	
	//create assets
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");



	// create screen buffer
	wchar_t *screen = new wchar_t[screenWidth * screenHeight];
	for (int i = 0; i < screenHeight * screenWidth; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;


	playField = new unsigned char[fieldHeight * fieldWidth];		// create playfield buffer
	for(int x = 0; x < fieldWidth; x++)								// fill the board, make board boundary
		for (int y = 0; y < fieldHeight; y++)
			playField[y * fieldWidth + x] = (x == 0 || x == fieldWidth - 1 || y == fieldHeight - 1) ? 9 : 0;	// 9 represents border, 0 empty space	
	
																												
	// game loop
	bool gameOver{ false };
	while (!gameOver)
	{
		// draw field
		for (int x = 0; x < fieldWidth; x++)
			for (int y = 0; y < fieldHeight; y++)
				screen[(y + 2) * screenWidth + (x + 2)] = L" ABCDEFG=#"[playField[y * fieldWidth + x]];		// +2 for drawing span

		// display frame
		WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}
}