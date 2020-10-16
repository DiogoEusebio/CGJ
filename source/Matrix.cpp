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
		this->data[0][1] = k1;
		this->data[1][0] = k2;
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
	mat2& mat2::operator+=(const mat2& v)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] += v.data[i][j];
		}
		return *this;
	}
	mat2& mat2::operator+=(const float k) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] += k;
		}
		return *this;
	}
	mat2& mat2::operator+=(const vec2 v) {
		for (int i = 0; i < 2; i++) {
			data[0][i] += v.x;
			data[1][i] += v.y;
		}
		return *this;
	}
	mat2& mat2::operator-=(const mat2& v)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] = v.data[i][j];
		}
		return *this;
	}
	mat2& mat2::operator-=(const float k) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] -= k;
		}
		return *this;
	}
	mat2& mat2::operator-=(const vec2 v) {
		for (int i = 0; i < 2; i++) {
			data[0][i] -= v.x;
			data[1][i] -= v.y;
		}
		return *this;
	}

	mat2& mat2::operator*=(const float k)
	{
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				data[i][j] *= k;
		}
		return *this;
	}
	mat2& mat2::operator *= (const mat2& v)
	{
		mat2 res = mat2(*this);

		this->data[0][0] = res.data[0][0] * v.data[0][0] + res.data[1][0] * v.data[0][1];

		this->data[0][1] = res.data[0][0] * v.data[0][1] + res.data[0][1] * v.data[1][1];

		this->data[1][0] = res.data[1][0] * v.data[0][0] + res.data[1][1] * v.data[1][0];

		this->data[1][1] = res.data[1][0] * v.data[0][1] + res.data[1][1] * v.data[1][1];

		return *this;
	}
	/*mat2& operator *= (const vec2& v)
	{
		mat2 res = mat2(0);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
			data[0][i] *= v.x;
			data[1][i] *= v.y;
		}
		return *this;
	}*/
	mat2 operator + (const mat2& m0, const mat2& m1)
	{
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				res.data[i][j] = m0.data[i][j] + m1.data[i][j];
		}
		return res;
	}
	mat2 operator + (float k, const mat2& m)
	{
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				res.data[i][j] = k + m.data[i][j];
		}
		return res;
	}
	mat2 operator + (const mat2& m, float k)
	{
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				res.data[i][j] = m.data[i][j] + k;
		}
		return res;
	}
	mat2 operator + (const mat2& m, vec2 v) {
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			res.data[0][i] = m.data[0][i] + v.x;
			res.data[1][i] = m.data[1][i] + v.y;
		}
		return res;
	}
	mat2 operator + (const vec2 v, const mat2& m) {
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			res.data[0][i] = m.data[0][i] + v.x;
			res.data[1][i] = m.data[1][i] + v.y;
		}
		return res;
	}
	mat2 operator - (const mat2& m0, const mat2& m1)
	{
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				res.data[i][j] = m0.data[i][j] - m1.data[i][j];
		}
		return res;
	}
	mat2 operator - (float k, const mat2& m)
	{
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				res.data[i][j] = k - m.data[i][j];
		}
		return res;
	}
	mat2 operator - (const mat2& m, float k)
	{
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++)
				res.data[i][j] = m.data[i][j] - k;
		}
		return res;
	}
	mat2 operator - (const vec2 v, const mat2& m) {
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			res.data[0][i] = v.x - m.data[0][i];
			res.data[1][i] = v.y - m.data[1][i];
		}
		return res;
	}
	mat2 operator - (const mat2& m, const vec2 v) {
		mat2 res = mat2(0.0f);
		for (int i = 0; i < 2; i++) {
			res.data[0][i] = m.data[0][i] - v.x;
			res.data[1][i] = m.data[1][i] - v.y;
		}
		return res;
	}
	std::ostream& operator<<(std::ostream& os, const mat2& m)
	{
		os << "[ " << m.data[0][0] << " , " << m.data[0][1] << std::endl
			<< "  " << m.data[1][0] << " , " << m.data[1][1] << " ]" << std::endl;
		return os;
	}

	mat3::mat3()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				data[i][j] = 0.0f;
		}
	}

	mat3::mat3(const float k)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] = k;
			}
		}
	}

	mat3::mat3(const float k1, const float k2, const float k3, const float k4, const float k5, const float k6, const float k7, const float k8, const float k9)
	{
		data[0][0] = k1; data[0][1] = k2; data[0][2] = k3;
		data[1][0] = k4; data[1][1] = k5; data[1][2] = k6;
		data[2][0] = k7; data[2][1] = k8; data[2][2] = k9;
	}

	mat3::mat3(const mat3& m)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] = m.data[i][j];
			}
		}
	}

	void mat3::clean()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (fabs(data[i][j]) < THRESHOLD)
					data[i][j] = 0.0f;
			}
		}
	}

	float mat3::determinant() const
	{
		float det = data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
				  - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
				  + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
		return det;
	}

	mat3& mat3::operator=(const mat3& m)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
				data[i][j] = m.data[i][j];
		}
		return *this;
	}
	mat3& mat3::operator+=(const mat3& m)
	{
		mat3 mat = mat3();
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] += m.data[i][j];
			}
		}

		return *this;
	}
	mat3& mat3::operator+=(const vec3& v)
	{
		for (int i = 0; i < 3; i++)
		{
			data[0][i] += v.x;
			data[1][i] += v.y;
			data[2][i] += v.z;
		}

		return *this;
	}
	mat3& mat3::operator+=(const float k)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] += k;
			}
		}

		return *this;
	}
	mat3& mat3::operator-=(const mat3& m)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] -= m.data[i][j];
			}
		}

		return *this;
	}
	mat3& mat3::operator-=(const vec3& v)
	{
		for (int i = 0; i < 3; i++)
		{
			data[0][i] -= v.x;
			data[1][i] -= v.y;
			data[2][i] -= v.z;
		}

		return *this;
	}
	mat3& mat3::operator-=(const float k)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] -= k;
			}
		}

		return *this;
	}
	mat3& mat3::operator*=(const mat3& m)
	{
		mat3 aux = mat3(*this);

		this->data[0][0] = aux.data[0][0] * m.data[0][0] + aux.data[0][1] * m.data[1][0] + aux.data[0][2] * m.data[2][0];
		this->data[0][1] = aux.data[0][0] * m.data[0][1] + aux.data[0][1] * m.data[1][1] + aux.data[0][2] * m.data[2][1];
		this->data[0][2] = aux.data[0][0] * m.data[0][2] + aux.data[0][1] * m.data[1][2] + aux.data[0][2] * m.data[2][2];
		this->data[1][0] = aux.data[1][0] * m.data[0][0] + aux.data[1][1] * m.data[1][0] + aux.data[1][2] * m.data[2][0];
		this->data[1][1] = aux.data[1][0] * m.data[0][1] + aux.data[1][1] * m.data[1][1] + aux.data[1][2] * m.data[2][1];
		this->data[1][2] = aux.data[1][0] * m.data[0][2] + aux.data[1][1] * m.data[1][2] + aux.data[1][2] * m.data[2][2];
		this->data[2][0] = aux.data[2][0] * m.data[0][0] + aux.data[2][1] * m.data[1][0] + aux.data[2][2] * m.data[2][0];
		this->data[2][1] = aux.data[2][0] * m.data[0][1] + aux.data[2][1] * m.data[1][1] + aux.data[2][2] * m.data[2][1];
		this->data[2][2] = aux.data[2][0] * m.data[0][2] + aux.data[2][1] * m.data[1][2] + aux.data[2][2] * m.data[2][2];

		return *this;
	}
	mat3& mat3::operator*=(const vec3& v)
	{
		mat3 aux = mat3(*this);

		this->data[0][0] = aux.data[0][0] * v.x + aux.data[0][1] * v.y + aux.data[0][2] * v.z;
		this->data[0][1] = aux.data[0][0] * v.x + aux.data[0][1] * v.y + aux.data[0][2] * v.z;
		this->data[0][2] = aux.data[0][0] * v.x + aux.data[0][1] * v.y + aux.data[0][2] * v.z;
		this->data[1][0] = aux.data[1][0] * v.x + aux.data[1][1] * v.y + aux.data[1][2] * v.z;
		this->data[1][1] = aux.data[1][0] * v.x + aux.data[1][1] * v.y + aux.data[1][2] * v.z;
		this->data[1][2] = aux.data[1][0] * v.x + aux.data[1][1] * v.y + aux.data[1][2] * v.z;
		this->data[2][0] = aux.data[2][0] * v.x + aux.data[2][1] * v.y + aux.data[2][2] * v.z;
		this->data[2][1] = aux.data[2][0] * v.x + aux.data[2][1] * v.y + aux.data[2][2] * v.z;
		this->data[2][2] = aux.data[2][0] * v.x + aux.data[2][1] * v.y + aux.data[2][2] * v.z;

		return *this;
	}
	mat3& mat3::operator*=(const float k)
	{
		mat3 aux = mat3(*this);

		this->data[0][0] = aux.data[0][0] * k + aux.data[0][1] * k + aux.data[0][2] * k;
		this->data[0][1] = aux.data[0][0] * k + aux.data[0][1] * k + aux.data[0][2] * k;
		this->data[0][2] = aux.data[0][0] * k + aux.data[0][1] * k + aux.data[0][2] * k;
		this->data[1][0] = aux.data[1][0] * k + aux.data[1][1] * k + aux.data[1][2] * k;
		this->data[1][1] = aux.data[1][0] * k + aux.data[1][1] * k + aux.data[1][2] * k;
		this->data[1][2] = aux.data[1][0] * k + aux.data[1][1] * k + aux.data[1][2] * k;
		this->data[2][0] = aux.data[2][0] * k + aux.data[2][1] * k + aux.data[2][2] * k;
		this->data[2][1] = aux.data[2][0] * k + aux.data[2][1] * k + aux.data[2][2] * k;
		this->data[2][2] = aux.data[2][0] * k + aux.data[2][1] * k + aux.data[2][2] * k;

		return *this;
	}
	std::ostream& operator<<(std::ostream& os, const mat3& m)
	{
		os << "[ " << m.data[0][0] << " , " << m.data[0][1] << " , " << m.data[0][2] << std::endl <<
			"  " << m.data[1][0] << " , " << m.data[1][1] << " , " << m.data[1][2] << std::endl <<
			"  " << m.data[2][0] << " , " << m.data[2][1] << " , " << m.data[2][2] << " ]";
		return os;
	}
	mat3 transpose(const mat3& m)
	{
		return mat3(m.data[0][0], m.data[1][0], m.data[2][0], m.data[0][1], m.data[1][1], m.data[2][1], m.data[0][2], m.data[1][2], m.data[2][2]);
	}
	mat3 inverse(const mat3& m)
	{
		float det = m.determinant();
		if (det == 0) return mat3(0);

		mat3 mT = transpose(m);
		mat3 inv = mat3();
		int sign = 1;

		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				mat2 mat = mat2(0);
				int k = 0;
				int l = 0;
				
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (i != x && j != y)
						{
							mat.data[k][l++] = mT.data[i][j];
							if (l == 2)
							{
								k++;
								l = 0;
							}
						}
					}
				}

				inv.data[x][y] = sign * mat.determinant() / det;
				sign = -sign;
			}
		}

		return inv;
	}
	mat3 operator+(const mat3& m0, const mat3& m1)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res.data[i][j] = m0.data[i][j] + m1.data[i][j];
			}
		}

		return res;
	}
	mat3 operator+(const mat3& m, const float k)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res.data[i][j] = m.data[i][j] + k;
			}
		}

		return res;
	}
	mat3 operator+(const float k, const mat3& m)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res.data[i][j] = k + m.data[i][j];
			}
		}

		return res;
	}
	mat3 operator+(const mat3& m, const vec3& v)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			res.data[0][i] = m.data[0][i] + v.x;
			res.data[1][i] = m.data[1][i] + v.y;
			res.data[2][i] = m.data[2][i] + v.z;
		}

		return res;
	}
	mat3 operator+(const vec3& v, const mat3& m)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			res.data[0][i] = m.data[0][i] + v.x;
			res.data[1][i] = m.data[1][i] + v.y;
			res.data[2][i] = m.data[2][i] + v.z;
		}

		return res;
	}
	mat3 operator-(const mat3& m0, const mat3& m1)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res.data[i][j] = m0.data[i][j] - m1.data[i][j];
			}
		}

		return res;
	}
	mat3 operator-(const mat3& m, const float k)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res.data[i][j] = m.data[i][j] - k;
			}
		}

		return res;
	}
	mat3 operator-(const float k, const mat3& m)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				res.data[i][j] = k - m.data[i][j];
			}
		}

		return res;
	}
	mat3 operator-(const mat3& m, const vec3& v)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			res.data[0][i] = m.data[0][i] - v.x;
			res.data[1][i] = m.data[1][i] - v.y;
			res.data[2][i] = m.data[2][i] - v.z;
		}

		return res;
	}
	mat3 operator-(const vec3& v, const mat3& m)
	{
		mat3 res = mat3();

		for (int i = 0; i < 3; i++)
		{
			res.data[0][i] = v.x - m.data[0][i];
			res.data[1][i] = v.y - m.data[1][i];
			res.data[2][i] = v.z - m.data[2][i];
		}

		return res;
	}
	mat3 operator*(const mat3& m0, const mat3& m1)
	{
		mat3 res = mat3();

		res.data[0][0] = m0.data[0][0] * m1.data[0][0] + m0.data[0][1] * m1.data[1][0] + m0.data[0][2] * m1.data[2][0];
		res.data[0][1] = m0.data[0][0] * m1.data[0][1] + m0.data[0][1] * m1.data[1][1] + m0.data[0][2] * m1.data[2][1];
		res.data[0][2] = m0.data[0][0] * m1.data[0][2] + m0.data[0][1] * m1.data[1][2] + m0.data[0][2] * m1.data[2][2];
		res.data[1][0] = m0.data[1][0] * m1.data[0][0] + m0.data[1][1] * m1.data[1][0] + m0.data[1][2] * m1.data[2][0];
		res.data[1][1] = m0.data[1][0] * m1.data[0][1] + m0.data[1][1] * m1.data[1][1] + m0.data[1][2] * m1.data[2][1];
		res.data[1][2] = m0.data[1][0] * m1.data[0][2] + m0.data[1][1] * m1.data[1][2] + m0.data[1][2] * m1.data[2][2];
		res.data[2][0] = m0.data[2][0] * m1.data[0][0] + m0.data[2][1] * m1.data[1][0] + m0.data[2][2] * m1.data[2][0];
		res.data[2][1] = m0.data[2][0] * m1.data[0][1] + m0.data[2][1] * m1.data[1][1] + m0.data[2][2] * m1.data[2][1];
		res.data[2][2] = m0.data[2][0] * m1.data[0][2] + m0.data[2][1] * m1.data[1][2] + m0.data[2][2] * m1.data[2][2];

		return res;
	}
	mat3 operator*(const mat3& m, const float k)
	{
		mat3 res = mat3();

		res.data[0][0] = m.data[0][0] * k + m.data[0][1] * k + m.data[0][2] * k;
		res.data[0][1] = m.data[0][0] * k + m.data[0][1] * k + m.data[0][2] * k;
		res.data[0][2] = m.data[0][0] * k + m.data[0][1] * k + m.data[0][2] * k;
		res.data[1][0] = m.data[1][0] * k + m.data[1][1] * k + m.data[1][2] * k;
		res.data[1][1] = m.data[1][0] * k + m.data[1][1] * k + m.data[1][2] * k;
		res.data[1][2] = m.data[1][0] * k + m.data[1][1] * k + m.data[1][2] * k;
		res.data[2][0] = m.data[2][0] * k + m.data[2][1] * k + m.data[2][2] * k;
		res.data[2][1] = m.data[2][0] * k + m.data[2][1] * k + m.data[2][2] * k;
		res.data[2][2] = m.data[2][0] * k + m.data[2][1] * k + m.data[2][2] * k;

		return res;
	}
	mat3 operator*(const float k, const mat3& m)
	{
		mat3 res = mat3();

		res.data[0][0] = k * m.data[0][0] + k * m.data[1][0] + k * m.data[2][0];
		res.data[0][1] = k * m.data[0][1] + k * m.data[1][1] + k * m.data[2][1];
		res.data[0][2] = k * m.data[0][2] + k * m.data[1][2] + k * m.data[2][2];
		res.data[1][0] = k * m.data[0][0] + k * m.data[1][0] + k * m.data[2][0];
		res.data[1][1] = k * m.data[0][1] + k * m.data[1][1] + k * m.data[2][1];
		res.data[1][2] = k * m.data[0][2] + k * m.data[1][2] + k * m.data[2][2];
		res.data[2][0] = k * m.data[0][0] + k * m.data[1][0] + k * m.data[2][0];
		res.data[2][1] = k * m.data[0][1] + k * m.data[1][1] + k * m.data[2][1];
		res.data[2][2] = k * m.data[0][2] + k * m.data[1][2] + k * m.data[2][2];

		return res;
	}
	mat3 operator*(const mat3& m, const vec3& v)
	{
		return mat3();
	}
	mat3 operator*(const vec3& v, const mat3& m)
	{
		return mat3();
	}
	bool operator==(const mat3& m0, const mat3& m1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (abs(m0.data[i][j] - m1.data[i][j]) > THRESHOLD)
				{
					return false;
				}
			}
		}

		return true;
	}
	bool operator!=(const mat3& m0, const mat3& m1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (abs(m0.data[i][j] - m1.data[i][j]) > THRESHOLD)
				{
					return true;
				}
			}
		}

		return false;
	}


	std::ostream& operator<<(std::ostream& os, const mat4& m)
	{
		os << "[ " << m.data[0][0] << " , " << m.data[0][1] << " , " << m.data[0][2] << " , " << m.data[0][3] << std::endl <<
			"  " << m.data[1][0] << " , " << m.data[1][1] << " , " << m.data[1][2] << " , " << m.data[1][3] << std::endl <<
			"  " << m.data[2][0] << " , " << m.data[2][1] << " , " << m.data[2][2] << " , " << m.data[2][3] << " ]";
		return os;
	}
	mat4::mat4()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				data[i][j] = 0;
			}
		}
	}
	mat4::mat4(const float k)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				data[i][j] = k;
			}
		}
	}
	mat4::mat4(const float k1, const float k2, const float k3, const float k4, const float k5, const float k6, const float k7, const float k8, const float k9, const float k10, const float k11, const float k12, const float k13, const float k14, const float k15, const float k16)
	{
		data[0][0] = k1;
		data[0][1] = k2;
		data[0][2] = k3;
		data[0][3] = k4;
		data[1][0] = k5;
		data[1][1] = k6;
		data[1][2] = k7;
		data[1][3] = k8;
		data[2][0] = k9;
		data[2][1] = k10;
		data[2][2] = k11;
		data[2][3] = k12;
		data[3][0] = k13;
		data[3][1] = k14;
		data[3][2] = k15;
		data[3][3] = k16;
	}
	mat4::mat4(const mat4& m)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				data[i][j] = m.data[i][j];
			}
		}
	}
	void mat4::clean()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (fabs(data[i][j]) < THRESHOLD)
					data[i][j] = 0.0f;
			}
		}
	}
	mat4& mat4::operator=(const mat4& m)
	{
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				data[i][j] = m.data[i][j];
		}
		return *this;
	}
	mat4& mat4::operator+=(const mat4& m)
	{
		mat4 mat = mat4();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				data[i][j] += m.data[i][j];
			}
		}

		return *this;
	}
	mat4& mat4::operator+=(const vec4& v)
	{
		for (int i = 0; i < 4; i++)
		{
			data[0][i] += v.x;
			data[1][i] += v.y;
			data[2][i] += v.z;
			data[3][i] += v.w;
		}

		return *this;
	}
	mat4& mat4::operator+=(const float k)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				data[i][j] += k;
			}
		}

		return *this;
	}
	mat4& mat4::operator-=(const mat4& m)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				data[i][j] -= m.data[i][j];
			}
		}

		return *this;
	}
	mat4& mat4::operator-=(const vec4& v)
	{
		for (int i = 0; i < 4; i++)
		{
			data[0][i] -= v.x;
			data[1][i] -= v.y;
			data[2][i] -= v.z;
			data[3][i] -= v.w;
		}

		return *this;
	}
	mat4& mat4::operator-=(const float k)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				data[i][j] -= k;
			}
		}

		return *this;
	}
	mat4& mat4::operator*=(const mat4& m)
	{
		mat4 aux = mat4(*this);

		this->data[0][0] = aux.data[0][0] * m.data[0][0] + aux.data[0][1] * m.data[1][0] + aux.data[0][2] * m.data[2][0] + aux.data[0][3] * m.data[3][0];
		this->data[0][1] = aux.data[0][0] * m.data[0][1] + aux.data[0][1] * m.data[1][1] + aux.data[0][2] * m.data[2][1] + aux.data[0][3] * m.data[3][1];
		this->data[0][2] = aux.data[0][0] * m.data[0][2] + aux.data[0][1] * m.data[1][2] + aux.data[0][2] * m.data[2][2] + aux.data[0][3] * m.data[3][2];
		this->data[0][3] = aux.data[0][0] * m.data[0][3] + aux.data[0][1] * m.data[1][3] + aux.data[0][2] * m.data[2][3] + aux.data[0][3] * m.data[3][3];
		this->data[1][0] = aux.data[1][0] * m.data[0][0] + aux.data[1][1] * m.data[1][0] + aux.data[1][2] * m.data[2][0] + aux.data[1][3] * m.data[3][0];
		this->data[1][1] = aux.data[1][0] * m.data[0][1] + aux.data[1][1] * m.data[1][1] + aux.data[1][2] * m.data[2][1] + aux.data[1][3] * m.data[3][1];
		this->data[1][2] = aux.data[1][0] * m.data[0][2] + aux.data[1][1] * m.data[1][2] + aux.data[1][2] * m.data[2][2] + aux.data[1][3] * m.data[3][2];
		this->data[1][3] = aux.data[1][0] * m.data[0][3] + aux.data[1][1] * m.data[1][3] + aux.data[1][2] * m.data[2][3] + aux.data[1][3] * m.data[3][3];
		this->data[2][0] = aux.data[2][0] * m.data[0][0] + aux.data[2][1] * m.data[1][0] + aux.data[2][2] * m.data[2][0] + aux.data[2][3] * m.data[3][0];
		this->data[2][1] = aux.data[2][0] * m.data[0][1] + aux.data[2][1] * m.data[1][1] + aux.data[2][2] * m.data[2][1] + aux.data[2][3] * m.data[3][1];
		this->data[2][2] = aux.data[2][0] * m.data[0][2] + aux.data[2][1] * m.data[1][2] + aux.data[2][2] * m.data[2][2] + aux.data[2][3] * m.data[3][2];
		this->data[2][3] = aux.data[2][0] * m.data[0][3] + aux.data[2][1] * m.data[1][3] + aux.data[2][2] * m.data[2][3] + aux.data[2][3] * m.data[3][3];
		this->data[3][0] = aux.data[3][0] * m.data[0][0] + aux.data[3][1] * m.data[1][0] + aux.data[3][2] * m.data[2][0] + aux.data[3][3] * m.data[3][0];
		this->data[3][1] = aux.data[3][0] * m.data[0][1] + aux.data[3][1] * m.data[1][1] + aux.data[3][2] * m.data[2][1] + aux.data[3][3] * m.data[3][1];
		this->data[3][2] = aux.data[3][0] * m.data[0][2] + aux.data[3][1] * m.data[1][2] + aux.data[3][2] * m.data[2][2] + aux.data[3][3] * m.data[3][2];
		this->data[3][3] = aux.data[3][0] * m.data[0][3] + aux.data[3][1] * m.data[1][3] + aux.data[3][2] * m.data[2][3] + aux.data[3][3] * m.data[3][3];

		return *this;
	}
	mat4& mat4::operator*=(const vec4& v)
	{
		mat4 aux = mat4(*this);

		this->data[0][0] = aux.data[0][0] * v.x + aux.data[0][1] * v.y + aux.data[0][2] * v.z + aux.data[0][3] * v.w;
		this->data[0][1] = aux.data[0][0] * v.x + aux.data[0][1] * v.y + aux.data[0][2] * v.z + aux.data[0][3] * v.w;
		this->data[0][2] = aux.data[0][0] * v.x + aux.data[0][1] * v.y + aux.data[0][2] * v.z + aux.data[0][3] * v.w;
		this->data[0][3] = aux.data[0][0] * v.x + aux.data[0][1] * v.y + aux.data[0][2] * v.z + aux.data[0][3] * v.w;
		this->data[1][0] = aux.data[1][0] * v.x + aux.data[1][1] * v.y + aux.data[1][2] * v.z + aux.data[1][3] * v.w;
		this->data[1][1] = aux.data[1][0] * v.x + aux.data[1][1] * v.y + aux.data[1][2] * v.z + aux.data[1][3] * v.w;
		this->data[1][2] = aux.data[1][0] * v.x + aux.data[1][1] * v.y + aux.data[1][2] * v.z + aux.data[1][3] * v.w;
		this->data[1][3] = aux.data[1][0] * v.x + aux.data[1][1] * v.y + aux.data[1][2] * v.z + aux.data[1][3] * v.w;
		this->data[2][0] = aux.data[2][0] * v.x + aux.data[2][1] * v.y + aux.data[2][2] * v.z + aux.data[2][3] * v.w;
		this->data[2][1] = aux.data[2][0] * v.x + aux.data[2][1] * v.y + aux.data[2][2] * v.z + aux.data[2][3] * v.w;
		this->data[2][2] = aux.data[2][0] * v.x + aux.data[2][1] * v.y + aux.data[2][2] * v.z + aux.data[2][3] * v.w;
		this->data[2][3] = aux.data[2][0] * v.x + aux.data[2][1] * v.y + aux.data[2][2] * v.z + aux.data[2][3] * v.w;
		this->data[3][0] = aux.data[3][0] * v.x + aux.data[3][1] * v.y + aux.data[3][2] * v.z + aux.data[3][3] * v.w;
		this->data[3][1] = aux.data[3][0] * v.x + aux.data[3][1] * v.y + aux.data[3][2] * v.z + aux.data[3][3] * v.w;
		this->data[3][2] = aux.data[3][0] * v.x + aux.data[3][1] * v.y + aux.data[3][2] * v.z + aux.data[3][3] * v.w;
		this->data[3][3] = aux.data[3][0] * v.x + aux.data[3][1] * v.y + aux.data[3][2] * v.z + aux.data[3][3] * v.w;

		return *this;
	}
	mat4& mat4::operator*=(const float k)
	{
		mat4 aux = mat4(*this);

		this->data[0][0] = aux.data[0][0] * k + aux.data[0][1] * k + aux.data[0][2] * k + aux.data[0][3] * k;
		this->data[0][1] = aux.data[0][0] * k + aux.data[0][1] * k + aux.data[0][2] * k + aux.data[0][3] * k;
		this->data[0][2] = aux.data[0][0] * k + aux.data[0][1] * k + aux.data[0][2] * k + aux.data[0][3] * k;
		this->data[0][3] = aux.data[0][0] * k + aux.data[0][1] * k + aux.data[0][2] * k + aux.data[0][3] * k;
		this->data[1][0] = aux.data[1][0] * k + aux.data[1][1] * k + aux.data[1][2] * k + aux.data[1][3] * k;
		this->data[1][1] = aux.data[1][0] * k + aux.data[1][1] * k + aux.data[1][2] * k + aux.data[1][3] * k;
		this->data[1][2] = aux.data[1][0] * k + aux.data[1][1] * k + aux.data[1][2] * k + aux.data[1][3] * k;
		this->data[1][3] = aux.data[1][0] * k + aux.data[1][1] * k + aux.data[1][2] * k + aux.data[1][3] * k;
		this->data[2][0] = aux.data[2][0] * k + aux.data[2][1] * k + aux.data[2][2] * k + aux.data[2][3] * k;
		this->data[2][1] = aux.data[2][0] * k + aux.data[2][1] * k + aux.data[2][2] * k + aux.data[2][3] * k;
		this->data[2][2] = aux.data[2][0] * k + aux.data[2][1] * k + aux.data[2][2] * k + aux.data[2][3] * k;
		this->data[2][3] = aux.data[2][0] * k + aux.data[2][1] * k + aux.data[2][2] * k + aux.data[2][3] * k;
		this->data[3][0] = aux.data[3][0] * k + aux.data[3][1] * k + aux.data[3][2] * k + aux.data[3][3] * k;
		this->data[3][1] = aux.data[3][0] * k + aux.data[3][1] * k + aux.data[3][2] * k + aux.data[3][3] * k;
		this->data[3][2] = aux.data[3][0] * k + aux.data[3][1] * k + aux.data[3][2] * k + aux.data[3][3] * k;
		this->data[3][3] = aux.data[3][0] * k + aux.data[3][1] * k + aux.data[3][2] * k + aux.data[3][3] * k;

		return *this;
	}
	mat4 operator+(const mat4& m0, const mat4& m1)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.data[i][j] = m0.data[i][j] + m1.data[i][j];
			}
		}

		return res;
	}
	mat4 operator+(const mat4& m, const float k)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.data[i][j] = m.data[i][j] + k;
			}
		}

		return res;
	}
	mat4 operator+(const float k, const mat4& m)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.data[i][j] = k + m.data[i][j];
			}
		}

		return res;
	}
	mat4 operator+(const mat4& m, const vec4& v)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			res.data[0][i] = m.data[0][i] + v.x;
			res.data[1][i] = m.data[1][i] + v.y;
			res.data[2][i] = m.data[2][i] + v.z;
			res.data[3][i] = m.data[3][i] + v.w;
		}

		return res;
	}
	mat4 operator+(const vec4& v, const mat4& m)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			res.data[0][i] = v.x + m.data[0][i];
			res.data[1][i] = v.y + m.data[1][i];
			res.data[2][i] = v.z + m.data[2][i];
			res.data[3][i] = v.w + m.data[3][i];
		}

		return res;
	}
	mat4 operator-(const mat4& m0, const mat4& m1)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.data[i][j] = m0.data[i][j] - m1.data[i][j];
			}
		}

		return res;
	}
	mat4 operator-(const mat4& m, const float k)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.data[i][j] = m.data[i][j] - k;
			}
		}

		return res;
	}
	mat4 operator-(const float k, const mat4& m)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.data[i][j] = k - m.data[i][j];
			}
		}

		return res;
	}
	mat4 operator-(const mat4& m, const vec4& v)
	{
		mat4 res = mat4();

		for (int i = 0; i < 4; i++)
		{
			res.data[0][i] = m.data[0][i] - v.x;
			res.data[1][i] = m.data[1][i] - v.y;
			res.data[2][i] = m.data[2][i] - v.z;
			res.data[3][i] = m.data[3][i] - v.w;
		}

		return res;
	}
	mat4 operator-(const vec4& v, const mat4& m)
	{
		mat4 res = mat4();

		for (int i = 0; i < 3; i++)
		{
			res.data[0][i] = v.x - m.data[0][i];
			res.data[1][i] = v.y - m.data[1][i];
			res.data[2][i] = v.z - m.data[2][i];
			res.data[3][i] = v.w - m.data[3][i];
		}

		return res;
	}
	mat4 operator*(const mat4& m0, const mat4& m1)
	{
		mat4 res = mat4();

		res.data[0][0] = m0.data[0][0] * m1.data[0][0] + m0.data[0][1] * m1.data[1][0] + m0.data[0][2] * m1.data[2][0] + m0.data[0][3] * m1.data[3][0];
		res.data[0][1] = m0.data[0][0] * m1.data[0][1] + m0.data[0][1] * m1.data[1][1] + m0.data[0][2] * m1.data[2][1] + m0.data[0][3] * m1.data[3][1];
		res.data[0][2] = m0.data[0][0] * m1.data[0][2] + m0.data[0][1] * m1.data[1][2] + m0.data[0][2] * m1.data[2][2] + m0.data[0][3] * m1.data[3][2];
		res.data[0][3] = m0.data[0][0] * m1.data[0][3] + m0.data[0][1] * m1.data[1][3] + m0.data[0][2] * m1.data[2][3] + m0.data[0][3] * m1.data[3][3];
		res.data[1][0] = m0.data[1][0] * m1.data[0][0] + m0.data[1][1] * m1.data[1][0] + m0.data[1][2] * m1.data[2][0] + m0.data[1][3] * m1.data[3][0];
		res.data[1][1] = m0.data[1][0] * m1.data[0][1] + m0.data[1][1] * m1.data[1][1] + m0.data[1][2] * m1.data[2][1] + m0.data[1][3] * m1.data[3][1];
		res.data[1][2] = m0.data[1][0] * m1.data[0][2] + m0.data[1][1] * m1.data[1][2] + m0.data[1][2] * m1.data[2][2] + m0.data[1][3] * m1.data[3][2];
		res.data[1][3] = m0.data[1][0] * m1.data[0][3] + m0.data[1][1] * m1.data[1][3] + m0.data[1][2] * m1.data[2][3] + m0.data[1][3] * m1.data[3][3];
		res.data[2][0] = m0.data[2][0] * m1.data[0][0] + m0.data[2][1] * m1.data[1][0] + m0.data[2][2] * m1.data[2][0] + m0.data[2][3] * m1.data[3][0];
		res.data[2][1] = m0.data[2][0] * m1.data[0][1] + m0.data[2][1] * m1.data[1][1] + m0.data[2][2] * m1.data[2][1] + m0.data[2][3] * m1.data[3][1];
		res.data[2][2] = m0.data[2][0] * m1.data[0][2] + m0.data[2][1] * m1.data[1][2] + m0.data[2][2] * m1.data[2][2] + m0.data[2][3] * m1.data[3][2];
		res.data[2][3] = m0.data[2][0] * m1.data[0][3] + m0.data[2][1] * m1.data[1][3] + m0.data[2][2] * m1.data[2][3] + m0.data[2][3] * m1.data[3][3];
		res.data[3][0] = m0.data[3][0] * m1.data[0][0] + m0.data[3][1] * m1.data[1][0] + m0.data[3][2] * m1.data[2][0] + m0.data[3][3] * m1.data[3][0];
		res.data[3][1] = m0.data[3][0] * m1.data[0][1] + m0.data[3][1] * m1.data[1][1] + m0.data[3][2] * m1.data[2][1] + m0.data[3][3] * m1.data[3][1];
		res.data[3][2] = m0.data[3][0] * m1.data[0][2] + m0.data[3][1] * m1.data[1][2] + m0.data[3][2] * m1.data[2][2] + m0.data[3][3] * m1.data[3][2];
		res.data[3][3] = m0.data[3][0] * m1.data[0][3] + m0.data[3][1] * m1.data[1][3] + m0.data[3][2] * m1.data[2][3] + m0.data[3][3] * m1.data[3][3];

		return res;
	}
	mat4 operator*(const mat4& m, const float k)
	{
		mat4 res = mat4();

		res.data[0][0] = m.data[0][0] * k + m.data[0][1] * k + m.data[0][2] * k + m.data[0][3] * k;
		res.data[0][1] = m.data[0][0] * k + m.data[0][1] * k + m.data[0][2] * k + m.data[0][3] * k;
		res.data[0][2] = m.data[0][0] * k + m.data[0][1] * k + m.data[0][2] * k + m.data[0][3] * k;
		res.data[0][3] = m.data[0][0] * k + m.data[0][1] * k + m.data[0][2] * k + m.data[0][3] * k;
		res.data[1][0] = m.data[1][0] * k + m.data[1][1] * k + m.data[1][2] * k + m.data[1][3] * k;
		res.data[1][1] = m.data[1][0] * k + m.data[1][1] * k + m.data[1][2] * k + m.data[1][3] * k;
		res.data[1][2] = m.data[1][0] * k + m.data[1][1] * k + m.data[1][2] * k + m.data[1][3] * k;
		res.data[1][3] = m.data[1][0] * k + m.data[1][1] * k + m.data[1][2] * k + m.data[1][3] * k;
		res.data[2][0] = m.data[2][0] * k + m.data[2][1] * k + m.data[2][2] * k + m.data[2][3] * k;
		res.data[2][1] = m.data[2][0] * k + m.data[2][1] * k + m.data[2][2] * k + m.data[2][3] * k;
		res.data[2][2] = m.data[2][0] * k + m.data[2][1] * k + m.data[2][2] * k + m.data[2][3] * k;
		res.data[2][3] = m.data[2][0] * k + m.data[2][1] * k + m.data[2][2] * k + m.data[2][3] * k;
		res.data[3][0] = m.data[3][0] * k + m.data[3][1] * k + m.data[3][2] * k + m.data[3][3] * k;
		res.data[3][1] = m.data[3][0] * k + m.data[3][1] * k + m.data[3][2] * k + m.data[3][3] * k;
		res.data[3][2] = m.data[3][0] * k + m.data[3][1] * k + m.data[3][2] * k + m.data[3][3] * k;
		res.data[3][3] = m.data[3][0] * k + m.data[3][1] * k + m.data[3][2] * k + m.data[3][3] * k;

		return res;
	}
	mat4 operator*(const float k, const mat4& m)
	{
		mat4 res = mat4();

		res.data[0][0] = k * m.data[0][0] + k * m.data[1][0] + k * m.data[2][0] + k * m.data[3][0];
		res.data[0][1] = k * m.data[0][1] + k * m.data[1][1] + k * m.data[2][1] + k * m.data[3][1];
		res.data[0][2] = k * m.data[0][2] + k * m.data[1][2] + k * m.data[2][2] + k * m.data[3][2];
		res.data[0][3] = k * m.data[0][3] + k * m.data[1][3] + k * m.data[2][3] + k * m.data[3][3];
		res.data[1][0] = k * m.data[0][0] + k * m.data[1][0] + k * m.data[2][0] + k * m.data[3][0];
		res.data[1][1] = k * m.data[0][1] + k * m.data[1][1] + k * m.data[2][1] + k * m.data[3][1];
		res.data[1][2] = k * m.data[0][2] + k * m.data[1][2] + k * m.data[2][2] + k * m.data[3][2];
		res.data[1][3] = k * m.data[0][3] + k * m.data[1][3] + k * m.data[2][3] + k * m.data[3][3];
		res.data[2][0] = k * m.data[0][0] + k * m.data[1][0] + k * m.data[2][0] + k * m.data[3][0];
		res.data[2][1] = k * m.data[0][1] + k * m.data[1][1] + k * m.data[2][1] + k * m.data[3][1];
		res.data[2][2] = k * m.data[0][2] + k * m.data[1][2] + k * m.data[2][2] + k * m.data[3][2];
		res.data[2][3] = k * m.data[0][3] + k * m.data[1][3] + k * m.data[2][3] + k * m.data[3][3];
		res.data[3][0] = k * m.data[0][0] + k * m.data[1][0] + k * m.data[2][0] + k * m.data[3][0];
		res.data[3][1] = k * m.data[0][1] + k * m.data[1][1] + k * m.data[2][1] + k * m.data[3][1];
		res.data[3][2] = k * m.data[0][2] + k * m.data[1][2] + k * m.data[2][2] + k * m.data[3][2];
		res.data[3][3] = k * m.data[0][3] + k * m.data[1][3] + k * m.data[2][3] + k * m.data[3][3];

		return res;
	}
	mat4 operator*(const mat4& m, const vec4& v)
	{
		return mat4();
	}
	mat4 operator*(const vec4& v, const mat4& m)
	{
		return mat4();
	}
	bool operator==(const mat4& m0, const mat4& m1)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m0.data[i][j] != m1.data[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}
	bool operator!=(const mat4& m0, const mat4& m1)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m0.data[i][j] != m1.data[i][j])
				{
					return true;
				}
			}
		}

		return false;
	}
};