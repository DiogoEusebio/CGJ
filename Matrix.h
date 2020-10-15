#pragma once
#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <math.h>
#include "Constants.h"

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
	};
	struct mat3 {

	};
};
#endif
