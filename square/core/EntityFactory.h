#pragma once
#include "../physics/api/System.h"
#include "../graphics/api/System.h"

namespace core {

class EntityFactory 
	: public physics::api::System,
	public graphics::api::System
{};

} // namespace core
