#include "BallPhysics.h"

// Basic SUVAT equations
glm::vec2 BallPhysics::calFinVelocity(const glm::vec2 &u, const glm::vec2 &a, const float &msec)
{
	return u + (a*msec);
}

glm::vec2 BallPhysics::calDisplacement(const glm::vec2 &u, const glm::vec2 &a, const float &msec)
{
	return (u*msec) + 0.5f * a * (msec*msec);
}


glm::vec2 BallPhysics::calAcceleration(const glm::vec2 &v, const float &drag_coef)
{
	return v * drag_coef;
}

// Explicit Euler
glm::vec2 BallPhysics::exEulVel1(const glm::vec2 &v0, const glm::vec2 &a0, const float &dt)
{
	return v0 + a0 * dt;
}
glm::vec2 BallPhysics::exEulDis1(const glm::vec2 &s0, const glm::vec2 &v0, const float &dt)
{
	return s0 + v0 * dt;
}

// Implicit Euler
glm::vec2 BallPhysics::impEulVel1(const glm::vec2 &v0, const glm::vec2 &a1, const float &dt)
{
	return v0 + a1 * dt;
}
glm::vec2 BallPhysics::impEulDis1(const glm::vec2 &s0, const glm::vec2 &v1, const float &dt)
{
	return s0 + v1 * dt;
}

// Semi Euler
glm::vec2 BallPhysics::semiEulVel1(const glm::vec2 &v0, const glm::vec2 &a0, const float &dt)
{
	return exEulVel1(v0, a0, dt);
}
glm::vec2 BallPhysics::semiEulDis1(const glm::vec2 &s0, const glm::vec2 &v1, const float &dt)
{
	return s0 + v1 * dt;
}

// compute maximum length of each x and y
glm::vec2 BallPhysics::max(glm::vec2 &a, glm::vec2 &b)
{
	glm::vec2 result;
	if (a.x > b.x)
		result.x = a.x;
	else 
		result.x = b.x;
	if (a.y > b.y)
		result.y = a.y;
	else
		result.y = b.y;

	return result;
}

// Broad Phase
bool BallPhysics::AABBball(Ball *a, Ball *b)
{
	AABB first, second;
	first.min = *a->getPosition() - a->getRadius();
	first.max = *a->getPosition() + a->getRadius();
	second.min = *b->getPosition() - b->getRadius();
	second.max = *b->getPosition() + b->getRadius();

	glm::vec2 distance1 = second.min - first.max;
	glm::vec2 distance2 = first.min - second.max;
	glm::vec2 distances = max(distance1, distance2);

	float maxDistance = (distances.x > distances.y) ? maxDistance = distances.x : maxDistance = distances.y;

	return maxDistance < 0;
}

bool BallPhysics::AABBcushion(Ball* a, Table &table)
{
	AABB first;
	first.min = *a->getPosition() - a->getRadius();
	first.max = *a->getPosition() + a->getRadius();
	for (int i = 0; i < 6; i++){

		glm::vec2 distance1 = table.cushions[i].aabb[0] - first.max;
		glm::vec2 distance2 = first.min - table.cushions[i].aabb[1];
		glm::vec2 distances = max(distance1, distance2);

		float maxDistance = (distances.x > distances.y) ? maxDistance = distances.x : maxDistance = distances.y;

		if (maxDistance < 0) {
			return true;
		}
	}
	return false;
}

// Narrow Phase ball to table collision check
bool BallPhysics::pocket_collide(Ball* a, Ball*b)
{
	glm::vec2 d = *b->getPosition() - *a->getPosition();
	float distance_squared = glm::dot(d, d);
	float radius_squared = a->getRadius() * a->getRadius(); // only the pocket radius to check if the ball's centre passes the pocket
	if (distance_squared < radius_squared) {
		return true;
	}
	return false;
}

// Narrow Phase ball to ball collision check
bool BallPhysics::collide(Ball* a, Ball*b)
{
	glm::vec2 d = *b->getPosition() - *a->getPosition();
	float distance_squared = glm::dot(d, d);
	float radius = a->getRadius() + b->getRadius();
	float radius_squared = radius * radius;
	if (distance_squared < radius_squared) {
		return true;
	}
	return false;
}

