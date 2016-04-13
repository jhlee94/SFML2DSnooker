#include "Ball.h"

Ball::Ball() : Entity()
{
	radius = 0.f;
	m_colour = BLACK;
	m_vel = new glm::vec2();
	m_accel = new glm::vec2();
}

Ball::Ball(const float &x, const float &y, const float &r, Colour colour) : Ball()
{
	setPosition(x, y);
	radius = r;
	m_colour = colour;
}


Ball::Ball(const Ball &cpy) : Entity(cpy)
{
	m_vel = new glm::vec2();
	m_accel = new glm::vec2();
	setPosition(cpy.getPosition()->x, cpy.getPosition()->y);
	setVelocity(cpy.getVelocity()->x, cpy.getVelocity()->y);
	setAcceleration(cpy.getAcceleration()->x, cpy.getAcceleration()->y);
	radius = cpy.getRadius();
	m_colour = cpy.m_colour;
}

Ball::~Ball()
{
	delete m_vel;
	m_vel = nullptr;
	delete m_accel;
	m_accel = nullptr;
}

Ball& Ball::operator= (const Ball &cpy)
{
	setPosition(cpy.getPosition()->x, cpy.getPosition()->y);
	setVelocity(cpy.getVelocity()->x, cpy.getVelocity()->y);
	setAcceleration(cpy.getAcceleration()->x, cpy.getAcceleration()->y);
	radius = cpy.getRadius();
	m_colour = cpy.m_colour;
	
	return *this;
}

float Ball::getRadius() const
{
	return radius;
}

void Ball::setRadius(const float &r)
{
	radius = r;
}

glm::vec2* Ball::getVelocity() const
{
	return m_vel;
}
void Ball::setVelocity(const float &x, const float &y)
{
	m_vel->x = x;
	m_vel->y = y;
}

glm::vec2* Ball::getAcceleration() const
{
	return m_accel;
}
void Ball::setAcceleration(const float &x, const float &y)
{
	m_accel->x = x;
	m_accel->y = y;
}

void Ball::draw()
{
	switch (m_colour){
	case RED:
		glColor3f(1.f, 0.f, 0.f);
		break;
	case GREEN:
		glColor3f(0.f, 1.f, 0.f);
		break;
	case BLUE:
		glColor3f(0.f, 0.f, 1.f);
		break;
	case ORANGE:
		glColor3f(0.9f, 0.6f, 0.f);
		break;
	case YELLOW:
		glColor3f(1.f, 0.8f, 0.f);
		break;
	case PINK:
		glColor3f(1.f, 0.4f, 0.7f);
		break;
	case BLACK:
		glColor3f(0.f, 0.f, 0.f);
		break;
	case WHITE:
		glColor3f(1.f, 1.f, 1.f);
	}
	glPointSize(2 * getRadius());
	glBegin(GL_POINTS);
	glVertex2f(getPosition()->x, getPosition()->y);
	glEnd();
}


