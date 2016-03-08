#include <assert.h>

struct vector3 {
	float x, y, z;

	float& operator[](int index) {
		assert(index >= 0 && index < 3);
		return this->*members[index];
	}

	float operator[](int index) const {
		assert(index >= 0 && index < 3);
		return this->*members[index];
	}

	vector3 operator-(vector3 &rhs) const {
		vector3 temp;
		temp[0] = this->*members[0] - rhs[0];
		temp[1] = this->*members[1] - rhs[1];
		temp[2] = this->*members[2] - rhs[2];

		return temp;
	}

	static float vector3::* const members[3];
};

float vector3::* const vector3::members[3] = { &vector3::x, &vector3::y, &vector3::z };

class Entity{

public:
	Entity() {
		v = new vector3;
		aggroRange = 0.0f;
		entitiesInRange = 0;
	}
	
	~Entity() {
		delete v;
		v = nullptr;
	}
	
	Entity(float &x, float &y, float &z) {
		v = new vector3;
		(*v)[0] = x;
		(*v)[1] = y;
		(*v)[2] = z;
	}

	Entity(const Entity &obj) {
		v = new vector3;
		*v = *obj.v;
	}

	void setAggroRange(const float &aggro) {
		aggroRange = aggro;
	}

	void setEntitiesInRange(const int &entities) {
		entitiesInRange = entities;
	}

	void setPosition(float &x, float &y, float &z) {
		(*v)[0] = x;
		(*v)[1] = y;
		(*v)[2] = z;
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