#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "Entity.h"

using namespace std;

void updateEntities(Entity *&entities, const int &size);
float calcSqDistance(Entity &a, Entity &b);

int main()
{
	srand(time(NULL));
	const int count = 500;
	Entity *entities = new Entity[count];

	for (int i = 0; i < count; i++) {
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float range = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 3.0f);
		entities[i].setPosition(x, y, z);
		entities[i].setAggroRange(range);
	}

	for (int i = 0; i < 5; i++) {
		vector3 *v;
		v = entities[i].getPosition();
		cout << "Vector " << i + 1 << ":" << endl;
		cout << "x: " << (*v)[0] << endl;
		cout << "y: " << (*v)[1] << endl;
		cout << "z: " << (*v)[2] << endl;
		cout << "Range: " << entities[i].getAggroRange() << endl << endl;
	}

	updateEntities(entities, count);

	for (int i = 0; i < count; i++) {
		cout << "Vector " << i + 1 << ":" << endl;
		cout << "Entities in range: " << entities[i].getEntitiesInRange() << endl;
	}

	delete[] entities;
	return 0;
}

void updateEntities(Entity *&entities, const int &size)
{
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (calcSqDistance(entities[i], entities[j]) <= pow(entities[i].getAggroRange(), 2)) {
				int a = entities[i].getEntitiesInRange();
				a++;
				entities[i].setEntitiesInRange(a);
			}
		}
	}
}

float calcSqDistance(Entity &a, Entity &b) {
	vector3 temp = *b.getPosition() - *a.getPosition();

	return pow(temp[0], 2) + pow(temp[1], 2) + pow(temp[2], 2);
}