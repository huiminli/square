#pragma once
#ifndef SQUARE_SCENE_H 
#define SQUARE_SCENE_H 

#include <list>
#include "Entity.h"
#include "EntityFactory.h"
#include "PhysicsScene.h"
#include "RendererScene.h"

class Scene : public EntityFactory {
public:
	void initialize() { renderer.initialize(); }
	void update(float dt);
	void render() { renderer.render(); };
	void addEntity(std::unique_ptr<Entity> entity) { entities.push_back(std::move(entity)); }

	std::shared_ptr<AABBCollider> newAABBCollider() override { return physics.newAABBCollider(); }
	Camera* getCamera() override { return renderer.getCamera(); }
	std::shared_ptr<RenderableSprite> newRenderableSprite() override { return renderer.newRenderableSprite(); }

private:
	std::list<std::unique_ptr<Entity>> entities;
	RendererScene renderer;
	PhysicsScene physics;
};

#endif // SQUARE_SCENE_H 