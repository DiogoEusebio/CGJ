#include "../header/Camera.h"

#include "../header/Constants.h"

namespace egn {

	Camera::Camera()
	{
		firstMouseMovement = true;
	}

	void Camera::ViewMatrix(const vec3& eye, const vec3& center, const vec3& up)
	{	
		this->center = center;
		this->eye = eye;
		this->up = up;
		vec3 view = center - eye;
		vec3 v = vec3::normalize(view);
		//std::cout << "v = " << v << std::endl;
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
	mat4& Camera::getProjectionMatrix()
	{
		return projectionMatrix;
	}
	vec3& Camera::getEye()
	{
		return eye;
	}
	vec3& Camera::getCenter()
	{
		return center;
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

	void egn::Camera::addTranslation(vec3 v) {

		T.data[0][3] += v.x;
		T.data[1][3] += v.y;
		T.data[2][3] += v.z;
		std::cout << T << std::endl << R << std::endl;
		mat4 M = R * T;
		viewMatrix = M;

	}
	void egn::Camera::mouseCallBack(float xpos, float ypos)
	{
		if (firstMouseMovement)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouseMovement = false;
			std::cout << "I'm here once" << std::endl;
		}

		float xoffset = xpos - lastX;
		float yoffset = ypos - lastY;
		lastX = xpos;
		lastY = ypos;
		
		xoffset *= 0.005;
		yoffset *= -0.005;

		R = R * mat4::rotationY(xoffset) * mat4::rotationX(yoffset);
		/*
		vec3 view = vec3(center);
		view -= eye;
		vec3 v = vec3::normalize(view);
		//std::cout << "v = " << v << std::endl;
		vec3 side = vec3::cross(v, up);
		vec3 s = vec3::normalize(side);
		vec3 u = vec3::cross(s, v);
		s.clean(); u.clean();
		std::cout << "s = " << s << "     u = " << u <<std::endl;
		center = center * mat3::rotationMatrix(yoffset,s) * mat3::rotationMatrix(xoffset,u);
		up = vec3(0, -center.x, center.y);

		view = vec3(center);
		view -= eye;
		v = vec3::normalize(view);
		//std::cout << "v = " << v << std::endl;
		side = vec3::cross(v, up);
		s = vec3::normalize(side);
		u = vec3::cross(s, v);
		R = mat4(s.x, s.y, s.z, 0.0f,
			u.x, u.y, u.z, 0.0f,
			-v.x, -v.y, -v.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		T = mat4(1.0f, 0.0f, 0.0f, -eye.x,
			0.0f, 1.0f, 0.0f, -eye.y,
			0.0f, 0.0f, 1.0f, -eye.z,
			0.0f, 0.0f, 0.0f, 1.0f);
		*/
		mat4 M = R * T;
		viewMatrix = M;

		//std::cout << R << std::endl;
	}
}

