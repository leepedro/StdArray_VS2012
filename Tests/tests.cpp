#include <array>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "safe_cast.h"

// Enables copy operation only if it is implicitly allowed.
// 1) integer -> floating && src < dst
// 2) floating -> floating && src <= dst
// 2) integer -> integer && {u -> u || s -> s} && src <= dst
template <typename T, typename U, ::size_t N>
typename std::enable_if<	
	(std::is_integral<T>::value && std::is_floating_point<U>::value && sizeof(T) < sizeof(U)) ||
	(std::is_floating_point<T>::value && std::is_floating_point<U>::value &&
	sizeof(T) <= sizeof(U)) ||
	(std::is_integral<T>::value && std::is_integral<U>::value &&
	((std::is_unsigned<T>::value && std::is_unsigned<U>::value) ||
	(std::is_signed<T>::value && std::is_signed<U>::value)) &&
	sizeof(T) <= sizeof(U)), void>::type
Copy(const std::array<T, N> &src, std::array<U, N> &dst)
{
	std::copy(src.cbegin(), src.cend(), dst.begin());
}

void test_type_conversion(void)
{
	// Scalar implicit conversion.
	float f(0.0f);
	double d(0.0);
	int i(0);
	unsigned int ui(0);
	long long l(0);
	unsigned long long ul(0);
		
	//f = i;	// warning C4244 "conversion from 'int' to 'float', possible loss of data.
	d = i;
	i = ui;		// NO WARNIG. NOT GOOD.
	ui = i;		// NO WARNIG. NOT GOOD.
	l = i;
	//i = l;		// warning C4244 "conversion from '__int64' to 'int', possible loss of data.
	ul = l;		// NO WARNIG. NOT GOOD.
	l = ul;		// NO WARNIG. NOT GOOD.

	std::array<int, 3> i1 = {1, 2, 3};
	std::array<int, 3> i2(i1);		// copy constructor.
	i2 = i1;						// assignment operator.

	std::array<double, 3> d1 = {11.0, 12.0, 13.0};
	//f1 = i1;		// std::array<T> cannot copy each other between different data types.

	// Next line works because of implicit conversion from int scalar to float scalar.
	std::array<double, 3> d2 = {21, 22, 23};

	// Next line works by copying each element through the implicit conversion!
	std::copy(i1.cbegin(), i1.cend(), d1.begin());

	// Next line throws warning C4244 pointing <xutility>
	// "conversion from 'const float' to 'int', possible loss of data"
	//std::copy(f2.cbegin(), f2.cend(), i1.begin());

	std::array<unsigned int, 3> ui1 = {4, 5, 6};
	std::array<float, 3> f1 = {11.0, 12.0, 13.0};
	std::array<long long, 3> l1 = {101, 102, 103};
	std::array<unsigned long long, 3> ul1 = {101, 102, 103};
	//Copy(i1, f1);	// error C2893 "failed to specialize function template"
	Copy(i1, d1);
	//Copy(i1, ui1);	// error C2893 "failed to specialize function template" GOOD!
	//Copy(ui1, i1);	// error C2893 "failed to specialize function template" GOOD!
	Copy(i1, l1);
	//Copy(l1, i1);	// error C2893 "failed to specialize function template"
	//Copy(l1, ul1);	// error C2893 "failed to specialize function template" GOOD!
	//Copy(ul1, l1);	// error C2893 "failed to specialize function template" GOOD!
}

template <typename T, typename U, ::size_t N>
typename std::enable_if<
	std::is_floating_point<T>::value, void>::type
round_to(const std::array<T, N> &src, std::array<U, N> &dst)
{
	auto it_src = src.cbegin();
	auto it_dst_end = dst.end();	
	for (auto it_dst = dst.begin(); it_dst != it_dst_end; ++it_src, ++it_dst)
#if _MSC_VER > 1700		// from VS2013
		*it_dst = static_cast<U>(std::round(*it_src));
#else					// up to VS2013
		if (*it_src >= 0)
			SafeCast(std::floor(*it_src + 0.5), *it_dst);
		else
			SafeCast(std::ceil(*it_src - 0.5), *it_dst);
#endif
}

void test_round_to(void)
{
	std::array<float, 3> f1 = {2.1f, 2.5f, 2.6f};
	std::array<float, 3> f2 = {-2.1f, -2.5f, -2.6f};
	std::array<double, 3> d1 = {2.1, 2.5, 2.6};
	std::array<double, 3> d2 = {-2.1, -2.5, -2.6};
	std::array<int, 3> i1 = {};
	std::array<unsigned int, 3> ui1 = {};
	round_to(f1, i1);
	std::array<int, 3> i2 = i1;
	round_to(f1, ui1);
	std::array<unsigned int, 3> ui2 = ui1;
	round_to(f2, i1);
	//round_to(f2, ui1);	// Overflow detected.
	round_to(d1, i1);
	round_to(d1, ui1);
	round_to(d2, i1);
	//round_to(d2, ui1);	// Overflow detected.
}

void test_operators(void)
{
	std::array<int, 3> i1 = {1, 2, 3}, i2 = {1, 0, 3}, i3;
	i3 = i1;
	if (i1 == i3)
		std::cout << "i1 == i3 is true" << std::endl;
	else
		std::cout << "i1 == i3 is not true" << std::endl;
	if (i1 != i2)
		std::cout << "i1 != i2 is true" << std::endl;
	else
		std::cout << "i1 != i2 is not true" << std::endl;
	//i3 = i1 + i2;		// undefined.
	std::array<long long, 3> l1;

}

int main(void)
{
	try
	{
		test_type_conversion();
		test_round_to();
		test_operators();
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}