#include "VarExcept.hpp"

VarExcept::VarExcept(std::string s)
{
    mStr = s;
}

std::string VarExcept::what() const throw()
{
    return mStr;
}
