#include "Token.hpp"

Token::Token()
{
    mType = NONE;
}

//set to matrix value, takes ownership
void Token::setMatrix(Matrix * mat)
{
    clear();
    mType = MATRIX;
    mMatrix = mat;
}

//set to matrix reference, does not take value
void Token::setMatrixRef(Matrix * mat)
{
    clear();
    mType = MATRIXREF;
    mMatrix = mat;
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
