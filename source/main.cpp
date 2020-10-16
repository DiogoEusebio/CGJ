#include <iostream>
#include "../header/MasterHeader.h"


int main(int argc, char* argv[])
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Testes ao Mat2
	egn::mat2 m0 = egn::mat2();
	egn::mat2 m1 = egn::mat2(m0);
	egn::mat2 m2 = egn::mat2(4, 7, 2, 6);
	egn::mat2 m3 = egn::mat2(0.000005);

	std::cout << "construtores mat2" << m0 << '\n' << m1 << '\n' << m2 << '\n' << m3 << '\n' << m2.determinant() << std::endl;

	egn::mat2 m4 = egn::mat2();
	m4 = m3;
	m3.clean();
	std::cout << "clean e igual" << m3 << '\n' << m4 << '\n' << transpose(m2) << '\n' << inverse(m2) << std::endl;
	
	m0 += egn::mat2(5);
	egn::vec2 vec2 = egn::vec2(5, 7);
	m1 += vec2;
	m3 += 5;
	std::cout << "+=" << m0 << '\n' << m1 << '\n' << m3 << std::endl;

	m0 -= egn::mat2(5);
	m1 -= vec2;
	m3 -= 5;
	std::cout << "-=" << m0 << '\n' << m1 << '\n' << m3 << std::endl;

	m1 = m2;
	m2 *= egn::mat2(10);
	m1 *= 10;
	std::cout << "*=" << m2 << '\n' << m1 << std::endl;

	std::cout << "= +" << m1 + m2 << '\n' << m1 + vec2 << '\n' << vec2 + m1 << '\n' << 5 + m1 << '\n' << m1 + 5 << std::endl;
	std::cout << "= -" << m1 - m2 << '\n' << m1 - vec2 << '\n' << vec2 - m1 << '\n' << 5 - m1 << '\n' << m1 - 5 << std::endl;
	std::cout << "= *" << m1 * m2 << '\n' << m1 * vec2 << '\n' << vec2 * m1 << '\n' << 5 * m1 << '\n' << m1 * 5 << std::endl;

	m1 = m2;
	m3 -= 1;
	m4 = egn::mat2::identityMatrix();
	std::cout << "== != Identity\n" << (m1 == m2) << '\n' << (m3 != m2) << '\n' << m4 <<std::endl;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Testes ao Mat3

	egn::mat3 m5 = egn::mat3();
	egn::mat3 m6 = egn::mat3(m5);
	egn::mat3 m7 = egn::mat3(3, 0, 2, 2, 0, -2, 0, 1, 1);
	egn::mat3 m8 = egn::mat3(0.000005);

	std::cout << "construtores mat3" << m5 << '\n' << m6 << '\n' << m7<< '\n' << m8 << '\n' << m7.determinant() << std::endl;

	egn::mat3 m9 = egn::mat3();
	m9 = m8;
	m8.clean();
	std::cout << "clean e igual" << m8 << '\n' << m9 << '\n' << transpose(m7) << '\n' << inverse(m7) << std::endl;

	m5 += egn::mat3(5);
	egn::vec3 vec3 = egn::vec3(5, 7, 9);
	m6 += vec3;
	m9 += 5;
	std::cout << "+=" << m5 << '\n' << m6 << '\n' << m9 << std::endl;

	m5 -= egn::mat3(5);
	m6 -= vec3;
	m9 -= 5;
	std::cout << "-=" << m5 << '\n' << m6 << '\n' << m9 << std::endl;

	m6 = m7;
	m7 *= egn::mat3(10);
	m6 *= 10;
	std::cout << "*=" << m7 << '\n' << m6 << std::endl;

	std::cout << "= +" << m6 + m7 << '\n' << m6 + vec3 << '\n' << vec3 + m6 << '\n' << 5 + m6 << '\n' << m6 + 5 << std::endl;
	std::cout << "= -" << m6 - m7 << '\n' << m6 - vec3 << '\n' << vec3 - m6 << '\n' << 5 - m6 << '\n' << m6 - 5 << std::endl;
	std::cout << "= *" << m6 * m7 << '\n' << m6 * vec3 << '\n' << vec3 * m6 << '\n' << 5 * m6 << '\n' << m6 * 5 << std::endl;

	m6 = m7;
	m8 -= 1;
	m9 = egn::mat3::identityMatrix();
	egn::mat3 m10 = egn::mat3::dualMatrix(vec3);
	std::cout << "== != Identity\n" << (m6 == m7) << '\n' << (m8 != m7) << '\n' << m9 << '\n' << m10 << std::endl;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Testes ao Mat4

	egn::mat4 m11 = egn::mat4();
	egn::mat4 m12 = egn::mat4(m11);
	egn::mat4 m13 = egn::mat4(3, 0, 2, 2, 0, -2, 0, 1, 1, 2, 4, 5, 1, 2, 3, 1);
	egn::mat4 m14 = egn::mat4(0.000005);

	std::cout << "construtores mat3" << m11 << '\n' << m12 << '\n' << m13 << '\n' << m14 << std::endl;

	egn::mat4 m15 = egn::mat4();
	m15 = m14;
	m14.clean();
	std::cout << "clean e igual" << m14 << '\n' << m15 << std::endl;

	m11 += egn::mat4(5);
	egn::vec4 vec4 = egn::vec4(3, 5, 7, 9);
	m12 += vec4;
	m15 += 5;
	std::cout << "+=" << m11 << '\n' << m12 << '\n' << m15 << std::endl;

	m11 -= egn::mat4(5);
	m12 -= vec4;
	m15 -= 5;
	std::cout << "-=" << m11 << '\n' << m12 << '\n' << m15 << std::endl;

	m12 = m13;
	m13 *= egn::mat4(10);
	m12 *= 10;
	std::cout << "*=" << m13 << '\n' << m12 << std::endl;

	std::cout << "= +" << m12 + m13 << '\n' << m12 + vec4 << '\n' << vec4 + m12 << '\n' << 5 + m12 << '\n' << m12 + 5 << std::endl;
	std::cout << "= -" << m12 - m13 << '\n' << m12 - vec4 << '\n' << vec4 - m12 << '\n' << 5 - m12 << '\n' << m12 - 5 << std::endl;
	std::cout << "= *" << m12 * m13 << '\n' << m12 * vec4 << '\n' << vec4 * m12 << '\n' << 5 * m12 << '\n' << m12 * 5 << std::endl;

	m12 = m13;
	m14 -= 1;
	m15 = egn::mat4::identityMatrix();
	egn::mat4 m16 = egn::mat4::scaling(1, 2, 3, 1);
	egn::mat4 m17 = egn::mat4::translation(1, 2, 3);
	egn::mat4 m18 = egn::mat4::rotationX(2);
	egn::mat4 m19 = egn::mat4::rotationY(2);
	egn::mat4 m20 = egn::mat4::rotationZ(2);
	std::cout << "== != Identity\n" << (m12 == m13) << '\n' << (m14 != m13) << '\n' << m15 << '\n' << m16 << '\n' << m17 << '\n' << m18 << '\n' << m19 << '\n' << m20 << std::endl;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Segundo Assignment


	egn::mat3 mA = egn::mat3();
	egn::mat3 mB = egn::mat3();
	egn::mat3 mC = egn::mat3();
	egn::mat3 mD = egn::mat3();

	for (int k = 0; k < 10; k++)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				mA.data[i][j] = rand() % 10 + 1;
				mB.data[i][j] = rand() % 10 + 1;
				mC.data[i][j] = rand() % 10 + 1;
				mD.data[i][j] = rand() % 10 + 1;
			}
		}

		std::cout << "A = \n" << mA << "\nB = \n" << mB << "\nC = \n" << mC << "\nD = \n" << mD << std::endl;

		egn::mat3 ab = egn::mat3();
		ab = mA * mB;

		egn::mat3 cd = egn::mat3();
		cd = mC * mD;

		egn::mat3 left = egn::mat3();
		left = transpose(inverse(ab) * inverse(cd));

		egn::mat3 dc = egn::mat3();
		dc = inverse(mD) * inverse(mC);

		egn::mat3 ba = egn::mat3();
		ba = inverse(mB) * inverse(mA);

		egn::mat3 right = egn::mat3();
		right = transpose(dc) * transpose(ba);

		std::cout << "left-hand side matrix:\n" << left << "\nright-hand side matrix:\n" << right << "\ncomparison: " << (left == right) << std::endl;
	}

}