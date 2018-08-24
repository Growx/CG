#include "SceneNode.h"
#include <cstdarg>
#include <cstdio>

namespace cg
{ // begin namespace cg

void
SceneNode::setName(const char* format, ...)
{
  const int bufferSize{128};
  char buffer[bufferSize];
  va_list args;

  va_start(args, format);
  std::vsnprintf(buffer, bufferSize, format, args);
  _name = buffer;
}

} // end namespace cg
