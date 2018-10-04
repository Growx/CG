//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2018 Orthrus Group.                               |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: Camera.cpp
// ========
// Source file for camera.
//
// Author(s): Paulo Pagliosa (and your name)
// Last revision: 15/09/2018

#include "Camera.h"

namespace cg
{ // begin namespace cg


//////////////////////////////////////////////////////////
//
// Camera implementation
// ======
uint32_t Camera::_nextId;

inline const char*
Camera::defaultName()
{
  static char name[16];

  snprintf(name, sizeof name, "Camera %d", ++_nextId);
  return name;
}

Camera::Camera():
  NameableObject{defaultName()}
{
  setDefaultView();
}

void
Camera::setPosition(const vec3f& value)
//[]---------------------------------------------------[]
//|  Set the camera's position                          |
//|                                                     |
//|  Setting the camera's position will not change      |
//|  neither the direction of projection nor the        |
//|  distance between the position and the focal point. |
//|  The focal point will be moved along the direction  |
//|  of projection.                                     |
//[]---------------------------------------------------[]
{
  // TODO
	if (_position != value)
	{
		_position = value;
		_focalPoint = _position + _eulerAngles * _distance;
	}
}

void
Camera::setEulerAngles(const vec3f& value)
{
  // TODO
	direction.x = cos(toRadians3(value)) * cos(toRadians3(value);
	direction.y = sin(math::radians(pitch));
	direction.z = cos(math::radians(pitch)) * sin(glm::radians(yaw));
}

void
Camera::setRotation(const quatf& value)
{
  // TODO
	if (!math::isZero(value))
	{
		const mat4f r = mat4f::rotation(value, _focalPoint);

		Transform(_position, r);
	}
}

void
Camera::setProjectionType(ProjectionType value)
//[]---------------------------------------------------[]
//|  Set the camera's projection type                   |
//[]---------------------------------------------------[]
{
  // TODO
	if (_projectionType != value)
	{
		_projectionType = value;
	}
}

void
Camera::setDistance(float value)
//[]---------------------------------------------------[]
//|  Set the camera's distance                          |
//|                                                     |
//|  Setting the distance between the position and      |
//|  focal point will move the focal point along the    |
//|  direction of projection.                           |
//[]---------------------------------------------------[]
{
  // TODO
	if (!math::isEqual(_distance, value))
	{
		_focalPoint = _distance + value;
	}
}

void
Camera::setViewAngle(float value)
//[]---------------------------------------------------[]
//|  Set the camera's view angle                        |
//[]---------------------------------------------------[]
{
  // TODO
	
	if (!math::isEqual(_viewAngle, value))
	{
		_viewAngle = dMin(dMax(value, MIN_ANGLE), MAX_ANGLE);
		if (projectionType == Perspective)
			viewModified = true;
	}
}

void
Camera::setHeight(float value)
//[]---------------------------------------------------[]
//|  Set the camera's view_height                       |
//[]---------------------------------------------------[]
{
  // TODO
	if (!math::isEqual(_height, value))
	{
		_height = dMax(value, MIN_HEIGHT);
		if (_projectionType == Parallel)
			viewModified = true;
	}
}

void
Camera::setAspectRatio(float value)
//[]---------------------------------------------------[]
//|  Set the camera's aspect ratio                      |
//[]---------------------------------------------------[]
{
  // TODO
	if (!math::isEqual(_aspectRatio, value))
	{
		_aspectRatio = dMax(value, MIN_ASPECT);
	}
}

void
Camera::setClippingPlanes(float F, float B)
//[]---------------------------------------------------[]
//|  Set the distance of the clippling planes           |
//[]---------------------------------------------------[]
{
  // TODO

	if (_F > _B)
	{
		Real temp = F;

		F = B;
		B = temp;
	}
	if (_F < MIN_FRONT_PLANE)
		_F = MIN_FRONT_PLANE;
	if ((_B - _F) < MIN_DEPTH)
		_B = _F + MIN_DEPTH;
	if (!math::isEqual(this->_F, _F) || !math::isEqual(this->_B, _B))
	{
		this->_F = _F;
		this->_B = _B;
	}
}

void
Camera::rotateYX(float ay, float ax, bool orbit)
//[]---------------------------------------------------[]
//|  Rotate YX                                          |
//|                                                     |
//|  If orbit is true, then it is a composition of an   |
//|  azimuth of ay with an elevation of ax, in this     |
//|  order. Otherwise, it is a composition of a yaw of  |
//|  ay with a pitch of ax, in this order.              |
//[]---------------------------------------------------[]
{
  // TODO
	const quatf qy(ay, ax);
	vec3f u = directionOfProjection.cross(viewUp);

	u = qy.rotate(u).versor();

	const quatf qx(ax, u);

	viewUp = qx.rotate(viewUp).versor();
	directionOfProjection = viewUp.cross(u).versor();
	_position = focalPoint - directionOfProjection * distance;
	viewModified = true;
}

void
Camera::zoom(float zoom)
//[]---------------------------------------------------[]
//|  Zoom                                               |
//|                                                     |
//|  Change the view angle (or height) of the camera so |
//|  that more or less of a scene occupies the view     |
//|  window. A value > 1 is a zoom-in. A value < 1 is   |
//|  zoom-out.                                          |
//[]---------------------------------------------------[]
{
  // TODO
	if (zoom > 0)
		if (_projectionType == Perspective)
			setViewAngle(_viewAngle / zoom);
		else
			setHeight(_height / zoom);
}

void
Camera::translate(float dx, float dy, float dz)
//[]---------------------------------------------------[]
//|  Translate the camera                               |
//[]---------------------------------------------------[]
{
  // TODO
}

void
Camera::setDefaultView(float aspect)
//[]---------------------------------------------------[]
//|  Set default view                                   |
//[]---------------------------------------------------[]
{
  _position.set(0.0f, 0.0f, 10.0f);
  _eulerAngles.set(0.0f);
  _rotation = quatf::identity();
  _focalPoint.set(0.0f, 0.0f, 0.0f);
  _distance = 10.0f;
  _aspectRatio = aspect;
  _projectionType = Perspective;
  _viewAngle = 60.0f;
  _height = 10.0f;
  _F = 0.01f;
  _B = 1000.0f;
  // TODO: update view and projection matrices.

}
} // end namespace cg
