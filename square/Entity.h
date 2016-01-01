#pragma once
#ifndef SQUARE_ENTITY_H
#define SQUARE_ENTITY_H

class Entity {
public:
	virtual void update(float dt) = 0;
};

#endif // SQUARE_ENTITY_H