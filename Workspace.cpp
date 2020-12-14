#include "Workspace.hpp"
#include <fstream>
#include "matrixParse.hpp"

//retrieve variable name
Variable & Workspace::operator[](const std::string & str)
{
    return mVariables[str];
}

void Workspace::writeToFile(const std::string & path)
{
    std::fstream file (path, std::fstream::out);

    for(auto & it : mVariables)
    {
        file << it.first << '\n';
        file << it.second << '\n';
    }

    file.close();
}

void Workspace::readFromFile(const std::string &path)
{
    std::fstream file (path, std::fstream::in);
    std::string varName;
    std::string value;

    while(getline(file, varName))
    {
        getline(file, value);
        mVariables[varName] = Variable(matrixParse(value));
    }

    file.close();
}
