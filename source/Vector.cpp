#include "../header/Vector.h"

namespace egn {

	vec2::vec2()
	{
		vec2::x = 0.0f;
		vec2::y = 0.0f;
	}

	vec2::vec2(const float k)
	{
		vec2::x = k;
		vec2::y = k;
	}

	vec2::vec2(const float x, const float y)
	{
		vec2::x = x;
		vec2::y = y;
	}

	vec2::vec2(const vec2& v)
	{
		vec2::x = v.x;
		vec2::y = v.y;
	}

	float* vec2::data()
	{
		static float v[2] = { x,y };
		return v;
	}

	void vec2::clean()
	{
		x = fabs(x) < THRESHOLD ? 0.0f : x;
		y = fabs(y) < THRESHOLD ? 0.0f : y;
	}

	const float vec2::length() const
	{
		return sqrt(pow(vec2::x, 2) + pow(vec2::y, 2));
	}

	vec2& vec2::operator=(const vec2& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	vec2 vec2::operator-()
	{
		return vec2(-vec2::x, -vec2::y);
	}

	vec2& vec2::operator+=(const vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	vec2& vec2::operator+=(const float k)
	{
		x += k;
		y += k;
		return *this;
	}

	vec2& vec2::operator-=(const vec2& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	vec2& vec2::operator-=(const float k) {
		x -= k;
		y -= k;
		return *this;
	}

	vec2& vec2::operator*=(const float k)
	{
		x *= k;
		y *= k;
		return *this;
	}

	vec2 normalize(const vec2& v)
	{
		float len = v.length();
		if (len == 0) { return vec2(0, 0); }
		return vec2(v.x / len, v.y / len);
	}

	vec2 operator + (vec2& v0, vec2& v1)
	{
		return vec2(v0.x + v1.x, v0.y + v1.y);
	}

	vec2 operator + (vec2 v0, vec2 v1)
	{
		return vec2(v0.x + v1.x, v0.y + v1.y);
	}

	vec2 operator + (vec2& v, float k)
	{
		return vec2(v.x + k, v.y + k);
	}

	vec2 operator + (float k, vec2& v)
	{
		return vec2(v.x + k, v.y + k);
	}

	vec2 operator - (vec2& v0, vec2& v1)
	{
		return vec2(v0.x - v1.x, v0.y - v1.y);
	}

	vec2 operator - (vec2 v0, vec2 v1)
	{
		return vec2(v0.x - v1.x, v0.y - v1.y);
	}

	vec2 operator - (vec2& v, float k) 
	{
		return vec2(v.x - k, v.y - k);
	}

	vec2 operator - (float k, vec2& v)
	{
		return vec2(k - v.x, k - v.y);
	}

	vec2 operator * (vec2& v, float k)
	{
		return vec2(v.x * k, v.y * k);
	}

	vec2 operator*(float k, vec2& v)
	{
		return vec2(v.x * k, v.y * k);
	}

	vec2 operator / (vec2& v, float k)
	{
		if (k == 0)
			return vec2(0, 0);
		return vec2(v.x / k, v.y / k);
	}

	vec2 operator / (float k, vec2& v)
	{
		if (v.x == 0)
			if (v.y == 0)
				return vec2(0, 0);
			return vec2(0, k / v.y);
		if (v.y == 0)
			return vec2(k / v.x, 0);
		return vec2(k / v.x, k / v.y);
	}

	bool operator==(const vec2& v0, const vec2& v1)
	{
		if (v0.x == v1.x && v0.y == v1.y)
			return true;
		return false;
	}

	bool operator!=(const vec2& v0, const vec2& v1)
	{
		if (v0.x == v1.x && v0.y == v1.y)
			return false;
		return true;
	}

	std::ostream& operator<<(std::ostream& os, const vec2& v)
	{
		os << "[" << v.x << " , " << v.y << "]";
		return os;
	}

	std::istream& operator>>(std::istream& is, vec2& v)
	{
		char c;
		is >> v.x;
		is.get(c);
		is >> v.y;
		is.get(c);
		return is;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	vec3::vec3()
	{
		vec3::x = 0.0f;
		vec3::y = 0.0f;
		vec3::z = 0.0f;

	}
	vec3::vec3(const float k)
	{
		vec3::x = k;
		vec3::y = k;
		vec3::z = k;
	}
	vec3::vec3(const float x, const float y, const float z)
	{
		vec3::x = x;
		vec3::y = y;
		vec3::z = z;
	}
	vec3::vec3(const vec3& v)
	{
		vec3::x = v.x;
		vec3::y = v.y;
		vec3::z = v.z;
	}
	vec3::vec3(const vec4& v)
	{
		vec3::x = v.x;
		vec3::y = v.y;
		vec3::z = v.z;
	}
	float* vec3::data()
	{
		static float v[3] = { x,y,z };
		return v;
	}
	void vec3::clean()
	{
		x = fabs(x) < THRESHOLD ? 0.0f : x;
		y = fabs(y) < THRESHOLD ? 0.0f : y;
		z = fabs(z) < THRESHOLD ? 0.0f : z;
	}

	const float vec3::length() const
	{
		return sqrt(pow(vec3::x, 2) + pow(vec3::y, 2) + pow(vec3::z, 2));
	}
	vec3& vec3::operator=(const vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	vec3& vec3::operator=(const vec4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	vec3 vec3::operator-()
	{
		return vec3(-vec3::x, -vec3::y, -vec3::z);
	}
	vec3& vec3::operator+=(const vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec3& vec3::operator+=(float k)
	{
		x += k;
		y += k;
		z += k;
		return *this;
	}

	vec3& vec3::operator-=(const vec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	vec3& vec3::operator-=(float k)
	{
		x -= k;
		y -= k;
		z -= k;
		return *this;
	}
	vec3& vec3::operator*=(const float k)
	{
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	vec3 vec3::normalize(const vec3& v)
	{
		float len = v.length();
		if (len == 0) { return vec3(0, 0, 0); }
		return vec3(v.x / len, v.y / len, v.z / len);
	}

	vec3 operator+ (vec3& v0, vec3& v1) 
	{
		return vec3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
	}
	vec3 operator+ (vec3 v0, vec3 v1)
	{
		return vec3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
	}
	vec3 operator+(vec3& v, float k)
	{
		return vec3(v.x + k, v.y + k, v.z + k);
	}
	vec3 operator+(float k, vec3& v)
	{
		return vec3(k + v.x, k + v.y, k + v.z);
	}

	vec3 operator-(vec3& v0, vec3& v1)
	{
		return vec3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
	}
	vec3 operator-(vec3 v0, vec3 v1)
	{
		return vec3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
	}
	vec3 operator-(vec3& v, float k)
	{
		return vec3(v.x - k, v.y - k, v.z - k);
	}
	vec3 operator-(float k, vec3& v)
	{
		return vec3(k - v.x, k - v.y, k - v.z);
	}

	const vec3 operator*(const vec3& v, const float k)
	{
		return vec3(v.x * k, v.y * k, v.z * k);
	}
	const vec3 operator*(const float k, const vec3& v)
	{
		return vec3(v.x * k, v.y * k, v.z * k);
	}
	vec3 vec3::operator*(const float k)
	{
		return vec3(this->x * k, this->y * k, this->z * k);
	}
	const vec3 operator/(const float k, const vec3& v)
	{
		return vec3(k / v.x, k / v.y, k / v.z);
	}
	float vec3::dot(const vec3& v0, const vec3& v1)
	{
		return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
	}
	vec3 vec3::cross(const vec3& v0, const vec3& v1)
	{
		float x = v0.y * v1.z - v0.z * v1.y;
		float y = v0.z * v1.x - v0.x * v1.z;
		float z = v0.x * v1.y - v0.y * v1.x;
		return vec3(x, y, z);
	}

	vec3 vec3::lerp(const vec3& v0, const vec3& v1, float delta)
	{
		vec3 res = vec3();
		vec3 aux = v1 - v0;
		aux *= delta;
		res = v0 + aux;
		return res;
	}

	bool operator==(const vec3& v0, const vec3& v1)
	{
		if (v0.x == v1.x && v0.y == v1.y && v0.z == v1.z)
			return true;
		return false;
	}

	bool operator!=(const vec3& v0, const vec3& v1)
	{
		if (v0.x == v1.x && v0.y == v1.y && v0.z == v1.z)
			return false;
		return true;
	}

	std::ostream& operator<<(std::ostream& os, const vec3& v)
	{
		os << "[" << v.x << " , " << v.y << " , " << v.z << "]";
		return os;
	}

	std::istream& operator>>(std::istream& is, vec3& v)
	{
		char c;
		is >> v.x;
		is.get(c);
		is >> v.y;
		is.get(c);
		is >> v.z;
		is.get(c);
		return is;
	}

	///////////////////////////////////////////////////////////////////////////////////

	vec4::vec4()
	{
		vec4::x = 0.0f;
		vec4::y = 0.0f;
		vec4::z = 0.0f;
		vec4::w = 0.0f;
	}

	vec4::vec4(const float k)
	{
		vec4::x = k;
		vec4::y = k;
		vec4::z = k;
		vec4::w = k;
	}

	vec4::vec4(const float x, const float y, const float z)
	{
		vec4::x = x;
		vec4::y = y;
		vec4::z = z;
		vec4::w = 0.0f;
	}

	vec4::vec4(const float x, const float y, const float z, const float w)
	{
		vec4::x = x;
		vec4::y = y;
		vec4::z = z;
		vec4::w = w;
	}

	vec4::vec4(const vec3& v)
	{
		vec4::x = v.x;
		vec4::y = v.y;
		vec4::z = v.z;
		vec4::w = 0.0f;
	}

	vec4::vec4(const vec4& v)
	{
		vec4::x = v.x;
		vec4::y = v.y;
		vec4::z = v.z;
		vec4::w = v.w;
	}
	void vec4::getData(float inData[])
	{
		inData[0] = x;
		inData[1] = y;
		inData[2] = z;
		inData[3] = w;
	}

	void vec4::clean()
	{
		x = fabs(x) < THRESHOLD ? 0.0f : x;
		y = fabs(y) < THRESHOLD ? 0.0f : y;
		z = fabs(z) < THRESHOLD ? 0.0f : z;
		w = fabs(w) < THRESHOLD ? 0.0f : w;
	}

	const vec4 normalize(const vec4& v)
	{
		vec4 vn;
		float s = 1 / (v.w * sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
		vn.x = v.x * s;
		vn.y = v.y * s;
		vn.z = v.z * s;
		vn.w = 1.0f;
		return vn;
	}

	const bool operator==(const vec4& v0, const vec4& v1)
	{
		if (v0.x == v1.x && v0.y == v1.y && v0.z == v1.z && v0.w == v1.w)
			return true;
		return false;
	}

	const bool operator!=(const vec4& v0, const vec4& v1)
	{
		if (v0.x == v1.x && v0.y == v1.y && v0.z == v1.z && v0.w == v1.w)
			return false;
		return true;
	}

	std::ostream& operator<<(std::ostream& os, const vec4& v)
	{
		os << "[" << v.x << " , " << v.y << " , " << v.z << " , " << v.w << "]";
		return os;
	}

	std::istream& operator>>(std::istream& is, vec4& v)
	{
		char c;
		is >> v.x;
		is.get(c);
		is >> v.y;
		is.get(c);
		is >> v.z;
		is.get(c);
		is >> v.w;
		is.get(c);
		return is;
	}

}