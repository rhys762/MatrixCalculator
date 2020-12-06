#include "MatCalc.hpp"
#include "matrixEquationParse.hpp"

//the input for the user, returns a vector of strings which holds the output
std::string MatCalc::input(const std::string & userInput)
{

	//first check if there is an assignment, if not we store in variable called ans by default
	std::string target = "ans";

	size_t assLoc = userInput.find('=');

	if(assLoc != std::string::npos)
	{
		//there should be a valid variable name to the left of the assignment
		target = userInput.substr(0, assLoc);

		//trim whitespace left
		size_t i = 0;
		while(i < target.length() && target[i] == ' ')
		{
			i++;
		}
		//trim whitespace right
		size_t j = target.length() - 1;
		while(j >= 0 && target[j] == ' ')
		{
			j--;
		}
		target = target.substr(i, j - i + 1);
	}
	auto eq = matrixEquationParse(userInput.substr(assLoc+1), work);
	work[target] = eq.solve();

    std::string output = target + " =<br>";
	output += work[target].toStr();
	return output;
}
