#ifndef _BALL_H_
#define _BALL_H_

#include "Entity.h"

enum Colour
{
	RED = 1, 
	YELLOW = 2, 
	GREEN = 3, 
	ORANGE = 4, 
	BLUE = 5, 
	PINK = 6, 
	BLACK = 7, 
	WHITE
};
class Ball :
	public Entity
{
private:
	glm::vec2* m_vel;
	glm::vec2* m_accel;
	float radius;
	float mass;
public:
	Colour m_colour;
public:
	Ball();
	Ball(const float &x, const float &y, const float &r, Colour colour);
	Ball(const Ball &cpy);
	~Ball();

	Ball& operator= (const Ball &cpy);

	float getRadius() const;
	void  setRadius(const float &r);

	glm::vec2* getVelocity() const;
	void setVelocity(const float &x, const float &y);

	glm::vec2* getAcceleration() const;
	void setAcceleration(const float &x, const float &y);

	void draw();
};
#endif
