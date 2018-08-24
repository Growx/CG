#ifndef __Primitive_h
#define __Primitive_h

#include "Component.h"
#include "graphics/GLMeshArray.h"

namespace cg
{ // begin namespace cg

class Primitive: public Component
{
public:
  Primitive(GLMeshArray* mesh):
    Component{"Primitive"},
    _mesh{mesh}
  {
    // do nothing
  }

  ~Primitive() override
  {
    delete _mesh;
  }

  auto mesh() const
  {
    return _mesh;
  }

private:
  GLMeshArray * _mesh;

}; // Primitive

} // end namespace cg

#endif // __Primitive_h
