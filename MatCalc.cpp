#include "MatCalc.hpp"
#include "matrixEquationParse.hpp"
#include <fstream>

//the input for the user, returns a vector of strings which holds the output
std::string MatCalc::input(const std::string & userInput)
{
    auto eq = matrixEquationParse(userInput, mWork);
    return eq.solve().getVar().toStr();
}

void MatCalc::saveWorkspace(const std::string &path)
{
    mWork.writeToFile(path);
}
