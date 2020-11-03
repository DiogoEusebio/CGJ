#include "../header/Camera.h"

#include "../header/Constants.h"

namespace egn {

	Camera::Camera()
	{
		firstMouseMovement = true;
		position = vec3(0);
		front = vec3(0);
		right = vec3(0);
		up = vec3(0);
	}

	Camera::Camera(vec3& eye, vec3& center, vec3& upvec)
	{
		firstMouseMovement = true;
		position = eye;
		front = vec3(center) - position;
		right = vec3::cross(front, upvec);
		up = upvec;
	}
	
	void Camera::resetCamera(vec3& eye, vec3& center, vec3& upvec)
	{
		firstMouseMovement = true;
		position = eye;
		front = vec3(center) - position;
		right = vec3::cross(front, upvec);
		up = upvec;
	}

	mat4& Camera::getViewMatrix()
	{
		vec3 aux = vec3(position);
		aux += front;
		return lookAt(position, aux, up);
	}
	mat4& Camera::lookAt(const vec3& eye, const vec3& center, const vec3& upvec)
	{	

		vec3 view = center - eye;
		vec3 v = vec3::normalize(view);

		vec3 side = vec3::cross(v, up);
		vec3 s = vec3::normalize(side);
		vec3 u = vec3::cross(s, v);

		R = mat4(s.x, s.y, s.z, 0.0f,
			u.x, u.y, u.z, 0.0f,
			-v.x, -v.y, -v.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		T = mat4(1.0f, 0.0f, 0.0f, -eye.x,
			0.0f, 1.0f, 0.0f, -eye.y,
			0.0f, 0.0f, 1.0f, -eye.z,
			0.0f, 0.0f, 0.0f, 1.0f);

		mat4 M = R * T;
		viewMatrix = M;
		return viewMatrix;
	}

	void Camera::OrthographicProjectionMatrix(float left, float right, float bot, float top, float near, float far)
	{
		//does near - far instead of far - near cuz -z of openGL
		orthographicMatrix = mat4(2 / (right - left), 0, 0, (left + right) / (left - right),
					0, 2 / (top - bot), 0, (bot + top) / (bot - top),
					0, 0, 2 / (near - far), (near + far) / (near - far),
					0, 0, 0, 1);

		type = ORTHOGRAPHIC;
		projectionMatrix = orthographicMatrix;
	}

	void Camera::PerspectiveProjectionMatrix(float fovy, float aspect, float nearZ, float farZ)
	{
		float teta = fovy / 2.0f;
		float d = 1.0f / tan(teta * PI / 180);

		perspectiveMatrix = mat4(d / aspect, 0, 0, 0,
							0, d, 0, 0,
							0, 0, (nearZ + farZ) / (nearZ - farZ), 2 * farZ * nearZ / (nearZ - farZ),
							0, 0, -1.0f, 0);
		type = PERSPECTIVE;
		projectionMatrix = perspectiveMatrix;
	}

	mat4& Camera::getOrthographicMatrix()
	{
		return orthographicMatrix;
	}

	mat4& Camera::getPerspectiveMatrix()
	{
		return perspectiveMatrix;
	}
	mat4& Camera::getProjectionMatrix()
	{
		return projectionMatrix;
	}

	void Camera::setFirstMouseMovement(bool b) {
		firstMouseMovement = b;
	}

	void Camera::switchProjectionMatrix()
	{
		if (type == PERSPECTIVE) {
			type = ORTHOGRAPHIC;
			projectionMatrix = orthographicMatrix;
		}
		else if (type == ORTHOGRAPHIC) {
			type = PERSPECTIVE;
			projectionMatrix = perspectiveMatrix;
		}
	}

	void egn::Camera::addTranslation(vec3 v)
	{	
		vec3 vec = vec3::normalize(v);
		if (vec.z != 0)
		{
			this->position += front * v.z;
		}
		if (vec.x != 0)
		{
			this->position += right * v.x;
		}
	}

	void egn::Camera::mouseCallBack(float xpos, float ypos)
	{	
		
		if (firstMouseMovement)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouseMovement = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = ypos - lastY;
		lastX = xpos;
		lastY = ypos;
		
		xoffset *= 0.005;
		yoffset *= -0.005;

		mat4 matPitch = mat4::rotationY(xoffset);
		mat4 matYaw = mat4::rotationX(yoffset);
		R = R * matPitch * matYaw;
		T.data[0][3] = position.x;
		T.data[1][3] = position.y;
		T.data[2][3] = position.z;
		viewMatrix = R * T;
		front = vec3::normalize(-vec3(viewMatrix.data[2][0], viewMatrix.data[2][1], viewMatrix.data[2][2]));
		right = vec3::normalize(vec3(viewMatrix.data[0][0], viewMatrix.data[0][1], viewMatrix.data[0][2]));
		up = vec3::cross(right,front);		
	}
}

