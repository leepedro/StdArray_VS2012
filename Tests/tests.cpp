#include <array>
#include <iostream>

void test_type_conversion(void)
{
	std::array<int, 3> i1 = {1, 2, 3};
	std::array<int, 3> i2(i1);		// copy constructor.
	i2 = i1;						// assignment operator.

	std::array<float, 3> f1 = {11.0, 12.0, 13.0};
	//f1 = i1;		// std::array<T> cannot copy each other between different data types.

	// Next line works because of implicit conversion from int scalar to float scalar.
	std::array<float, 3> f2 = {1, 2, 3};
	
}

int main(void)
{
	try
	{
		test_type_conversion();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}