#pragma once
#include "vector3.h"
class LeePhysics
{
public:
	static vector3 calFinVelocity(const vector3 &u, const vector3 &a, const float &msec);
	static vector3 calDisplacement(const vector3 &u, const vector3 &a, const float &msec);
	
	static vector3 exEulVel1(const vector3 &v0, const vector3 &a0, const float &dt);
	static vector3 exEulDis1(const vector3 &s0, const vector3 &v0, const float &dt);

	static vector3 impEulVel1(const vector3 &v0, const vector3 &a1, const float &dt);
	static vector3 impEulDis1(const vector3 &s0, const vector3 &v1, const float &dt);

	static vector3 semiEulVel1(const vector3 &v0, const vector3 &a0, const float &dt);
	static vector3 semiEulDis1(const vector3 &s0, const vector3 &v0, const vector3 &a0, const float &dt);
};

