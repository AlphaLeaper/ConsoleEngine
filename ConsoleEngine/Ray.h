#pragma once
#include "Player.h"
#include <iostream>

class Ray
{
public:
	Ray(std::wstring map, Player player, float radian);
private:
	float CalculateLenght();
public:
	int X();
	int Y();
	float Lenght();
private:
	int x;
	int y;
	float lenght;
};