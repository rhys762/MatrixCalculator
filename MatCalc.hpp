#ifndef MATCALC_HPP
#define MATCALC_HPP

#include "Workspace.hpp"
#include <string>
#include <vector>

class MatCalc
{
	public:
		//the input for the user, returns a vector of strings which holds the output
		std::string input(const std::string & userInput);
	private:
		Workspace work;

	
};

#endif
