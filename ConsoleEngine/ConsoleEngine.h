#pragma 
#include "Player.h"
#include <Windows.h>

class ConsoleEngine
{
public:
	ConsoleEngine(int ScreenWidth, int ScreenHeight);
	~ConsoleEngine();
private:
	void PutChar(int possition, char c);
	void PutChar(int x, int y, char c);
	void PrintBufferToConsole();

	void ConposeFrame();
	void UpdateFrame();
	void LateUpdateFame();
public:
	void run();
private:
	int screenWidth;
	int screenHeight;
	int totalScreenCharSize;

	wchar_t* screen;																											//array screen chars
	HANDLE hConsoleOutput = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);	//console buffer																		//setting our buffer as console buffet
	DWORD nLenght = 0;																											//random windows stuff lol	
private:
	/****************************/
	/*                          */
	/*      Game functions      */
	/*                          */
	/****************************/

private:
	/****************************/
	/*                          */
	/*      Game variables      */
	/*                          */
	/****************************/
	Player player;
};