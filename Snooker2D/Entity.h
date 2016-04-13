#pragma once
#define  _USE_MATH_DEFINES
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "defines.h"
class Entity
{
public:
	Entity()
	{
		m_pos = new glm::vec2(0, 0);
	}
	Entity(const Entity &cpy)
	{
		m_pos = new glm::vec2(0, 0);
		m_pos->x = cpy.m_pos->x;
		m_pos->y = cpy.m_pos->y;
	}
	virtual ~Entity()
	{
		delete m_pos;
		m_pos = nullptr;
	}

	inline glm::vec2* getPosition() const
	{
		return m_pos;
	}

	inline void setPosition(const float &x, const float &y)
	{
		m_pos->x = x;
		m_pos->y = y;
	}
	virtual void draw() = 0;
private:
	glm::vec2* m_pos;
};

