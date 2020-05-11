#include "ConsoleEngine.h"
#include "Ray.h"
#include <Windows.h>
#include <cmath>

ConsoleEngine::ConsoleEngine(int _ScreenWidth, int _ScreenHeight)
	:
	screenHeight(_ScreenHeight),
	screenWidth(_ScreenWidth),
	mapLenght(6),
	depthIndex(25),
	fieldOfView(3.14f / 4.0f)
{
	totalScreenCharSize = _ScreenHeight * _ScreenWidth;
	SetConsoleActiveScreenBuffer(hConsoleOutput);
	screen = new wchar_t[totalScreenCharSize];

	map  = L"OOOOOO";
	map += L"O....O";
	map += L"O....O";
	map += L"O....O";
	map += L"O....O";
	map += L"OOOOOO";

	player.x = 4.0f;
	player.y = 4.0f;
	player.rotation = 0.0f;
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
	for (int x = 0; x < screenWidth; x++)
	{
		float rayAngle = (player.rotation - (fieldOfView / 2.0f)) + (((float)x / (float)screenWidth) * fieldOfView);

		float rayLenght = 0.0f;
		bool hitWall = false;

		float rayXA = std::sinf(rayAngle);
		float rayYA = std::cosf(rayAngle);

		while (!hitWall && rayLenght < mapLenght)
		{
			rayLenght += 0.1f;

			int rayHitX = (int)(player.x + rayXA * rayLenght);
			int rayHitY = (int)(player.y + rayYA * rayLenght);

			if (rayHitX < 0 || rayHitX >= mapLenght || rayHitY < 0 || rayHitY >= mapLenght)
			{
				hitWall = true; 
				rayLenght = mapLenght;
			}
			else
			{
				if (map[rayHitX + rayHitY * mapLenght] == 'O')
					hitWall = true;
			}
		}

		int floorPos = ((float)screenHeight / 2.0f) + ((float)screenHeight / rayLenght);
		if (floorPos > screenHeight)
			floorPos = screenHeight;
		int cellingPos = screenHeight - floorPos;

		for (int y = 0; y < cellingPos; y++)
			screen[x + y * screenWidth] = ' ';
		for (int y = cellingPos; y < floorPos; y++)
			screen[x + y * screenWidth] = wchar_t(0x2588);
		for (int y = floorPos; y < screenHeight; y++)
			screen[x + y * screenWidth] = ' ';

		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			player.rotation -= (0.0001f);
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			player.rotation += (0.0001f);
	}
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
