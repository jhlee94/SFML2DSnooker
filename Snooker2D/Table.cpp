#include "Table.h"


Table::Table()
{
	width = WIDTH;
	height = HEIGHT;

	initPockets();
	initCushions();
}


Table::~Table()
{
	delete[] pockets;
	delete[] cushions;
}

void Table::initCushions()
{
	cushions = new cushion[6];
	cushions[0].vertices[0] = glm::vec2(20.f, 42.5f);
	cushions[0].vertices[1] = glm::vec2(35.f, 65.f);
	cushions[0].vertices[2] = glm::vec2(35.f, height - 65.f);
	cushions[0].vertices[3] = glm::vec2(20.f, height - 42.5f);
	cushions[0].aabb[0] = glm::vec2(20.f, 42.5f); // AABB min
	cushions[0].aabb[1] = glm::vec2(35.f, height - 42.5f); // AABB max

	cushions[1].vertices[0] = glm::vec2((width / 2.f) - POCKET_RADIUS, 20.f);
	cushions[1].vertices[1] = glm::vec2((width / 2.f) - 22.5f, 35.f);
	cushions[1].vertices[2] = glm::vec2(65.f, 35.f);
	cushions[1].vertices[3] = glm::vec2(42.5f, 20.f);
	cushions[1].aabb[0] = glm::vec2(42.5f, 20.f);
	cushions[1].aabb[1] = glm::vec2((width / 2.f) - POCKET_RADIUS, 35.f);

	cushions[2].vertices[0] = glm::vec2(width - 42.5, 20);
	cushions[2].vertices[1] = glm::vec2(width - 65, 35);
	cushions[2].vertices[2] = glm::vec2((width / 2) + 22.5, 35);
	cushions[2].vertices[3] = glm::vec2((width / 2) + POCKET_RADIUS, 20);
	cushions[2].aabb[0] = glm::vec2((width / 2) + POCKET_RADIUS, 20);
	cushions[2].aabb[1] = glm::vec2(width - 42.5, 35);

	cushions[3].vertices[0] = glm::vec2(width - 20, height - 42.5);
	cushions[3].vertices[1] = glm::vec2(width - 35, height - 65);
	cushions[3].vertices[2] = glm::vec2(width - 35, 65);
	cushions[3].vertices[3] = glm::vec2(width - 20, 42.5);
	cushions[3].aabb[0] = glm::vec2(width - 35, 42.5);
	cushions[3].aabb[1] = glm::vec2(width - 20, height - 42.5);

	cushions[4].vertices[0] = glm::vec2((width / 2) + POCKET_RADIUS, height - 20);
	cushions[4].vertices[1] = glm::vec2((width / 2) + 22.5, height - 35);
	cushions[4].vertices[2] = glm::vec2(width - 65, height - 35);
	cushions[4].vertices[3] = glm::vec2(width - 42.5, height - 20);
	cushions[4].aabb[0] = glm::vec2((width / 2) + POCKET_RADIUS, height - 35);
	cushions[4].aabb[1] = glm::vec2(width - 42.5, height - 20);

	cushions[5].vertices[0] = glm::vec2(42.5, height - 20);
	cushions[5].vertices[1] = glm::vec2(65, height - 35);
	cushions[5].vertices[2] = glm::vec2((width / 2) - 22.5, height - 35);
	cushions[5].vertices[3] = glm::vec2((width / 2) - POCKET_RADIUS, height - 20);
	cushions[5].aabb[0] = glm::vec2(42.5, height - 35);
	cushions[5].aabb[1] = glm::vec2((width / 2) - POCKET_RADIUS, height - 20);
}

void Table::initPockets()
{
	pockets = new Ball[6];
	for (int i = 0; i < 6; i++)
	{
		pockets[i].setRadius(POCKET_RADIUS);
	}
	pockets[0].setPosition(30.f, 30.f);
	pockets[1].setPosition(width / 2.f, 20.f);
	pockets[2].setPosition(width - 30.f, 30.f);
	pockets[3].setPosition(width - 30.f, height - 30.f);
	pockets[4].setPosition(width / 2.f, height - 20.f);
	pockets[5].setPosition(30.f, height - 30.f);
}

void Table::draw()
{
	// surface
	glColor4f(0.f, 0.78824f, 0.34117f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.f, 0.f);
	glVertex2f(width*1.f, 0.f);
	glVertex2f(width*1.f, height*1.f);
	glVertex2f(0.f, height*1.f);
	glEnd();

	drawDZone(D_ZONE_RADIUS);
	
	//cushion
	for (int i = 0; i < 6; i++)
	{
		cushions[i].draw();
	}

	//boarder
	glColor3f(0.545098f, 0.270588f, 0.0745098f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.f, 0.f);
	glVertex2f(20.f, 0.f);
	glVertex2f(20.f, height *1.f);
	glVertex2f(0.f, height*1.f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.f, 0.f);
	glVertex2f(width*1.f, 0.f);
	glVertex2f(width*1.f, 20.f);
	glVertex2f(0.f, 20.f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(width*1.f, 0.f);
	glVertex2f(width*1.f, height*1.f);
	glVertex2f(width - 20.f, height*1.f);
	glVertex2f(width - 20.f, 0.f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(width*1.f, height*1.f);
	glVertex2f(width*1.f, height - 20.f);
	glVertex2f(0.f, height - 20.f);
	glVertex2f(0.f, height*1.f);
	glEnd();

	for (int i = 0; i < 6; i++)
	{
		pockets[i].draw();
	}
}

void Table::drawDZone(float radius)
{
	// D-Zone
	glLineWidth(1);
	glColor3f(1.f, 1.f, 1.f);
	glBegin(GL_LINES);
	glVertex2f(ORANGE_X, 35.f);
	glVertex2f(ORANGE_X, height - 35.f);
	glEnd();

	glBegin(GL_LINE_STRIP);

	// D zone vertices
	for (float i = 270; i <= 450.f; i++)
	{
		float degInRad = (float) DEG2RAD(i);
		glVertex2f(cos(degInRad)*radius + ORANGE_X, sin(degInRad)*radius + ORANGE_Y);
	}

	glEnd();
}