// Ball Elastic Collision
void BallPhysics::elasticCollision(Ball *a, Ball *b)
{
	glm::vec2 position, velocity;
	float dot, d, coef;
	
	position = *b->getPosition() - *a->getPosition();
	velocity = *b->getVelocity() - *a->getVelocity();


	dot = glm::dot(velocity, position);

	if (dot <= 0){
		glm::vec2 delta = *b->getPosition() - *a->getPosition();
		float dist = glm::length(delta);
		glm::vec2 penetration = delta * ((a->getRadius() + b->getRadius()) - dist) / dist;
		*a->getPosition() -= 0.5f * penetration;
		*b->getPosition() += 0.5f * penetration;

		coef = position.y / position.x;
		d = -2 * (velocity.x + (coef*velocity.y)) / ((1 + coef*coef) * 2);
		b->getVelocity()->x = b->getVelocity()->x + d;
		b->getVelocity()->y = b->getVelocity()->y + coef*d;
		a->getVelocity()->x = a->getVelocity()->x - d;
		a->getVelocity()->y = a->getVelocity()->y - coef*d;
	}

}

// Projection Method to find the closest point 
glm::vec2 BallPhysics::closest_point(const glm::vec2 &seg_a, const glm::vec2 &seg_b, const glm::vec2 &pos, glm::vec2 &unit_seg_v)
{
	glm::vec2 closest;
	glm::vec2 seg_v = seg_b - seg_a;
	glm::vec2 pt_v = pos- seg_a;
	glm::vec2 proj_v;

	unit_seg_v = glm::normalize(seg_v);
	float proj_v_l = glm::dot(pt_v, unit_seg_v);


	if (proj_v_l < 0)
		return seg_a;
		
	if (proj_v_l > glm::length(seg_v))
		return seg_b;

	proj_v = proj_v_l * unit_seg_v;

	closest = seg_a + proj_v;
	return closest;
}

// Narrow Phase for ball to cushion collision detection and response
bool BallPhysics::checkBounds(Ball *a, Table &table)
{
	// check each cushion segments
	for (int i = 0; i < 6; i++){
		for (int j = 0; j < 3; j++)
		{
			// SAT - Separating Axis Theorem
			// find closest point from cushion to ball
			glm::vec2 closest;
			glm::vec2 seg_a = table.cushions[i].vertices[j];
			glm::vec2 seg_b = table.cushions[i].vertices[j + 1];
			glm::vec2 pos = *(a->getPosition());
			glm::vec2 unit_seg_v;
			closest = closest_point(seg_a, seg_b, pos, unit_seg_v);
			
			// checking for intersaction
			glm::vec2 dist_v = *(a->getPosition()) - closest;
			float x = dist_v.x;
			float y = dist_v.y;
			float dist_v_l = x*x+ y*y;
			
			// if collide
			if (dist_v_l < a->getRadius() * a->getRadius()){
				glm::vec2 new_vel;

				// adjust collision point by adding penetration depth so that wall and the ball are just touching
				*(a->getPosition()) += (a->getRadius() - glm::sqrt(dist_v_l)) * glm::normalize(dist_v);

				// voronoi region testing (edge response)
				if (closest != seg_a && closest != seg_b)
				{ // cushion face - ball collision response
					// normal of cushion's face
					glm::vec2 normal(unit_seg_v.y, -unit_seg_v.x); 
					if (normal.x == -0.00) normal.x = 0;
					if (normal.y == -0.00) normal.y = 0;
					new_vel = *(a->getVelocity()) - 2 * glm::dot(*(a->getVelocity()), normal) * normal;
					*(a->getVelocity()) = new_vel;
					return true;
				}
				else { // Cushion vertex - ball collision response (treating vertex as a static ball with 0 radius)
					// distance from cushion's vertex to the ball
					glm::vec2 distance = (closest - *a->getPosition());
					glm::vec2 coll_normal = distance / glm::length(distance);
					new_vel = (*a->getVelocity() - 2 * glm::dot(*(a->getVelocity()), coll_normal) * coll_normal);

					*(a->getVelocity()) = new_vel;
					return true;
				}
			}
		}
	}
	return false;
}

void BallPhysics::updateBall(Ball*a, float dt)
{
	glm::vec2 vel = *a->getVelocity();
	glm::vec2 accel = *a->getAcceleration();
	glm::vec2 pos = *a->getPosition();
	glm::vec2 new_vel = BallPhysics::semiEulVel1(vel, accel, dt);
	glm::vec2 new_pos = BallPhysics::semiEulDis1(pos, new_vel, dt);
	glm::vec2 new_accel = BallPhysics::calAcceleration(vel, FRICTION);

	if (glm::abs(new_vel.x) < 1 && glm::abs(new_vel.y) < 1)
	{
		new_vel.x = 0;
		new_accel.x = 0;
		new_vel.y = 0;
		new_accel.y = 0;
	}
	a->setPosition(new_pos.x, new_pos.y);
	a->setVelocity(new_vel.x, new_vel.y);
	a->setAcceleration(new_accel.x, new_accel.y);
}