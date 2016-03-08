#include "SuvatCalc.h"


SuvatCalc::SuvatCalc()
{
}


SuvatCalc::~SuvatCalc()
{
}

vector3 SuvatCalc::calFinVelocity(const vector3 &u, const vector3 &a, const float &msec)
{
	return u + (a*msec);
}
