#include <iostream>
#include "../header/Vector.h"

int main(int argc, char* argv[])
{
	std::cout << "CGJ vectors | delivery 1" << std::endl;
	std::cout << "2D Vectors" << std::endl;
	egn::vec2 v1 = egn::vec2(1);
	egn::vec2 v2 = egn::vec2();
	egn::vec2 v3 = egn::vec2(1, 0);
	egn::vec2 v4 = egn::vec2(1, 1);
	std::cout << "v1 " << v1 << std::endl << "v2 " << v2 << std::endl << "v3 " << v3 << std::endl << "v4 " << v4 << std::endl;
	v2 += v3;
	v2 += 1;
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
	egn::vec3 v8 = egn::vec3(0, 1, 0);
	v7 = egn::normalize(v6);
	std::cout << "v5 " << v5 << std::endl << "v6 " << v6 << std::endl << "v7 " << v7 << std::endl << "v8 " << v8 << std::endl;
	std::cout << "v5 * 3 . v6 = " << egn::dot(v5 * 3, v6) << std::endl;
	std::cout << "v7 * v8 = " << -egn::cross(v7, v8) << std::endl;
	//---------------------
	egn::vec3 v9 = egn::vec3(0.0000000001, 0, 0);
	std::cout << "v9" << v9 << std::endl;
	v9.clean();
	std::cout << "v9" << v9 << std::endl;
}