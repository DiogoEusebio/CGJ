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

	};
};
#endif
