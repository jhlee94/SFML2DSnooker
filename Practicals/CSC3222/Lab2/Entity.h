#pragma once
#include "vector3.h"
class Entity{

public:
	Entity() {
		v = new vector3();
		aggroRange = 0.0f;
		entitiesInRange = 0;
	}

	~Entity() {
		delete v;
		v = nullptr;
	}

	Entity(float &x, float &y, float &z) {
		v = new vector3(x, y, z);
	}

	Entity(const Entity &obj) {
		v = new vector3();
		*v = *obj.v;
	}

	void setAggroRange(const float &aggro) {
		aggroRange = aggro;
	}

	void setEntitiesInRange(const int &entities) {
		entitiesInRange = entities;
	}

	void setPosition(float &x, float &y, float &z) {
		v->x = x;
		v->y = y;
		v->z = z;
	}

	float getAggroRange() const {
		return aggroRange;
	}

	int getEntitiesInRange() const {
		return entitiesInRange;
	}

	vector3 * getPosition() const {
		return v;
	}

private:
	vector3 *v;
	float aggroRange;
	int entitiesInRange;
};

