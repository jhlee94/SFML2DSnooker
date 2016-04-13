#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <string>
#include <vector>
#include "BallPhysics.h"

// Options
bool showFPS = false, showMag = false;

// FPS
int frameCount = 0, currentTime, previousTime = 0, fps;
const float dt_fixed = 1.f / 60.f; // 60fps

// Real Time
int currentFrame, lastFrame = 0,  dt;

// Game Logic
enum { DRAW_NULL, DRAW_AIM, DRAW_SHOT };
int shotTime, mode;
int mouseX, mouseY, mag;
bool placed, p1, p2;
bool firstTouch, secondTouch, touched, stationary, scored;
int colour;
bool dzone = false;

// Game Entities;
Table table;
std::vector<Ball> balls;
std::vector<Ball> player1, player2; // for score

// GL Function
void display(void);
void reshape(GLsizei width, GLsizei height);
void clean();
void idle();
void mouseFunc(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void initDisplay();

// Game Function
void initResources();
void calculateFPS();
void drawFPS(bool draw);
void drawGuide();
void drawCue();
void drawScore();
void drawTargetColour(bool draw);
void drawMagnitude(bool draw);
void slide();
void logic();
void reset();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT+SCORE_SECTION);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Snooker 2D");
	glewInit();
	initDisplay();
	reset();
	initResources();
	
	// Register Callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseFunc);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(mouseMotion);
	glutPassiveMotionFunc(mouseMotion);
	glutCloseFunc(clean);
	glutIdleFunc(idle);

	// Enable
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH); 
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Enter OpenGL main loop
	glutMainLoop();
	return EXIT_SUCCESS;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	table.draw();
	drawScore();
	drawTargetColour(true);
	// white ball
	if (placed) {
		balls[0].draw();
	}
	// rest of the ball
	for (unsigned int i = 1; i < balls.size(); i++) {
		balls[i].draw();
	}

	if (mode == DRAW_SHOT && glutGet(GLUT_ELAPSED_TIME) - shotTime > 50) {
		mode = DRAW_NULL;
	}
	else if (mode != DRAW_NULL && placed) {
		drawMagnitude(showMag);
		drawCue();
		drawGuide();
	}

	drawFPS(showFPS);

	glFlush();
	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	glutReshapeWindow(WIDTH, HEIGHT + SCORE_SECTION);
	lastFrame = glutGet(GLUT_ELAPSED_TIME);
}

void clean()
{
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
}

void idle()
{
	calculateFPS();

	//Animate Balls
	slide();
	
	// Game Logic Check
	if (placed){
		logic();
	}

	glutPostRedisplay();
}

void initDisplay()
{
	glViewport(0, 0, WIDTH, HEIGHT + SCORE_SECTION);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WIDTH, 0.0, HEIGHT + SCORE_SECTION, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.f, 0.f, 0.f, 0.f);
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN) {
			std::cout << "Mouse clicked @(" << x << "," << HEIGHT - y + SCORE_SECTION << ")" << std::endl;
			mouseX = x;
			mouseY = HEIGHT - y + SCORE_SECTION;
			// White ball is not on the table
			if (!placed){
				// forehand position check for white ball with temp ball
				// in order to avoid placing ball over a existing ball
				bool intersect = false;
				Ball temp;
				temp.setPosition(mouseX, mouseY);
				temp.setRadius(RADIUS);
				
				// exclude score section coordinates
				if (mouseY > HEIGHT - 35.f) return;
				// if the white ball is not placed in Dzone *checked once per reset
				if (!dzone) {
					glm::vec2 d = glm::vec2(ORANGE_X, ORANGE_Y) - *temp.getPosition();
					// lies on the left side of semi circle
					if (d.x > 0)
					{
						return;
					}
					float distance_squared = glm::dot(d, d);
					float radius_squared = D_ZONE_RADIUS * D_ZONE_RADIUS;
					if (distance_squared > radius_squared) { // is not in Dzone
						return;
					}
					dzone = true;
				}

				// check if the white ball placing position intersects with other balls
				for (unsigned int i = 1; i < balls.size(); i++){
					if (BallPhysics::AABBball(&temp, &balls[i])){
						intersect = true;
						break;
					}
				}
				if (!intersect) {
					balls[0].setPosition(static_cast<float>(x), static_cast<float>(HEIGHT + SCORE_SECTION - y));
					placed = true;
					showMag = true;
					mode = DRAW_AIM;
				}
			} // White ball is on the table
			else {
				mode = DRAW_AIM;
				showMag = true;
			}
		}
		if (state == GLUT_UP){
			// Apply force to white ball
			if (placed){
				glm::vec2 distance = *balls[0].getPosition() - glm::vec2(mouseX, mouseY);
				if (distance != glm::vec2(0, 0)){
					glm::vec2 new_vel = glm::normalize(distance);
					glm::vec2 maxVector = new_vel*200.f;
					glm::vec2 ratio = distance / maxVector;
					if (ratio.x > 1.0f) ratio.x = 1.0f;
					if (ratio.y > 1.0f) ratio.y = 1.0f;
					balls[0].setVelocity(ratio.x * FORCE_LIMIT*new_vel.x, ratio.y * FORCE_LIMIT*new_vel.y);
					mode = DRAW_SHOT;
					showMag = false;
					shotTime = glutGet(GLUT_ELAPSED_TIME);
					firstTouch = !firstTouch;
					secondTouch = !secondTouch;
					std::cout << firstTouch << std::endl;
					std::cout << secondTouch << std::endl;
				}
			}
		}
	}
}

