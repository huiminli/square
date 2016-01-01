#include "stdafx.h"
#include "Scene.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

void Scene::update(float dt)
{
	physics.processCollision(dt);

	for (auto &entity : entities) {
		entity->update(dt);
	}
}
