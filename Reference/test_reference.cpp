#include <array>

int main(void)
{
	std::array<int, 3> i1 = {1, 2, 3};
	int a = i1.at(0);
	int &b = i1.at(0);
	i1.at(0) = 20;	// This line does NOT change a, but DOES change b.

	std::array<int, 3> i2 = {10, 11, 12};
	
	// The next line changes i1 and b, but does NOT change i2 because move constructor
	// is not defined for std::array<T, N> class, so the class takes it as a copy constructor.
	i1 = std::move(i2);

	// This next line does NOT change i1 and bm but DOES change i2 because i1 and b were copied
	// from i2 and ended their relation to i1.
	i2.at(0)++;
}