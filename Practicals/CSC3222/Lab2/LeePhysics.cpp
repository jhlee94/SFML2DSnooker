#include "LeePhysics.h"

vector3 LeePhysics::calFinVelocity(const vector3 &u, const vector3 &a, const float &msec)
{
	return u + (a*msec);
}

vector3 LeePhysics::calDisplacement(const vector3 &u, const vector3 &a, const float &msec)
{
	return (u*msec) + 0.5f * a * (msec*msec);
}

vector3 LeePhysics::exEulVel1(const vector3 &v0, const vector3 &a0, const float &dt)
{
	return v0 + a0 * dt;
}
vector3 LeePhysics::exEulDis1(const vector3 &s0, const vector3 &v0, const float &dt)
{
	return s0 + v0 * dt;
}

vector3 LeePhysics::impEulVel1(const vector3 &v0, const vector3 &a1, const float &dt)
{
	return v0 + a1 * dt;
}
vector3 LeePhysics::impEulDis1(const vector3 &s0, const vector3 &v1, const float &dt)
{
	return s0 + v1 * dt;
}


vector3 LeePhysics::semiEulVel1(const vector3 &v0, const vector3 &a0, const float &dt)
{
	return exEulVel1(v0, a0, dt);
}
vector3 LeePhysics::semiEulDis1(const vector3 &s0, const vector3 &v0, const vector3 &a0, const float &dt)
{
	return s0 + (exEulVel1(v0, a0, dt) *dt);
}