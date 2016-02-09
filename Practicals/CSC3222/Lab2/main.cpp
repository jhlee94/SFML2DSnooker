#include "vector3.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	srand(time(NULL));
	const int count = 100;
	vector3* vectors = new vector3[count];

	for (int i = 0; i < count; i++) {
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f));
		float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 100.0f));
		vectors[i] = vector3(x, y, z);
	}

	for (int i = 0; i < 5; i++) {
		cout << "Vector " << i + 1 << ":" << endl;
		cout << "x: " << vectors[i].x << endl;
		cout << "y: " << vectors[i].y << endl;
		cout << "z: " << vectors[i].z << endl << endl;
	}

	for (int i = 0; i < count; i++) {
		vector3 v = vectors[i].normalise();
		cout << "Normalised Vector " << i + 1 << ":" << endl;
		cout << "x: " << v.x << endl;
		cout << "y: " << v.y << endl;
		cout << "z: " << v.z << endl << endl;
	}

	delete[] vectors;
	return 0;
}