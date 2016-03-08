#pragma once
#include "vector3.h"
class SuvatCalc
{
public:
	SuvatCalc();
	~SuvatCalc();

	static vector3 calFinVelocity(const vector3 &u, const vector3 &a, const float &msec);
};

