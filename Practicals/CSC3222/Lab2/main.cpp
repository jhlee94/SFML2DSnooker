#include "SuvatCalc.h"
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

	float x1, y1, z1, x2, y2, z2, time;

	cout << "Enter initial velocity (x, y, z): " << endl;
	cin >> x1;
	cin >> y1;
	cin >> z1;
	cout << "Enter acceleration (x, y, z): " << endl;
	cin >> x2;
	cin >> y2;
	cin >> z2;
	cout << "Enter time: ";
	cin >> time;

	vector3 v_fin = SuvatCalc::calFinVelocity(vector3(x1, y1, z1), vector3(x2, y2, z2), time);

	cout << "Final velocity:" << endl
		<< "x: " << v_fin.x << endl
		<< "y: " << v_fin.y << endl
		<< "z: " << v_fin.z << endl;

	delete[] vectors;

	return 0;
}