#include "coordinate.h"

#include <iostream>


template <typename T>
void test(void)
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

int main(void)
{
	try
	{
		test<unsigned char>();		
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