void mouseMotion(int x, int y)
{
	mouseX = x;
	mouseY = HEIGHT - y + SCORE_SECTION;

	if (showMag) {
		glm::vec2 distance = *balls[0].getPosition() - glm::vec2(mouseX, mouseY);
		if (distance != glm::vec2(0, 0)){
			glm::vec2 new_vel = glm::normalize(distance);
			glm::vec2 maxVector = new_vel*200.f;
			glm::vec2 ratio = distance / maxVector;
			if (ratio.x > 1.0f) ratio.x = 1.0f;
			if (ratio.y > 1.0f) ratio.y = 1.0f;
			new_vel = ratio * new_vel * FORCE_LIMIT;
			mag = glm::length(new_vel);
		}
	}
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		exit(EXIT_SUCCESS);
		break;
	case 'r':
		reset();
		initResources();
		break;
	case 'f':
		if (!showFPS)
			showFPS = true;
		else
			showFPS = false;
	}
}

void reset()
{
	// reset game
	balls.clear();
	player1.clear();
	player2.clear();
	shotTime = 0;
	mode = DRAW_NULL;
	mouseX = -100;
	mouseY = -100;
	mag = 0;
	placed = false;
	showMag = false;
	firstTouch = false;
	secondTouch = true;
	touched = false;
	stationary = true;
	scored = false;
	p1 = true;
	p2 = false;
	dzone = false;
}

void initResources()
{
	// white ball
	balls.push_back(Ball(-100, -100, RADIUS, Colour::WHITE));

	// Red Balls
	int ball_num = 1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < i + 1; j++) {
			float x = RED_X - i * RADIUS * 1.7320f;
			switch (i){
			case 0:
				balls.push_back(Ball(RED_X, RED_Y, RADIUS, Colour::RED)); break;
			case 1:
				if (j == 0)
					balls.push_back(Ball(x, RED_Y + RADIUS, RADIUS, Colour::RED));
				if (j == 1)
					balls.push_back(Ball(x, RED_Y - RADIUS, RADIUS, Colour::RED)); break;
			case 2: 
				if (j == 0)
					balls.push_back(Ball(x, RED_Y + i*RADIUS, RADIUS, Colour::RED));
				if (j == 1)
					balls.push_back(Ball(x, RED_Y, RADIUS, Colour::RED));
				if (j == 2)
					balls.push_back(Ball(x, RED_Y - i*RADIUS, RADIUS, Colour::RED)); break;
			case 3: 
				if (j == 0)
					balls.push_back(Ball(x, RED_Y + i*RADIUS, RADIUS, Colour::RED));
				if (j == 1)
					balls.push_back(Ball(x, RED_Y + RADIUS, RADIUS, Colour::RED));
				if (j == 2)
					balls.push_back(Ball(x, RED_Y - RADIUS, RADIUS, Colour::RED));
				if (j == 3)
					balls.push_back(Ball(x, RED_Y - i*RADIUS, RADIUS, Colour::RED)); break;
			case 4: 
				if (j == 0)
					balls.push_back(Ball(x, RED_Y + i*RADIUS, RADIUS, Colour::RED));
				if (j == 1)
					balls.push_back(Ball(x, RED_Y + i/2*RADIUS, RADIUS, Colour::RED));
				if (j == 2)
					balls.push_back(Ball(x, RED_Y, RADIUS, Colour::RED));
				if (j == 3)
					balls.push_back(Ball(x, RED_Y - i/2*RADIUS, RADIUS, Colour::RED));
				if (j == 4)
					balls.push_back(Ball(x, RED_Y - i*RADIUS, RADIUS, Colour::RED)); break;
			}
			ball_num++;
		}
	}

	// Colour Balls
	balls.push_back(Ball(RED_X + 2*RADIUS, RED_Y, RADIUS, Colour::PINK));
	balls.push_back(Ball(BLUE_X, BLUE_Y, RADIUS, Colour::BLUE));
	balls.push_back(Ball(BLACK_X, BLACK_Y, RADIUS, Colour::BLACK));
	balls.push_back(Ball(ORANGE_X, ORANGE_Y, RADIUS, Colour::ORANGE));
	balls.push_back(Ball(YELLOW_X, YELLOW_Y, RADIUS, Colour::YELLOW));
	balls.push_back(Ball(GREEN_X, GREEN_Y, RADIUS, Colour::GREEN));
}

void calculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	//  Calculate time passed
	int timeInterval = currentTime - previousTime;
	
	if (timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;
		//  Reset frame count
		frameCount = 0;
	}
}

void drawFPS(bool draw)
{
	if (draw) {
		std::string s;
		s = "FPS:" + std::to_string(fps);
		glColor3f(1,1,1);
		glRasterPos2i(80, HEIGHT - 20);
		for (unsigned int i = 0; i < s.size(); i++){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)s[i]); // generation of characters in our text with 9 by 15 GLU font
		}
	}
}

void drawTargetColour(bool draw)
{
	if (draw) {
		std::string s;
		s = (!firstTouch) ? "RED" : "COLOUR";
		glColor3f(1, 1, 1);
		glRasterPos2f(WIDTH - 120.f, 20.f);
		for (unsigned int i = 0; i < s.size(); i++){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)s[i]); // generation of characters in our text with 9 by 15 GLU font
		}
	}
}

void drawGuide()
{
	glLineWidth(2);
	glColor3f(1, 1, 1);
	glLineStipple(1, 10);
	glEnable(GL_LINE_STIPPLE);

	glBegin(GL_LINES);
	glVertex2f(balls[0].getPosition()->x, balls[0].getPosition()->y);
	glVertex2f(mouseX + 3 * (balls[0].getPosition()->x - mouseX),
		mouseY + 3 * (balls[0].getPosition()->y - mouseY));
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void drawCue()
{
	float front_scale, end_scale;
	if (mode == DRAW_AIM) {
		front_scale = .3f;
		end_scale = 3.f;
	}
	else {
		front_scale = .95f;
		end_scale = 4.f;
	}

	glLineWidth(7);
	glColor3f(.647f, .1647f, .1647f);

	glBegin(GL_LINES);
	glVertex2f(mouseX + front_scale*(balls[0].getPosition()->x - mouseX),
		mouseY + front_scale*(balls[0].getPosition()->y - mouseY));
	glVertex2f(mouseX - end_scale*(balls[0].getPosition()->x - mouseX),
		mouseY - end_scale*(balls[0].getPosition()->y - mouseY));
	glEnd();
}

void drawMagnitude(bool draw)
{
	if (draw) {
		std::string s;
		s = "Mag: " + std::to_string(mag);
		glColor3f(0, 0, 0);
		glRasterPos2f(balls[0].getPosition()->x + 2 * balls[0].getRadius(), balls[0].getPosition()->y);
		for (unsigned int i = 0; i < s.size(); i++){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)s[i]); // generation of characters in our text with 9 by 15 GLU font
		}
	}
}

void drawScore()
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5, 0.5, 0.5);
	glVertex2i(0, HEIGHT);
	glVertex2i(WIDTH, HEIGHT);
	glVertex2i(WIDTH, HEIGHT + SCORE_SECTION);
	glVertex2i(0, HEIGHT + SCORE_SECTION);
	glEnd();

	int score_p1 = 0, score_p2 = 0;
	std::string s;
	s = "Player 1";
	if (p1)	glColor3f(0, 1, 0);
	else glColor3f(1, 1, 1);
	glRasterPos2i(20, HEIGHT + SCORE_SECTION/2);
	for (unsigned int i = 0; i < s.size(); i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)s[i]); // generation of characters in our text with 9 by 15 GLU font
	}

	for (unsigned int i = 0; i < player1.size(); i++) {
		player1[i].setPosition(110.f + 2 * player1[i].getRadius() * i, HEIGHT + SCORE_SECTION / 2.f);
		player1[i].draw();
		score_p1 += player1[i].m_colour;
	}

	std::string s2;
	s2 = "Player 2";
	if (p2)	glColor3f(0, 1, 0);
	else glColor3f(1, 1, 1);
	glRasterPos2i(WIDTH - 90, HEIGHT + SCORE_SECTION / 2);
	for (unsigned int i = 0; i < s2.size(); i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)s2[i]); 
	}

	for (unsigned int i = 0; i < player2.size(); i++) {
		player2[i].setPosition(WIDTH - 110.f - 2 * player2[i].getRadius() * i, HEIGHT + SCORE_SECTION / 2.f);
		player2[i].draw();
		score_p2 += player2[i].m_colour;
	}

	std::string scores;
	scores = std::to_string(score_p1) + " : " + std::to_string(score_p2);
	glColor3f(1, 1, 1);
	glRasterPos2i(WIDTH/2 - 20, HEIGHT + SCORE_SECTION / 2);
	for (unsigned int i = 0; i < scores.size(); i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)scores[i]);
	}
	
}

