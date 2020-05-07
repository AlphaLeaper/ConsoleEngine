#pragma once

class Ray
{
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