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
Camera::updateFocalPoint(vec3f focalpoint,vec3f position, float distance) {
	//mat3f r = mat3f{ _rotation };
	//_focalPoint = _position - r[2] * _distance;
	//_focalPoint = position + (focalpoint - position) * (float)(1 / distance) * distance;
	_focalPoint = position - (position - focalpoint).versor() * distance;
	viewMatrix(position, _rotation);
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
	_position = value;
	updateFocalPoint(_focalPoint, _position, _distance);
	viewMatrix(_position, _rotation);
	inverseMatrix(_matrix);
}

void
Camera::setEulerAngles(const vec3f& value)
{
  // TODO
	_eulerAngles = value;


	_rotation = quatf::eulerAngles(_eulerAngles);
	viewMatrix(_position, _rotation);
}

void
Camera::setRotation(const quatf& value)
{
  // TODO
	_rotation = value;
	updateFocalPoint(_focalPoint, _position, _distance);
	viewMatrix(_position, _rotation);
	
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
		if (value > MIN_DISTANCE)
			_distance = value;
		else
			_distance = MIN_DISTANCE;
		updateFocalPoint(_focalPoint, _position, _distance);
}

void
Camera::setViewAngle(float value)
//[]---------------------------------------------------[]
//|  Set the camera's view angle                        |
//[]---------------------------------------------------[]
{
  // TODO
		float temp;

		if (value > MIN_ANGLE)
			temp = value;
		else
			temp = MIN_ANGLE;

		if (temp < MAX_ANGLE)
			_viewAngle = temp;
		else
			_viewAngle = MAX_ANGLE;

		projectionMatrix(_viewAngle, _aspectRatio, _F, _B);
	
}

void
Camera::setHeight(float value)
//[]---------------------------------------------------[]
//|  Set the camera's view_height                       |
//[]---------------------------------------------------[]
{
  // TODO
		if (value > MIN_HEIGHT)
			_height = value;
		else
			_height = MIN_HEIGHT;
		projectionMatrix(_viewAngle, _aspectRatio, _F, _B);
}

void
Camera::setAspectRatio(float value)
//[]---------------------------------------------------[]
//|  Set the camera's aspect ratio                      |
//[]---------------------------------------------------[]
{
  // TODO
		if (value > MIN_ASPECT)
			_aspectRatio = value;
		else
			_aspectRatio = MIN_ASPECT;
		projectionMatrix(_viewAngle, _aspectRatio, _F, _B);
}

void
Camera::setClippingPlanes(float F, float B)
//[]---------------------------------------------------[]
//|  Set the distance of the clippling planes           |
//[]---------------------------------------------------[]
{
  // TODO
	if (F > MIN_FRONT_PLANE && _B - F > MIN_DEPTH && !math::isEqual(_F, F))
	{
		_F = F;
	}

	if (F > B)
	{
		float temp = F;

		F = B;
		B = temp;
	}
	if (F < MIN_FRONT_PLANE)
		_F = MIN_FRONT_PLANE;
	if ((B - F) < MIN_DEPTH)
		_B = F + MIN_DEPTH;
	if (!math::isEqual(_F, F) || !math::isEqual(_B, B))
	{
		_F = F;
		_B = B;
	}
	projectionMatrix(_viewAngle, _aspectRatio, _F, _B);
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
	auto d = mat3f{ _rotation };

	if (orbit) {
		
		//azimuth

		mat4f s = mat4f::rotation(_focalPoint, ay, vec3f::up());
		_position = s.transform3x4(_position);
		viewMatrix(_position, _rotation);

		//elevation
		mat4f t = mat4f::rotation(-d[2].cross(vec3f::up()), ax, vec3f::up());
		_position = t.transform3x4(_position);
		viewMatrix(_position, _rotation);
	
	}

	else {
		//yaw
		mat4f r = mat4f::rotation(_position, ay, vec3f::up());
		_focalPoint = r.transform3x4(_focalPoint);
		updateFocalPoint(_focalPoint, _position, _distance);
		viewMatrix(_position, _rotation);

		//pitch
		mat4f u = mat4f::rotation(-d[2].cross(vec3f::up()), ax, _position);
		_focalPoint = u.transform3x4(_focalPoint);
		updateFocalPoint(_focalPoint, _position, _distance);
		viewMatrix(_position, _rotation);
	}

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
	if (zoom > 0) {
		if (_projectionType == Perspective)
			setViewAngle(_viewAngle / zoom);
		else
			setHeight(_height / zoom);
	}
}

void
Camera::translate(float dx, float dy, float dz)
//[]---------------------------------------------------[]
//|  Translate the camera                               |
//[]---------------------------------------------------[]
{
  // TODO
		_position.x += dx;
		_position.y += dy;
		_position.z -= dz;

	viewMatrix(_position,_rotation);
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
 // _matrix = mat4f::lookAt(_position, _focalPoint, vec3f::up());
  //_matrix.inverse(_inverseMatrix);
  //_projectionMatrix = mat4f::perspective(_viewAngle, _aspectRatio, _F, _B);
  inverseMatrix(_matrix);
  projectionMatrix(_viewAngle, _aspectRatio, _F, _B);
}
void
Camera::viewMatrix(const vec3f position, quatf rotation) 
{

	auto r = mat3f{ rotation };
	_matrix[0].set(r[0].x, r[1].x, r[2].x);
	_matrix[1].set(r[0].y, r[1].y, r[2].y);
	_matrix[2].set(r[0].z, r[1].z, r[2].z);
	_matrix[3][0] = -(position.dot(r[0]));
	_matrix[3][1] = -(position.dot(r[1]));
	_matrix[3][2] = -(position.dot(r[2]));
	_matrix[3][3] = 1.0f;

	_focalPoint = position - r[2] * _distance;
}
void
Camera::inverseMatrix(mat4f& matrix) 
{
	_matrix.inverse(_inverseMatrix);
}

void
Camera::projectionMatrix(float viewAngle, float aspectRatio, float F, float B) 
{
	float left;
	float right;
	float bottom;
	float top;
	float width;

	if (_projectionType == Perspective)
	{
		_projectionMatrix = mat4f::perspective(viewAngle, aspectRatio, F, B);
		_matrix = mat4f::lookAt(_position, _focalPoint, vec3f::up());
		inverseMatrix(_matrix);
	}
	else {
		width = aspectRatio * _height;
		left = -(width / 2);
		right = (width / 2);
		bottom = -(_height / 2);
		top = (_height / 2);

		_projectionMatrix = mat4f::ortho(left, right, bottom, top, _F, _B);
	}
}
} // end namespace cg
