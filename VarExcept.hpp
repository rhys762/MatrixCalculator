#ifndef VAREXCEPT_HPP
#define VAREXCEPT_HPP

#include <string>

class VarExcept
{
public:
    VarExcept(std::string s);
    std::string what() const throw();
private:
    std::string mStr;
};

#endif
