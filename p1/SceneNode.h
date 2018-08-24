#ifndef __SceneNode_h
#define __SceneNode_h

#include "core/SharedObject.h"
#include <string>

namespace cg
{ // begin namespace cg

class SceneNode: public SharedObject
{
public:
  virtual ~SceneNode() = default;

  auto name() const
  {
    return _name.c_str();
  }

  void setName(const char* format, ...);

protected:
  SceneNode() = default;

  SceneNode(const char* name):
    _name{name}
  {
    // do nothing
  }

private:
  std::string _name;

}; // SceneNode

} // end namespace cg

#endif // __SceneNode_h
