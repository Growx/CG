#ifndef __SceneObject_h
#define __SceneObject_h

#include "SceneNode.h"
#include "Transform.h"

namespace cg
{ // begin namespace cg

class SceneObject: public SceneNode
{
public:
  bool visible{true};

  SceneObject(const char* name):
    SceneNode{name}
  {
    // do nothing
  }

  auto parent() const
  {
    return _parent;
  }

  void setParent(SceneObject* parent);

  auto transform()
  {
    return &_transform;
  }

private:
  SceneObject* _parent{};
  Transform _transform;

}; // SceneObject

} // end namespace cg

#endif // __SceneObject_h
