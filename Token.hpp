#ifndef TOKEN_HPP
#define TOKEN_HPP

/*
 *  Rhys Trueman || 8/12/2020
 *
 * wrapper for a Variable, can either be L value or R value basically. Will be the template type for Equation
 */

#include <iostream>//debug

#include "Variable.hpp"

class Token
{
    public:
        //default, should really not be used..
        Token();
        //the Token represent a pure value, ie 6 or a matrix [1 2; 3 4]
        Token(const Variable & rvalue);
        //the token is refering to a variable, say "A", as such assigning or modifying this token will modify A as they are one and the same
        Token(Variable * lvalue);
        //copy
        Token(const Token & other);
        //assignment
        Token & operator=(const Token & other);
        //arithmatic
        Token & operator+=(const Token & other);
        Token & operator-=(const Token & other);
        Token & operator*=(const Token & other);
        Token & operator/=(const Token & other);
        Token operator+(const Token & B) const;
        Token operator-(const Token & B) const;
        Token operator*(const Token & B) const;
        Token operator/(const Token & B) const;

        //funcs
        //get the variable value
        Variable getVar() const;
    private:
        Variable mVar;
        //if we are actually referring to a lvalue this pointer will point to it, otherwise we are an rValue use mVar
        Variable * mRef = nullptr;
        bool fresh = true;

};

//debug
std::ostream & operator<<(std::ostream & os, const Token & tok);

#endif
