#ifndef TOKEN_HPP
#define TOKEN_HPP

/*
 *  Rhys Trueman || 8/12/2020
 *
 *  Going to be a wrapper for basically a dynamic variable
 *  Could be a matrix value, a matrix reference (to a variable in Workspace), a double, a double reference (to a variable in Workspace), a function call, etc
 */

#include "Matrix.hpp"

class Token
{
    public:
        //default constructor
        Token();
        //set the token
        //set to matrix value, takes ownership
        void setMatrix(Matrix * mat);
        //set to matrix reference, does not take value
        void setMatrixRef(Matrix * mat);
        //set to double value, takes ownership
        void setDouble(double * dub);
        //set to double reference, takes ownership
        void setDoubleRef(double * dub);
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
            MATRIXREF, //the token is a reference to a Matrix
            DOUBLE, //the token is a double value
            DOUBLEREF, //the token is a reference to a double
            FUNC, //the token represents a function call
            NONE //the token is nothing, default
        } mType;

        Matrix * mMatrix = nullptr;
        double * mDouble = nullptr;

        //clear any value owned by the Token
        void clear();
};

#endif
