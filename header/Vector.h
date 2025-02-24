#pragma once
#ifndef VECTOR
#define VECTOR
#include <iostream>
#include <math.h>
#include "Constants.h"



namespace egn
{
	struct vec2;
	struct vec3;
	struct vec4;

	struct vec2 {
		float x, y;

		vec2();
		vec2(const float k);
		vec2(const float x, const float y);
		vec2(const vec2& v);
		float* data();
		void clean();
		const float length() const;
		vec2& operator = (const vec2& v);
		vec2 operator - ();
		vec2& operator += (const vec2& v);
		vec2& operator += (const float k);
		vec2& operator -= (const vec2& v);
		vec2& operator -= (const float k);
		vec2& operator *= (const float k);
		friend vec2 normalize(const vec2& v);
		friend vec2 operator + (vec2& v0, vec2& v1);
		friend vec2 operator + (vec2 v0, vec2 v1);
		friend vec2 operator + (vec2& v, float k);
		friend vec2 operator + (float k, vec2& v);
		friend vec2 operator - (vec2& v0, vec2& v1);
		friend vec2 operator - (vec2 v0, vec2 v1);
		friend vec2 operator - (vec2& v, float k);
		friend vec2 operator - (float k, vec2& v);
		friend vec2 operator * (vec2& v, float k);
		friend vec2 operator * (float k, vec2& v);
		friend vec2 operator / (vec2& v, float k);
		friend vec2 operator / (float k, vec2& v);
		friend bool operator == (const vec2& v0, const vec2& v1);
		friend bool operator != (const vec2& v0, const vec2& v1);
		friend std::ostream& operator << (std::ostream& os, const vec2& v);
		friend std::istream& operator >> (std::istream& is, vec2& v);

	};

	struct vec3 {
		float x, y, z;

		vec3();
		vec3(const float k);
		vec3(const float x, const float y, const float z);
		vec3(const vec3& v);
		vec3(const vec4& v);
		float* data();
		void clean();
		const float length() const;
		vec3& operator = (const vec3& v);
		vec3& operator = (const vec4& v);
		vec3 operator - (); //additive inverse
		vec3& operator += (const vec3& v);
		vec3& operator += (float k);
		vec3& operator -= (const vec3& v);
		vec3& operator -= (float k);
		vec3& operator *= (const float k);
		//vec3 normalize();
		vec3 static normalize(const vec3& v);
		friend vec3 operator + (vec3& v0, vec3& v1);
		friend vec3 operator + (vec3 v0, vec3 v1);
		friend vec3 operator + (vec3& v, float k);
		friend vec3 operator + (float k, vec3& v);
		friend vec3 operator - (vec3& v0, vec3& v1);
		friend vec3 operator - (vec3 v0, vec3 v1);
		friend vec3 operator - (vec3& v, float k);
		friend vec3 operator - (float k, vec3& v);
		vec3 operator* (const float k);
		friend const vec3 operator * (const float k, const vec3& v1);
		friend const vec3 operator / (const float k, const vec3& v);
		float static dot(const vec3& v0, const vec3& v1);
		vec3 static cross(const vec3& v0, const vec3& v1);
		vec3 static lerp(const vec3& v0, const vec3& v1, float delta);
		friend bool operator == (const vec3& v0, const vec3& v1);
		friend bool operator != (const vec3& v0, const vec3& v1);
		friend std::ostream& operator << (std::ostream& os, const vec3& v);
		friend std::istream& operator >> (std::istream& is, vec3& v);
	};

	struct vec4 {
		float x, y, z, w;
		//float data[4];
		vec4();
		vec4(const float k);
		vec4(const float x, const float y, const float z);
		vec4(const float x, const float y, const float z, const float w);
		vec4(const vec3& v);
		vec4(const vec4& v);
		void getData(float inData[]);
		void clean();
		friend const vec4 normalize(const vec4& v);
		friend const bool operator == (const vec4& v0, const vec4& v1);
		friend const bool operator != (const vec4& v0, const vec4& v1);
		friend std::ostream& operator << (std::ostream& os, const vec4& v);
		friend std::istream& operator >> (std::istream& is, vec4& v);
	};
};
#endif
