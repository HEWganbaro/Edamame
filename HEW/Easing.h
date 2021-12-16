#pragma once
#include <math.h>

//プレイヤースピードを変更すると氷の上をすべる処理が
//ずれるからこれで微調整していただきたい
#define EASING_OFFSET 4

double Move_Easing(double x);
double Ice_Easing(double x);