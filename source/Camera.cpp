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
		rotation_type = EULER;
	}

	Camera::Camera(float r)
	{
		firstMouseMovement = true;
		T = mat4::identityMatrix();
		T.data[2][3] = -r;
		R = mat4::identityMatrix();
		viewMatrix = T * R;
		q = qtrn();
		rotation_type = QUATERNION;
	}
	
	void Camera::resetCamera(float r)
	{
		firstMouseMovement = true;
		T = mat4::identityMatrix();
		T.data[2][3] = -r;
		R = mat4::identityMatrix();
		viewMatrix = T * R;
		q = qtrn();
		rotation_type = QUATERNION;

	}
	void Camera::init(GLuint vbo, GLsizeiptr datasize, GLuint UBO_id)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, vbo);
		{
			glBufferData(GL_UNIFORM_BUFFER, datasize * 2, 0, GL_STREAM_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, UBO_id, vbo);
		}
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	mat4& Camera::getViewMatrix()
	{
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

		

		if (rotation_type == EULER)
		{
			xoffset *= 0.003f;
			yoffset *= -0.003f;
			mat4 matPitch = mat4::rotationY(xoffset);
			mat4 matYaw = mat4::rotationX(yoffset);
			R = matPitch * matYaw * R;
		}
		else if (rotation_type == QUATERNION)
		{
			xoffset *= 0.3f;
			yoffset *= -0.3f;
			qtrn qx = qtrn();
			qtrn qy = qtrn();
			qx = qx.qFromAngleAxis(xoffset, vec4(0.0f, 1.0f, 0.0f, 1.0f));
			qy = qy.qFromAngleAxis(yoffset, vec4(1.0f, 0.0f, 0.0f, 1.0f));
			q = qx * qy * q;
			mat4 matRot = qRotationMatrix(q);
			R = matRot;
		}

		viewMatrix = T * R;

	}
	void egn::Camera::scrollCallBack(float offset) {
		T.data[2][3] += offset;
		viewMatrix = T * R;
	}

	void Camera::changeRotationType()
	{
		if (rotation_type == EULER)
		{
			rotation_type = QUATERNION;
			std::cout << "QUATERNION MODE" << std::endl;
		}
		else if (rotation_type == QUATERNION)
		{
			rotation_type = EULER;
			std::cout << "EULER MODE" << std::endl;
		}
	}
}

