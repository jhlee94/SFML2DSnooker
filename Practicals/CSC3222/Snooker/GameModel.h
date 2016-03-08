#ifndef _GAMEMODEL_H_
#define _GAMEMODEL_H_

#include "vector3.h"

class GameModel
{
public:
	GameModel()
	{
		m_position = vector3(0, 0, 0);
		m_velocity = vector3(0, 0, 0);
	}

	GameModel(const vector3 &pos, const vector3 &vel)
	{
		m_position = pos;
		m_velocity = vel;
	}

	virtual ~GameModel()
	{
		;
	}

	inline vector3 getPosition() const
	{
		return m_position;
	}
	vector3 getVelocity() const
	{
		return m_velocity;
	}
	
	void setPosition(const vector3 &position)
	{
		m_position = position;
	}
	void setVelocity(const vector3 &velocity)
	{
		m_velocity = velocity;
	}

	virtual void draw() = 0;

private:
	vector3 m_position;
	vector3 m_velocity;
};
#endif // !_GAMEMODEL_H_
