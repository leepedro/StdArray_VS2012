#include "coordinate.h"

#include <iostream>


template <typename T>
void test1(void)
{
	std::array<T, 2> a1;
	std::array<T, 2> a2 = {0, 0};
	std::array<T, 2> a3 = {1, 2};
	//a1 = a2 + a3;

	//Cartesian<T, 2> c1;
	//Cartesian<T, 2> c2();
	//Cartesian<T, 2> c3 = {0, 0};

	Cartesian2D<T> c1;
	T x = c1.x;
	T y = c1.y;	
	Cartesian2D<T> c2(1, 2);
	x = c2.x;
	y = c2.y;
	c2.y++;
	c2.y = 0;
	c1 = c2;
	Cartesian2D<T> c3(c1);

	Add(c1, c2, c3);
	//c1 = c2 + c3;
}

void test_type_convert(void)
{
	double f1;
	int i1(2);
	f1 = i1;
	Cartesian2D<double> c_f1(1, 2);
	Cartesian2D<double> c_f2;
	Cartesian2D<int> c_i_1(2, 1);
	
	// Next line won't compile because there is no Cartesian2D<T> to std::array<> conversion.
	//c_f2 = c_i_1;
}

int main(void)
{
	try
	{
		test1<unsigned char>();
		test_type_convert();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception." << std::endl;
	}
}