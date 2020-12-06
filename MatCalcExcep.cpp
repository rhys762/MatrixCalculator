#include "MatCalcExcep.hpp"
#include <iostream>//debug

MatCalcExcep::MatCalcExcep(std::string errorMesssage, std::string userInput, int index)
    :mErrorMessage{errorMesssage}, mUserInput{userInput}, mIndex{index}
{}

std::string MatCalcExcep::what() const throw()
{
    std::string result = (mErrorMessage + "<br>");

    if(mUserInput.length() && mIndex >= 0)
    {
        //display character mIndex in red and bold
        result += (mUserInput.substr(0, mIndex) + "<b style=\"color: red\">" + mUserInput[mIndex] + "</b>" + mUserInput.substr(mIndex+1) + "<br>");
    }
    else if(mUserInput.length())
    {
        result += (mUserInput + "<br>");
    }

    return result;
}
