// Debugginh extensions to GLM library.

#pragma once
#ifndef GLM_EXT_H 
#define GLM_EXT_H 

#include <glm/glm.hpp>
#include <iostream>

namespace glm {
std::ostream & operator << (std::ostream &out, const glm::vec2 &v);
} // namespace glm

#endif // GLM_EXT_H