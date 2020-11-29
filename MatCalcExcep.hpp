#ifndef MATCALCEXCEP_HPP
#define MATCALCEXCEP_HPP

#include <exception>
#include <string>

class MatCalcExcep
{
    public:
        MatCalcExcep(std::string errorMesssage, std::string userInput = "", int index = -1);
        std::string what() const throw();
    private:
        //message to display describing the issue
        std::string mErrorMessage;
        //the input we took issue with
        std::string mUserInput;
        //index of the thing that we took issue with
        int mIndex;
};

#endif // MATCALCEXCEP_HPP
