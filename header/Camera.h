#pragma once
#include "Vector.h"
#include "Matrix.h"

namespace egn {
	class Camera
	{
	protected:
		mat4 viewMatrix, projectionMatrix, orthographicMatrix, perspectiveMatrix;
		enum TYPE { PERSPECTIVE, ORTHOGRAPHIC };
		TYPE type;
		bool firstMouseMovement;
		float lastX, lastY;
		mat4 T, R;
	public:
		vec3 eye, center, up;

	public:
		Camera();
		void ViewMatrix(const vec3& eye, const vec3& center, const vec3& up);
		void OrthographicProjectionMatrix(float left, float right, float bot, float top, float near, float far);
		void PerspectiveProjectionMatrix(float fovy, float aspect, float nearZ, float farZ);
		mat4& getViewMatrix();
		mat4& getOrthographicMatrix();
		mat4& getPerspectiveMatrix();
		mat4& getProjectionMatrix();
		vec3& getCenter();
		vec3& getEye();
		void setFirstMouseMovement(bool b);
		void switchProjectionMatrix();
		void mouseCallBack(float xpos, float ypos);
	};
}