#ifndef __Transform_h
#define __Transform_h

#include "Component.h"
#include "math/Vector3.h"

namespace cg
{ // begin namespace cg

class Transform final: public Component
{
public:
  vec3f position{0.0f};
  vec3f rotation{0.0f};
  vec3f scale{1.0f};

  Transform():
    Component{"Transform"}
  {
    // do nothing
  }

}; // Transform

} // end namespace cg

#endif // __Transform_h
