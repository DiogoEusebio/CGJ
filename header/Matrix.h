#pragma once
#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <math.h>
#include "Constants.h"
#include "Vector.h"

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
		mat2& operator *= (const vec2& v);
		friend mat2 operator + (const mat2& m0, const mat2& m1);
		friend mat2 operator + (float k, const mat2& m);
		friend mat2 operator + (const mat2& m, float k);
		friend mat2 operator + (const mat2& m, const vec2 v);
		friend mat2 operator + (const vec2 v, const mat2& m);
		friend mat2 operator - (const mat2& m0, const mat2& m1);
		friend mat2 operator - (float, const mat2& m);
		friend mat2 operator - (const mat2& m, float);
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
		mat3& operator *= (const vec3& v);
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
		friend mat3 operator * (const mat3& m, const vec3& v);
		friend mat3 operator * (const vec3& v, const mat3& m);
		friend bool operator == (const mat3& m0, const mat3& m1);
		friend bool operator != (const mat3& m0, const mat3& m1);
	};
};
#endif
