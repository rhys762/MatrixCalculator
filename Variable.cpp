#include "Variable.hpp"

//trivial default
Variable::Variable()
{}

//create the variable and set it to a particular value
Variable::Variable(double d)
{
    mType = DOUBLE;
    mDouble = d;
}

Variable::Variable(Matrix * m)//takes ownership so should be a unique ptr sorry bjarne xox TODO change to unique ptr
{
    mType = MATRIX;
    mMatrix = m;
}

//copy
Variable::Variable(const Variable & other)
{
    if((mType = other.mType) == MATRIX)
    {//if matrix
        mMatrix = new Matrix(other.mMatrix);
    }
    else
    {//if double
        mDouble = other.mDouble;
    }
}

//assignment
Variable & Variable::operator=(const Variable & other)
{
    if(mMatrix)
    {
        delete mMatrix;
        mMatrix = nullptr;
    }

    if((mType = other.mType) == MATRIX)
    {//if matrix
        mMatrix = new Matrix(other.mMatrix);
    }
    else
    {//if double
        mDouble = other.mDouble;
    }

    return *this;
}

//arith
Variable & Variable::operator+=(const Variable & other)
{
    //we cannot add a matrix and a double, so these need to match
    if(mType == other.mType)
    {
        if(mType == MATRIX)
        {//matrix
            *mMatrix += *other.mMatrix;
        }
        else
        {//double
            mDouble += mDouble;
        }
        return *this;
    }

    throw VarExcept("Tried to add a double and a matrix");
}

Variable & Variable::operator-=(const Variable & other)
{
    //we cannot subtract a matrix and a double, so these need to match
    if(mType == other.mType)
    {
        if(mType == MATRIX)
        {//matrix
            *mMatrix -= *other.mMatrix;
        }
        else
        {//double
            mDouble -= mDouble;
        }
        return *this;
    }

    throw VarExcept("Tried to subtract with a double and a matrix");
}

Variable & Variable::operator*=(const Variable & other)
{
    if(mType == other.mType)
    {
        if(mType == MATRIX)
        {
            *mMatrix *= *other.mMatrix;
        }
        else
        {
            mDouble *= mDouble;
        }
    }
    else
    {
        //we need to multiply each element in the matrix by the double
        Matrix m;
        double d;

        if(mType == MATRIX)
        {
            m = *mMatrix;
            d = other.mDouble;
        }
        else
        {
            m = *other.mMatrix;
            d = mDouble;
        }

        for(int i = 0; i < m.size(); i++)
        {
            m.access(i) *= d;
        }

        mType = MATRIX;
        if(mMatrix)
        {
            delete mMatrix;
        }
        mMatrix = new Matrix(m);
    }
    return *this;
}

Variable & Variable::operator/=(const Variable & other)
{
    throw VarExcept("cant multiply a matrix");
}

//get the type of variable
TYPE Variable::getType()
{
    return mType;
}

//external arith
Variable Variable::operator+(Variable A, const Variable & B)
{
    return A += B;
}

Variable Variable::operator-(Variable A, const Variable & B)
{
    return A -= B;
}

Variable Variable::operator*(Variable A, const Variable & B)
{
    return A *= B;
}

Variable Variable::operator/(Variable A, const Variable & B)
{
    return A /= B;
}
