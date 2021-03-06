#if !defined(COORDINATE_H)
#define COORDINATE_H

#include <array>

/* A template based array classs is derived from std::array<T, N> class.
DESIGN GOAL:
An easy to use 2-member array class with overloaded operators such as pt3 = pt1 + pt2.
*/
template <typename T>
class Cartesian2D : public std::array<T, 2>
{
public:
	Cartesian2D(void);

	template <typename U>
	Cartesian2D(const Cartesian2D<U> &src);

	template <typename U>
	Cartesian2D<T> &operator=(const Cartesian2D<U> &src);

	Cartesian2D(T x, T y);
	//Cartesian2D(const std::array<T, 2> &src);
	
	T &x, &y;
};


template <typename T>
Cartesian2D<T>::Cartesian2D(void) : x(this->at(0)), y(this->at(1)) {}

template <typename T> template <typename U>
Cartesian2D<T>::Cartesian2D(const Cartesian2D<U> &src) :
	std::array<T, 2>(src), x(this->at(0)), y(this->at(1)) {}

template <typename T> template <typename U>
Cartesian2D<T> &Cartesian2D<T>::operator=(const Cartesian2D<U> &src)
{
	this->std::array<T, 2>::operator=(src);
	return *this;
}

// Delegation constructor is possible from VS2013, so we can't use it here.
template <typename T>
#if _MSC_VER > 1700	// from VS2013
Cartesian2D<T>::Cartesian2D(T x, T y) : Cartesian2D<T>()
#else				// up to VS2012
Cartesian2D<T>::Cartesian2D(T x, T y) : x(this->at(0)), y(this->at(1))
#endif
{
	this->x = x;
	this->y = y;
}

// Unusual constructor to allow an explicit conversion Cartesian2D = std::array format.
//template <typename T>
//Cartesian2D<T>::Cartesian2D(const std::array<T, 2> &src) :
//	std::array<T, 2>(src), x(at(0)), y(at(1)) {}

template <typename T, typename U, ::size_t N>
void Add(const std::array<T, N> &a, const std::array<T, N> &b, std::array<U, N> &c)
{
	auto it_a = a.cbegin();
	auto it_b = b.cbegin();
	auto it_c_end = c.end();
	for (auto it_c = c.begin(); it_c != it_c_end; ++it_a, ++it_b, ++it_c)
		*it_c = *it_a + *it_b;
}

template <typename T, ::size_t N>
std::array<T, N> operator+(const std::array<T, N> &a, const std::array<T, N> &b)
{
	std::array<T, N> c;
	auto it_a = a.cbegin();
	auto it_b = b.cbegin();
	auto it_c_end = c.end();
	for (auto it_c = c.begin(); it_c != it_c_end; ++it_a, ++it_b, ++it_c)
		*it_c = *it_a + *it_b;
	return c;
}
#endif
