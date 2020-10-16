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


	egn::mat3 m30 = egn::mat3(1, 1, 1, 2, 2, 2, 3, 3, 3);
	std::cout << "0:\n" << m30 << std::endl;
	egn::mat3 m31 = egn::mat3(m30);
	egn::mat3 m312 = egn::mat3(inverse(m31));
	m312.clean();
	std::cout << "1:\n" << m31 << "\n1(inversed):\n" << m312 << std::endl;
	egn::mat3 m32 = egn::mat3(1, 2, 3, 0, 1, 4, 5, 6, 0);
	std::cout << "2:\n" << transpose(m32) << std::endl;
	egn::mat3 m33 = inverse(m32);
	std::cout << "3:\n" << m33 << std::endl;
	egn::mat3 m34 = egn::mat3(1);
	m34 += m30;
	std::cout << "4:\n" << m34 << std::endl;
	egn::mat3 m35 = egn::mat3(1, 2, 3, 4, 5, 6, 7, 8, 9);
	std::cout << "5:\n" << m35 << std::endl;
	m35 *= m35;
	std::cout << "5*=5:\n" << m35 << std::endl;
	egn::mat3 m36 = egn::mat3();
	m36 = m30 + m35;
	std::cout << "6:\n" << m36 << std::endl;
	m36 = m36 - m35;
	std::cout << "6 - 5:\n" << m36 << std::endl;*/

	egn::mat3 m1 = egn::mat3();
	egn::mat3 m2 = egn::mat3();
	egn::mat3 m3 = egn::mat3();
	egn::mat3 m4 = egn::mat3();

	for (int k = 0; k < 10; k++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m1.data[i][j] = rand() % 100;
				m2.data[i][j] = rand() % 100;
				m3.data[i][j] = rand() % 100;
				m4.data[i][j] = rand() % 100;
			}
		}

		m1.clean();
		m2.clean();
		m3.clean();
		m4.clean();

		std::cout << "A = \n" << m1 << "\nB = \n" << m2 << "\nC = \n" << m3 << "\nD = \n" << m4 << std::endl;

		egn::mat3 ab = egn::mat3();
		ab = m1 * m2;
		std::cout << "AB:\n" << ab << std::endl;

		egn::mat3 cd = egn::mat3();
		cd = m3 * m4;
		std::cout << "CD:\n" << cd << std::endl;

		egn::mat3 left = egn::mat3();
		left = transpose(inverse(ab) * inverse(cd));
		left.clean();
		std::cout << "inverseAB:\n" << inverse(ab) << "\ninverseCD:\n" << inverse(cd) << std::endl;

		egn::mat3 dc = egn::mat3();
		dc = inverse(m4) * inverse(m3);

		egn::mat3 ba = egn::mat3();
		ba = inverse(m2) * inverse(m1);

		egn::mat3 right = egn::mat3();
		right = transpose(dc) * transpose(ba);
		right.clean();

		bool test = (left == right);
		std::cout << "left-hand side matrix:\n" << left << "\nright-hand side matrix:\n" << right << "\ncomparison: " << test << std::endl;
	}

	/*egn::mat3 m = egn::mat3(1, 2, 3, 0, 4, 5, 1, 0, 6);
	std::cout << "M:\n" << m << "\ndeterminant: " << m.determinant() << "\ninverse:\n" << inverse(m) << std::endl;*/
}