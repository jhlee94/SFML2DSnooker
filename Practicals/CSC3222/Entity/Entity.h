#include <iostream>
using namespace std;

class Entity{

public:
	Entity() {
		v[0] = v[1] = v[2] = 0.0f;
		aggroRange = 0.0f;
		entitiesInRange = 0;
	}
	
	Entity(float &x, float &y, float &z) {
		v[0] = x;
		v[1] = y;
		v[2] = z;
		aggroRange = 0.0f;
		entitiesInRange = 0;
	}

	void setAggroRange(const float &aggro) {
		aggroRange = aggro;
	}

	void setEntitiesInRange(const int &entities) {
		entitiesInRange = entities;
	}

	float getAggroRange() const {
		return aggroRange;
	}

	int getEntitiesInRange() const {
		return entitiesInRange;
	}

	float * getPosition() {
		return v;
	}

private:
	float v[3];
	float aggroRange;
	int entitiesInRange;
};