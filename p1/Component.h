#ifndef __Component_h
#define __Component_h

#include "core/SharedObject.h"

namespace cg
{ // begin namespace cg

class Component: public SharedObject
{
public:
  auto typeName() const
  {
    return _typeName;
  }

protected:
  Component(const char* typeName):
    _typeName{typeName}
  {
    // do nothing
  }

private:
  const char* _typeName;

}; // Component

} // end namespace cg

#endif // __Component_h
