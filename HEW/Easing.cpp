#include "Easing.h"

#define PI 3.14159265359

double Move_Easing(double x)
{
	//return -(cos(PI * x) - 1) / 2;
	return sin((x * PI) / 2);
}

double Ice_Easing(double x)
{
	return -(cos(PI * x) - 1) / 2;
}