void logic()
{
	// Finish the simulation if there's only white ball left on the table.
	if (balls.size() == 1)
	{
		exit(EXIT_SUCCESS);
	}

	// Check for ball - pocket collision
	for (unsigned int i = 0; i < balls.size(); i++) {
		for (int j = 0; j < 6; j++) {
			if (BallPhysics::AABBball(&balls[i], &table.pockets[j])){

				if (BallPhysics::pocket_collide(&balls[i], &table.pockets[j])) {
					if (i == 0) // White Ball
					{
						balls[i].setPosition(-100, -100);
						balls[i].setAcceleration(0, 0);
						balls[i].setVelocity(0, 0);
						touched = true;
						colour = -1;
						break;
					}
					else { // Coloured Balls
						if (!scored) {
							if (firstTouch && balls[i].m_colour == Colour::RED)
							{
								scored = true;
							}
							else if (secondTouch && balls[i].m_colour > Colour::RED)
							{
								scored = true;
							}
						}
						//balls[index] = balls.back();
						if (p1)
							player1.push_back(balls[i]);
						else
							player2.push_back(balls[i]);
						balls.erase(balls.begin() + i);
						//balls.pop_back();
						break;
					}
				}
			}
		}
	}

	// Check if all the balls stopped
	for (unsigned int i = 0; i < balls.size(); i++){
		if (!(glm::abs(balls[i].getVelocity()->x) < 2 && glm::abs(balls[i].getVelocity()->y) < 2))
		{
			stationary = false;
			break;
		}
		else {
			stationary = true;
		}
	}
	
	// once all balls stopped, check for game logic flags
	if (stationary && mode != DRAW_AIM){
		
		// white ball didn't touch any balls
		if (!touched)
		{
			std::string alert = (p1) ? "Player 1 Foul!" : "Player 2 Foul!";
			std::cout << alert << std::endl;
			placed = false;
			p1 = !p1;
			p2 = !p2;
			firstTouch = false;
			secondTouch = true;
			colour = 0;
		} // white ball touched coloured ball or potted at first take
		else if (firstTouch && (colour != Colour::RED || colour == -1))
		{
			std::string alert = (p1) ? "Player 1 Foul!" : "Player 2 Foul!";
			std::cout << alert << std::endl;
			placed = false;
			p1 = !p1;
			p2 = !p2;
			firstTouch = false;
			secondTouch = true;
		} // white ball touched red ball or potted at second take
		else if (secondTouch && (colour == Colour::RED || colour == -1))
		{
			std::string alert = (p1) ? "Player 1 Foul!" : "Player 2 Foul!";
			std::cout << alert << std::endl;
			placed = false;
			p1 = !p1;
			p2 = !p2;
			firstTouch = false;
			secondTouch = true;
		}  // if didn't score right ball (red for first, colour for second) then turnover
		else if (!scored)
		{
			p1 = !p1;
			p2 = !p2;
			firstTouch = false;
			secondTouch = true;
		}
		touched = false;
		scored = false;
		mode = DRAW_AIM;
		showMag = true;
	}

	
}

// Physics Step
void slide()
{
	// variable DT
	currentFrame = glutGet(GLUT_ELAPSED_TIME);
	dt = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (placed){
		for (unsigned int i = 0; i < balls.size(); i++){
			BallPhysics::updateBall(&balls[i], dt_fixed);
		}

		for (unsigned int i = 0; i < balls.size(); i++)
		{
			for (unsigned int j = i + 1; j < balls.size(); j++)
			{
				//Broad Phase AABB
				if (BallPhysics::AABBball(&balls[i], &balls[j])) {
					//Narrow Phase
					if (BallPhysics::collide(&balls[i], &balls[j]))
					{
						// first ball that white ball contacts
						if (i == 0 && firstTouch && !touched)
						{
							colour = balls[j].m_colour;
							touched = true;
						}
						if (i == 0 && secondTouch && !touched)
						{
							colour = balls[j].m_colour;
							touched = true;
						}

						BallPhysics::elasticCollision(&balls[i], &balls[j]);
					}
				}
			}	
				// Broad Phase AABB
			if (BallPhysics::AABBcushion(&balls[i], table)) { // only if true then
				//Narrow Phase
				BallPhysics::checkBounds(&balls[i], table); 
			}
		}
	}
}
