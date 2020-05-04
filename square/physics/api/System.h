#pragma once
#include <memory>
#include "AABBCollider.h"

namespace physics {
namespace api {

class System {
public:
	virtual std::shared_ptr<AABBCollider> newAABBCollider() = 0;
};

} // namespace api
} // namespace physics