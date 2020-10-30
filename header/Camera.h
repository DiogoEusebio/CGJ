#pragma once
#include "Vector.h"
#include "Matrix.h"

namespace egn {
	class Camera
	{
	public:
		mat4 viewMatrix, orthographicMatrix, perspectiveMatrix;
		vec3 eye, center, up;

	public:
		Camera();
		void ViewMatrix(const vec3& eye, const vec3& center, const vec3& up);
		void OrthographicProjectionMatrix(float left, float right, float bot, float top, float near, float far);
		void PerspectiveProjectionMatrix(float fovy, float aspect, float nearZ, float farZ);
		mat4& getViewMatrix();
		mat4& getOrthographicMatrix();
		mat4& getPerspectiveMatrix();
	};
}