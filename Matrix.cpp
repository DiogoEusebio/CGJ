#include "../header/Matrix.h"

namespace egn {
	mat2::mat2()
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] = 0.0f;
		}
	}
	mat2::mat2(const float k)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] = k;
		}
	}
	mat2::mat2(const float k0, const float k1, const float k2, const float k3)
	{
		this->data[0][0] = k0;
		this->data[1][0] = k1;
		this->data[0][1] = k2;
		this->data[1][1] = k3;
	}
	mat2::mat2(const mat2& m)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] = m.data[i][j];
		}
	}
	void mat2::clean()
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				if (fabs(data[i][j]) < THRESHOLD) data[i][j] = 0.0f;
		}
	}
	float mat2::determinant() const {
		return data[0][0] * data[1][1] - data[0][1] * data[1][0];
	}
	mat2& mat2::operator=(const mat2& m)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] = m.data[i][j];
		}
		return *this;
	}
	mat2 transpose(const mat2& m)
	{
		return mat2(m.data[0][0], m.data[0][1], m.data[1][0], m.data[1][1]);
	}
	mat2 inverse(const mat2& m) 
	{
		float det = m.determinant();
		return mat2(m.data[1][1] / det, -m.data[1][0] / det, -m.data[0][1] / det, m.data[0][0] / det);
	}
	std::ostream& operator<<(std::ostream& os, const mat2& m)
	{
		os << "[ " << m.data[0][0] << " , " << m.data[0][1] << std::endl
			<< "  " << m.data[1][0] << " , " << m.data[1][1] << " ]" << std::endl;
		return os;
	}

};