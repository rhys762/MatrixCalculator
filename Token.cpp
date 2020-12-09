#include "Token.hpp"

Token::Token()
{}//trivial, defaults set in header

//set to matrix value, takes ownership
void Token::setMatrix(Matrix * mat)
{
    clear();
    mType = MATRIX;
    mMatrix = mat;
}

//set to double value, takes ownership
void setDouble(double * dub)
{
    clear();
    mType = DOUBLE;
    mDouble = dub;
}

//set to a (variable) reference, takes ownership
void setRef(Token * ref)
{
    clear();
    mType = REF;
    mRef = ref;
}

//copy
Token::Token(const Token & other)
{

}

//assignment
Token & Token::operator=(const Token & other)
{
    //if we are a reference, we need to set the value at our reference to the value at other
    if(mType == REF)
    {
        *mRef = other;
    }
    else//otherwise shallow copy
    {
        mType = other.mType;
        if(other.mDouble)
        {

        }
    }
}

//arithmatic
Token & Token::operator+(const Token & other)
{

}

Token & Token::operator-(const Token & other)
{

}

Token & Token::operator*(const Token & other)
{

}

Token & Token::operator/(const Token & other)
{

}

//clear any value owned by the Token
void Token::clear()
{
    if(mType == MATRIX || mType == DOUBLE)
    {
        delete mMatrix;
        delete mDouble;
    }

    mMatrix = nullptr;
    mDouble = nullptr;
    mType = NONE;
}
