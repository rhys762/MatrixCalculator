#include "MatCalcExcep.hpp"
#include <iostream>//debug

MatCalcExcep::MatCalcExcep(std::string errorMesssage, std::string userInput, int index)
    :mErrorMessage{errorMesssage}, mUserInput{userInput}, mIndex{index}
{}

std::string MatCalcExcep::what() const throw()
{
    std::string result = (mErrorMessage + "\n");

    if(mUserInput.length())
    {
        result += (mUserInput + "\n");
    }

    if(mIndex >= 0)
    {
        for(int j = 0; j < mIndex; j++)
        {
            result += " ";
        }

        result += "^\n";
    }

    std::cout << result;
    return result;
}
