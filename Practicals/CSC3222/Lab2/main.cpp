#include "LeePhysics.h"
#include "GameTimer.h"
#include "Entity.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
GameTimer timer;

int main()
{
	float totalTime, t0, dt;
	Entity object(0, 0, 0);
	vector3 velocity(0, 0, 0);
	vector3 accel(1, 1, 1);

	vector3 current, next, dis, eul_dis, semi_dis;
	timer.GetTimedMS();
	while (timer.GetMS() < 2000) {
		t0 = timer.GetMS() / 1000;
		// get timer
		dt = timer.GetTimedMS() / 1000;
		cout << dt << endl;

		//current velocity
		current = LeePhysics::calFinVelocity(velocity, accel, t0);
		cout << "Current velocity:" << endl
			<< "x: " << current.x << endl
			<< "y: " << current.y << endl
			<< "z: " << current.z << endl;

		//next frame velocity
		next = LeePhysics::exEulVel1(current, accel, dt);
		cout << "next velocity:" << endl
			<< "x: " << next.x << endl
			<< "y: " << next.y << endl
			<< "z: " << next.z << endl;
		
		dis = LeePhysics::calDisplacement(velocity, accel, t0);
		cout << "Current Displacement:" << endl
			<< "x: " << dis.x << endl
			<< "y: " << dis.y << endl
			<< "z: " << dis.z << endl;

		eul_dis = LeePhysics::exEulDis1(dis, current, dt);
		cout << "Next Displacement:" << endl
			<< "x: " << eul_dis.x << endl
			<< "y: " << eul_dis.y << endl
			<< "z: " << eul_dis.z << endl;
		semi_dis = LeePhysics::semiEulDis1(dis, current, accel, dt);
		cout << "Semi-Euler Displacement:" << endl
			<< "x: " << semi_dis.x << endl
			<< "y: " << semi_dis.y << endl
			<< "z: " << semi_dis.z << endl;
	}
	dis = LeePhysics::calDisplacement(velocity, accel, timer.GetMS()/1000);
	cout << "Current Displacement:" << endl
		<< "x: " << dis.x << endl
		<< "y: " << dis.y << endl
		<< "z: " << dis.z << endl;

	cout << "Total time: " << timer.GetMS();

	/*srand(time(NULL));
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

	vector3 v_fin = LeePhysics::calDisplacement(vector3(x1, y1, z1), vector3(x2, y2, z2), time);

	cout << "Final velocity:" << endl
		<< "x: " << v_fin.x << endl	
		<< "y: " << v_fin.y << endl
		<< "z: " << v_fin.z << endl;

	delete[] vectors; */
	return 0;
}