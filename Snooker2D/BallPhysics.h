#ifndef _BALL_PHYSICS_H_
#define _BALL_PHYSICS_H_
#include <glm\glm.hpp>
#include "Table.h"
class BallPhysics
{
private:
	struct AABB
	{
		glm::vec2 min;
		glm::vec2 max;
		glm::vec2 vel;
	};
	
	static glm::vec2 max(glm::vec2 &a, glm::vec2 &b);
	static glm::vec2 closest_point(const glm::vec2 &seg_a, const glm::vec2 &seg_b, const glm::vec2 &pos, glm::vec2 &unit_seg_v);

	static glm::vec2 calFinVelocity(const glm::vec2 &u, const glm::vec2 &a, const float &msec);
	static glm::vec2 calDisplacement(const glm::vec2 &u, const glm::vec2 &a, const float &msec);
	static glm::vec2 calAcceleration(const glm::vec2 &a, const float &drag_coef);

	static glm::vec2 exEulVel1(const glm::vec2 &v0, const glm::vec2 &a0, const float &dt);
	static glm::vec2 exEulDis1(const glm::vec2 &s0, const glm::vec2 &v0, const float &dt);

	static glm::vec2 impEulVel1(const glm::vec2 &v0, const glm::vec2 &a1, const float &dt);
	static glm::vec2 impEulDis1(const glm::vec2 &s0, const glm::vec2 &v1, const float &dt);

	static glm::vec2 semiEulVel1(const glm::vec2 &v0, const glm::vec2 &a0, const float &dt);
	static glm::vec2 semiEulDis1(const glm::vec2 &s0, const glm::vec2 &v1, const float &dt);

public:
	static bool AABBball(Ball* a, Ball *b);
	static bool AABBcushion(Ball* a, Table &table);

	static bool collide(Ball* a, Ball*b);
	static bool pocket_collide(Ball* a, Ball*b);
	static void elasticCollision(Ball *a, Ball *b);
	static bool checkBounds(Ball *a, Table &table);
	static void updateBall(Ball*a, float dt);
	
};
#endif
