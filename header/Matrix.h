#pragma once
#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <math.h>
#include "Constants.h"
#include "Vector.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace egn
{
	struct mat3;
	struct mat4;
	//column major format

	struct mat2 {
		float data[2][2];

		mat2();
		mat2(const float k);
		mat2(const float k0, const float k1, const float k2, const float k3);
		mat2(const mat2& m);
		friend std::ostream& operator<<(std::ostream& os, const mat2& m);
		void clean();
		float determinant() const;
		mat2& operator = (const mat2& m);
		friend mat2 transpose(const mat2& m);
		friend mat2 inverse(const mat2& m);
		mat2& operator += (const mat2& m);
		mat2& operator += (const float k);
		mat2& operator += (const vec2 v);
		mat2& operator -= (const mat2& m);
		mat2& operator -= (const float k);
		mat2& operator -= (const vec2 v);
		mat2& operator *= (const float k);
		mat2& operator *= (const mat2& m);
		friend mat2 operator + (const mat2& m0, const mat2& m1);
		friend mat2 operator + (float k, const mat2& m);
		friend mat2 operator + (const mat2& m, float k);
		friend mat2 operator + (const mat2& m, const vec2 v);
		friend mat2 operator + (const vec2 v, const mat2& m);
		friend mat2 operator - (const mat2& m0, const mat2& m1);
		friend mat2 operator - (float, const mat2& m);
		friend mat2 operator - (const mat2& m, float);
		friend mat2 operator - (const mat2& m, const vec2 v);
		friend mat2 operator - (const vec2 v, const mat2& m);
		friend mat2 operator * (const mat2& m0, const mat2& m1);
		friend mat2 operator * (const mat2& m, const float k);
		friend mat2 operator * (const float k, const mat2& m);
		friend vec2 operator * (const mat2& m, const vec2 v);
		friend vec2 operator * (const vec2 v, const mat2& m1);
		friend bool operator == (const mat2& m0, const mat2& m1);
		friend bool operator != (const mat2& m0, const mat2& m1);
		mat2 static identityMatrix();
	};

	struct mat3 {
		float data[3][3];

		mat3();
		mat3(const float k);
		mat3(const float k1, const float k2, const float k3, const float k4, const float k5, const float k6, const float k7, const float k8, const float k9);
		mat3(const mat3& m);
		friend std::ostream& operator<<(std::ostream& os, const mat3& m);
		void clean();
		float determinant() const;
		mat3& operator = (const mat3& m);
		friend mat3 transpose(const mat3& m);
		friend mat3 inverse(const mat3& m);
		mat3& operator += (const mat3& m);
		mat3& operator += (const vec3& v);
		mat3& operator += (const float k);
		mat3& operator -= (const mat3& m);
		mat3& operator -= (const vec3& v);
		mat3& operator -= (const float k);
		mat3& operator *= (const mat3& m);
		mat3& operator *= (const float k);
		friend mat3 operator + (const mat3& m0, const mat3& m1);
		friend mat3 operator + (const mat3& m, const float k);
		friend mat3 operator + (const float k, const mat3& m);
		friend mat3 operator + (const mat3& m, const vec3& v);
		friend mat3 operator + (const vec3& v, const mat3& m);
		friend mat3 operator - (const mat3& m0, const mat3& m1);
		friend mat3 operator - (const mat3& m, const float k);
		friend mat3 operator - (const float k, const mat3& m);
		friend mat3 operator - (const mat3& m, const vec3& v);
		friend mat3 operator - (const vec3& v, const mat3& m);
		friend mat3 operator * (const mat3& m0, const mat3& m1);
		friend mat3 operator * (const mat3& m, const float k);
		friend mat3 operator * (const float k, const mat3& m);
		friend vec3 operator * (const mat3& m, const vec3& v);
		friend vec3 operator * (const vec3& v, const mat3& m);
		friend bool operator == (const mat3& m0, const mat3& m1);
		friend bool operator != (const mat3& m0, const mat3& m1);
		mat3 static dualMatrix(const vec3& v);
		mat3 static identityMatrix();
	};

	struct mat4 {
		float data[4][4];

		mat4();
		mat4(const float k);
		mat4(const float k1, const float k2, const float k3, const float k4, const float k5, const float k6, const float k7, const float k8, const float k9, const float k10, const float k11, const float k12, const float k13, const float k14, const float k15, const float k16);
		mat4(const mat4& m);
		friend std::ostream& operator<<(std::ostream& os, const mat4& m);
		void clean();
		mat4& operator = (const mat4& m);
		mat4& operator += (const mat4& m);
		mat4& operator += (const vec4& v);
		mat4& operator += (const float k);
		mat4& operator -= (const mat4& m);
		mat4& operator -= (const vec4& v);
		mat4& operator -= (const float k);
		mat4& operator *= (const mat4& m);
		mat4& operator *= (const float k);
		friend mat4 operator + (const mat4& m0, const mat4& m1);
		friend mat4 operator + (const mat4& m, const float k);
		friend mat4 operator + (const float k, const mat4& m);
		friend mat4 operator + (const mat4& m, const vec4& v);
		friend mat4 operator + (const vec4& v, const mat4& m);
		friend mat4 operator - (const mat4& m0, const mat4& m1);
		friend mat4 operator - (const mat4& m, const float k);
		friend mat4 operator - (const float k, const mat4& m);
		friend mat4 operator - (const mat4& m, const vec4& v);
		friend mat4 operator - (const vec4& v, const mat4& m);
		friend mat4 operator * (const mat4& m0, const mat4& m1);
		friend mat4 operator * (const mat4& m, const float k);
		friend mat4 operator * (const float k, const mat4& m);
		friend vec4 operator * (const mat4& m, const vec4& v);
		friend vec4 operator * (const vec4& v, const mat4& m);
		friend bool operator == (const mat4& m0, const mat4& m1);
		friend bool operator != (const mat4& m0, const mat4& m1);
		mat4 static scaling(float sx, float sy, float sz, float sw);
		mat4 static translation(float tx, float ty, float tz);
		mat4 static rotationX(float x);
		mat4 static rotationY(float y);
		mat4 static rotationZ(float z);
		mat4 static identityMatrix();
		GLfloat* convertToGL(GLfloat* gl);
	};
};
#endif
