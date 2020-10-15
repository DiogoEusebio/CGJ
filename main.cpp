#include <iostream>
#include "../header/MasterHeader.h"


int main(int argc, char* argv[])
{
	/*
	std::cout << "CGJ vectors | delivery 1" << std::endl;
	std::cout << "2D Vectors" << std::endl;
	egn::vec2 v1 = egn::vec2(1);
	egn::vec2 v2; //0 arguments operator
	egn::vec2 v3 = egn::vec2(1, 0);
	egn::vec2 v4 = egn::vec2(1, 1);
	std::cout << "v1 " << v1 << std::endl << "v2 " << v2 << std::endl << "v3 " << v3 << std::endl << "v4 " << v4 << std::endl;
	v2 += v3;
	v2 += 1 + egn::vec2(1);
	std::cout << v2 << " addition v2 " << std::endl;
	v2 = egn::vec2(4) - v2;
	std::cout << v2 << " subtraction v2 " << std::endl;
	v2 *= 2;
	std::cout << v2 << " multiplication by scalar v2 " << std::endl;
	std::cout << (v1 == v4) << (v1 != v2) << (v1 == v2) << (v1 != v4) << std::endl;

	///////////////////////////////////////////////////////////////////////////////////////
	std::cout << "3D Vectors" << std::endl;
	egn::vec3 v5 = egn::vec3(1);
	egn::vec3 v6 = egn::vec3(2, 0, 0);
	egn::vec3 v7 = egn::vec3();
	egn::vec3 v8 = egn::vec3();
	v7 = egn::vec3::normalize(v6);
	v8 += 1 + egn::vec3(1) + v6;
	std::cout << "v5 " << v5 << std::endl << "v6 " << v6 << std::endl << "v7 " << v7 << std::endl << "v8 " << v8 << std::endl;
	std::cout << "v5 * 3 . v6 = " << egn::vec3::dot(v5 * 3, v6) << std::endl;
	std::cout << "v7 * v8 = " << -egn::vec3::cross(v7, v8) << std::endl;
	//---------------------
	egn::vec3 v9 = egn::vec3(0.0000000001f, 0, 0);
	std::cout << "v9" << v9 << std::endl;
	v9.clean();
	std::cout << "v9" << v9 << std::endl;

	///////////////////////////////////////////////////////////////////////////////////////
	egn::vec3 vector1 = egn::vec3(1, 0, 0);
	egn::vec3 vector2 = egn::vec3(0, 2, 0);
	egn::vec3 vector3 = egn::vec3(0, 0, 3);

	egn::vec3 v = egn::vec3();
	egn::vec3 u = egn::vec3();
	egn::vec3 w = egn::vec3();
	egn::vec3 w1 = egn::vec3();
	egn::vec3 up = egn::vec3();

	egn::vec3 myVecs[3] = { vector1, vector2, vector3 };
	for (int i = 0; i < 3; i++) {
		std::cout << i << std::endl << std::endl;
		v = egn::vec3::normalize(myVecs[i]);
		for (int j = 0; j < 3; j++) {
			up = myVecs[j];
			w = egn::vec3::cross(up, v);
			w1 = egn::vec3::normalize(w);
			u = egn::vec3::cross(v, w1);
			u.clean();
			std::cout << "up " << up << " view " << myVecs[i] << " v " << v << " w " << w << " w_normalized " << w1 << " u " << u << std::endl;
			//std::cout << "v " << v << " w " << w1 << " u " << u << std::endl;
		}
	}
	*/
	egn::mat2 m0 = egn::mat2(4, 2, 7, 6);
	egn::mat2 m1 = egn::mat2(m0);
	egn::mat2 m2 = m0;
	egn::mat2 m3;
	egn::mat2 m4 = egn::mat2(1);
	m3 += m0;
	m3 += 2;
	m3 -= 1;
	m4 += m4;
	m0 *= 2;
	std::cout << m0 << inverse(m1) << transpose(m2) << m3 << m4 << std::endl;
	
	egn::vec2 v0 = egn::vec2(1, 2);
	egn::mat2 m5 = egn::mat2(1);
	egn::mat2 m6;
	m5 = 2 + m5 + 1;
	m5 = 4 - (m5 - 1);
	m6 = m5 + v0;
	std::cout << v0 << m5 << m6 << std::endl;

	egn::mat2 m7 = egn::mat2(-2, 1, 0, 4);
	egn::mat2 m8 = egn::mat2(6, 5, -7, 1);
	m7 *= m8;
	std::cout << m7 << std::endl;
}