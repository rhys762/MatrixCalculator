#ifndef TOKEN_HPP
#define TOKEN_HPP

/*
 *  Rhys Trueman || 8/12/2020
 *
 * wrapper for a Variable, can either be L value or R value basically. Will be the template type for Equation
 */

#include "Matrix.hpp"
#include "Variable.hpp"

//what an ungodly mess....

class Token
{
    public:
        //default constructor
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
        Token & operator+(const Token & other);
        Token & operator-(const Token & other);
        Token & operator*(const Token & other);
        Token & operator/(const Token & other);
    private:
        enum TYPE
        {
            MATRIX, //the token is a Matrix value
            DOUBLE, //the token is a double value
            REF, //the token is a reference to a variable
            NONE //the token is nothing, default
        } mType = NONE;

        Matrix * mMatrix = nullptr;
        double * mDouble = nullptr;
        Token * mRef = nullptr;

        //clear any value owned by the Token
        void clear();
};

#endif
