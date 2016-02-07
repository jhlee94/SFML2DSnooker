#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Entity.h"

using namespace std;

void updateEntities(Entity *&entities, const int size);

int main()
{
	srand(time(NULL));
	const int count = 100;
	Entity *entities = new Entity[count];

	for (int i = 0; i < count; i++) {
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float range = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 1.5f);
		entities[i] = Entity(x, y, z);
		entities[i].setAggroRange(range);
	}

	updateEntities(entities, count);

	delete[] entities;

	return 0;
}

void updateEntities(Entity *&entities, const int size) 
{
	for (int i = 0; i < 5; i++) {
		float* v = entities[i].getPosition();
		cout << "Vector " << i + 1 << ":" << endl;
		cout << "x: " << v[0] << endl;
		cout << "y: " << v[1] << endl;
		cout << "z: " << v[2] << endl;
		cout << "Range: " << entities[i].getAggroRange() << endl << endl;
	}

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if ()
		}
	}

}