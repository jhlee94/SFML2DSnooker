#ifndef _TABLE_H_
#define _TABLE_H_
#include "Ball.h"

class Table :
	public Entity
{
private:
	struct cushion
	{
		glm::vec2* vertices = new glm::vec2[4];
		glm::vec2* aabb = new glm::vec2[2];
		~cushion() {
			delete[] vertices;
			delete[] aabb;
		}
		void draw()
		{
			glColor3f(0.f, 0.392156f, 0.f);
			glBegin(GL_TRIANGLE_FAN);
			glVertex2f(vertices[0].x, vertices[0].y);
			glVertex2f(vertices[1].x, vertices[1].y);
			glVertex2f(vertices[2].x, vertices[2].y);
			glVertex2f(vertices[3].x, vertices[3].y);
			glEnd();
		}
	};
	float friction;
public:
	int width, height;
	cushion* cushions;
	Ball *pockets;
private:
	void initPockets();
	void initCushions();
	void drawDZone(float radius);
public:
	Table();
	~Table();

	void draw();
};
#endif
