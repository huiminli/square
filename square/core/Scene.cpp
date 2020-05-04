#include "stdafx.h"
#include "Scene.h"

namespace core {
	using std::copysign;
	using std::fabs;
	using std::max;
	using std::min;

	void Scene::update(float dt)
	{
		for (auto& entity : entities) {
			entity->update(dt);
		}

		physics.processCollision(dt);
	}

} // namespace core
