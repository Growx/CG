#ifndef __Scene_h
#define __Scene_h

#include "SceneObject.h"
#include "graphics/Color.h"

namespace cg
{ // begin namespace cg

class Scene: public SceneNode
{
public:
  Color backgroundColor{Color::gray};

  Scene(const char* name):
    SceneNode{name}
  {
    // do nothing
  }

}; // Scene

} // end namespace cg

#endif // __Scene_h
