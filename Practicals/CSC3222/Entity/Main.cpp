#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Entity.h"

using namespace std;

int main()
{
	srand(time(NULL));
	const int count = 100;
	Entity *(entities)[count];

	for (int i = 0; i < count; i++) {
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 5.0f));
		float range = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		entities[i] = new Entity(x, y, z);
		entities[i]->setAggroRange(range);
	}

	for (int i = 0; i < 5; i++) {
		cout << "Vector " << i + 1 << ":" << endl;
		cout << "x: " << entities[i]->getPosition()[0] << endl;
		cout << "y: " << entities[i]->getPosition()[1] << endl;
		cout << "z: " << entities[i]->getPosition()[2] << endl;
		cout << "Range: " << entities[i]->getAggroRange() << endl << endl;
	}

	for (int i = 0; i < count; i++) {
		delete entities[i];
	}

	return 0;
}