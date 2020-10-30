#include "../header/Camera.h"

#include "../header/Constants.h"

namespace egn {

	Camera::Camera()
	{
	}

	void Camera::ViewMatrix(const vec3& eye, const vec3& center, const vec3& up)
	{
		vec3 view = center - eye;
		vec3 v = vec3::normalize(view);
		vec3 side = vec3::cross(v, up);
		vec3 s = vec3::normalize(side);
		vec3 u = vec3::cross(s, v);
		mat4 R = mat4(s.x, s.y, s.z, 0.0f,
			u.x, u.y, u.z, 0.0f,
			-v.x, -v.y, -v.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		mat4 T = mat4(1.0f, 0.0f, 0.0f, -eye.x,
			0.0f, 1.0f, 0.0f, -eye.y,
			0.0f, 0.0f, 1.0f, -eye.z,
			0.0f, 0.0f, 0.0f, 1.0f);
		mat4 M = R * T;
		viewMatrix = M;
	}

	void Camera::OrthographicProjectionMatrix(float left, float right, float bot, float top, float near, float far)
	{
		//does near - far instead of far - near cuz -z of openGL
		orthographicMatrix = mat4(2 / (right - left), 0, 0, (left + right) / (left - right),
					0, 2 / (top - bot), 0, (bot + top) / (bot - top),
					0, 0, 2 / (near - far), (near + far) / (near - far),
					0, 0, 0, 1);
	}

	void Camera::PerspectiveProjectionMatrix(float fovy, float aspect, float nearZ, float farZ)
	{
		float teta = fovy / 2.0f;
		float d = 1.0f / tan(teta * PI / 180);

		perspectiveMatrix = mat4(d / aspect, 0, 0, 0,
							0, d, 0, 0,
							0, 0, (nearZ + farZ) / (nearZ - farZ), 2 * farZ * nearZ / (nearZ - farZ),
							0, 0, -1.0f, 0);
	}

	mat4& Camera::getViewMatrix()
	{
		return viewMatrix;
	}

	mat4& Camera::getOrthographicMatrix()
	{
		return orthographicMatrix;
	}

	mat4& Camera::getPerspectiveMatrix()
	{
		return perspectiveMatrix;
	}

}

