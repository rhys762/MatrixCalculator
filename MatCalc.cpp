#include "MatCalc.hpp"
#include "matrixEquationParse.hpp"

//the input for the user, returns a vector of strings which holds the output
std::string MatCalc::input(const std::string & userInput)
{
    auto eq = matrixEquationParse(userInput, work);
    return eq.solve().getVar().toStr();
}
