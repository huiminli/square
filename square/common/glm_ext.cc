#include "glm_ext.h"

namespace glm {

std::ostream & operator << (std::ostream &out, const glm::vec2 &v)
{
  out << "x=" << v.x << " y=" << v.y;
  return out;
}

} // namespace glm
