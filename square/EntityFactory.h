#pragma once
#ifndef SQUARE_ENTITY_FACTORY
#define SQUARE_ENTITY_FACTORY

#include "PhysicsApi.h"
#include "RendererApi.h"

class EntityFactory 
	: public PhysicsFactory,
	public RendererFactory
{};

#endif // SQUARE_ENTITY_FACTORY
