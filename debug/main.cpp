#include <iostream>
#include "Equation.hpp"

int main()
{
	Equation<double> eq;

	eq.appendValue(4);
	eq.appendOp('+');
	eq.appendValue(2);

	std::cout << eq.solve() << '\n';

	return 0;
}
