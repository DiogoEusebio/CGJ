#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Quaternion.h"

namespace egn {
	class Camera
	{
	protected:
		mat4 viewMatrix, projectionMatrix, orthographicMatrix, perspectiveMatrix;
		enum TYPE { PERSPECTIVE, ORTHOGRAPHIC };
		enum ROTATION_TYPE {EULER, QUATERNION};
		TYPE type;
		ROTATION_TYPE rotation_type;
		bool firstMouseMovement;
		float lastX, lastY;
		mat4 T, R;
		qtrn q;
	public:
		vec3 position, front, up, right;

	public:
		Camera();
		Camera(float r);
		void resetCamera(float r);
		void init(GLuint vbo, GLsizeiptr datasize, GLuint UBO_id);
		void OrthographicProjectionMatrix(float left, float right, float bot, float top, float near, float far);
		void PerspectiveProjectionMatrix(float fovy, float aspect, float nearZ, float farZ);
		mat4& getViewMatrix();
		mat4& getOrthographicMatrix();
		mat4& getPerspectiveMatrix();
		mat4& getProjectionMatrix();
		void addTranslation(vec3 v);
		void setFirstMouseMovement(bool b);
		void switchProjectionMatrix();
		void mouseCallBack(float xpos, float ypos);
		void scrollCallBack(float offset);
		void changeRotationType();
	};
}