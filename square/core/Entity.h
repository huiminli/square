#pragma once
namespace core {

class Entity {
public:
	virtual void update(float dt) = 0;
};

} // namespace core