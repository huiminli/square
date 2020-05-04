#include "stdafx.h"
#include "Player.h"

namespace game {

	using std::copysign;
	using std::fabs;
	using std::max;
	using std::min;

	namespace {
		const float maxWalkVelocity = 5.0f;
		const float airAcceleration = 20.0f;
		const float walkAcceleration = 200.0f;
		const float jumpVelocity = 20.0f;
		const float cameraVelocity = 3.0f;

		const glm::vec2 player_size(0.8f, 0.8f);
		// Make the collision box slightly smaller so that going through narrow
		// passages is easier.
		const glm::vec2 collision_box_offset(0.1f, 0.1f);
	}

	Player::Player(core::EntityFactory& ef, const glm::vec2& position) : starting_position_(position)
	{
		camera = ef.getCamera();

		sprite = ef.newRenderableSprite();
		sprite->position = position;
		sprite->tileIndex = 60;

		collider = ef.newAABBCollider();
		collider->position_min = position + collision_box_offset;
		collider->size = player_size;
		collider->velocity = glm::vec2(0.0f);
		collider->fixed = false;
	}

	// TODO: put the pressed control into a struct
	void Player::update(float dt)
	{
		// Sprite update.
		sprite->position = collider->position_min - collision_box_offset;

		// Collider update.
		bool rightPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT] != 0;
		bool leftPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT] != 0;
		bool upPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP] != 0;
		bool downPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_DOWN] != 0;
		bool onGround = collider->bottom != nullptr;

		// Walking.
		collider->velocity.x += (rightPressed - leftPressed) * (onGround ? walkAcceleration : airAcceleration) * dt;
		collider->velocity.x = max(-maxWalkVelocity, min(maxWalkVelocity, collider->velocity.x));
		collider->velocity.y = (onGround && upPressed) ? jumpVelocity : collider->velocity.y;

		// Flying.
		// collider->velocity.x = (rightPressed - leftPressed) * 5;
		// collider->velocity.y = (upPressed - downPressed) * 5;

		// Camera update.
		bool wPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W] != 0;
		bool sPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S] != 0;
		bool aPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A] != 0;
		bool dPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D] != 0;
		camera->position.x += (dPressed - aPressed) * cameraVelocity * dt;
		camera->position.y += (wPressed - sPressed) * cameraVelocity * dt;

		// Morph blocks.
		bool spacePressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_SPACE] != 0;
		if (spacePressed) {
			collider->position_min = starting_position_;
		}
	}

} // namespace game
