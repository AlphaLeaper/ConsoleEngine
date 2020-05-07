#include "ConsoleEngine.h"
#include "Ray.h"
#include <Windows.h>

ConsoleEngine::ConsoleEngine(int _ScreenWidth, int _ScreenHeight)
	:
	screenHeight(_ScreenHeight),
	screenWidth(_ScreenWidth)
{
	totalScreenCharSize = _ScreenHeight * _ScreenWidth;
	SetConsoleActiveScreenBuffer(hConsoleOutput);
	screen = new wchar_t[totalScreenCharSize];
}

ConsoleEngine::~ConsoleEngine()
{
	delete screen;
}

void ConsoleEngine::PutChar(int _possition, char _c)
{
	screen[_possition] = _c;
}

void ConsoleEngine::PutChar(int _x, int _y, char _c)
{
	screen[screenWidth * _y + _x] = _c;
}

void ConsoleEngine::PrintBufferToConsole()
{
	screen[totalScreenCharSize - 1] = '\0';
	WriteConsoleOutputCharacter(hConsoleOutput, screen, totalScreenCharSize, { 0, 0 }, &nLenght);
}

/*************************************************/
/*                                               */
/* ConposeFrame    - calc for making a frame     */
/* UpdateFrame     - drawing composed frome      */
/* LateUpdateFrame - post drawn calculations     */
/*                                               */
/*************************************************/

void ConsoleEngine::ConposeFrame()
{

}

void ConsoleEngine::UpdateFrame()
{
	PrintBufferToConsole();
}

void ConsoleEngine::LateUpdateFame()
{

}

/************************/
/*                      */
/*	     Game loop      */
/*                      */
/************************/

void ConsoleEngine::run()
{
	while (true)
	{
		ConposeFrame();
		UpdateFrame();
		LateUpdateFame();
	}
}
