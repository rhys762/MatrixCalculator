#include "Token.hpp"

//default, should really not be used..
Token::Token()
{}

//the Token represent a pure value, ie 6 or a matrix [1 2; 3 4]
Token::Token(const Variable & rvalue)
{
    mVar = rvalue;
    std::cout << "created value token with \"" << mVar.toStr() << "\"\n";
}

//the token is refering to a variable, say "A", as such assigning or modifying this token will modify A as they are one and the same
Token::Token(Variable * lvalue)
{
    mRef = lvalue;
}

//assignment
Token & Token::operator=(const Token & other)
{
    Variable v;
    if(other.mRef)
    {
        v = *mRef;
    }
    else
    {
        v = mVar;
    }

    if(mRef)
    {
        *mRef = v;
    }
    else
    {
        mVar = v;
    }
    return *this;
}

//arithmatic
Token & Token::operator+=(const Token & other)
{
    Variable v = (other.mRef) ? (*other.mRef) : (other.mVar);

    if(mRef)
    {
        *mRef += v;
    }
    else
    {
        mVar += v;
    }

    return *this;
}

Token & Token::operator-=(const Token & other)
{
    Variable v = (other.mRef) ? (*other.mRef) : (other.mVar);

    if(mRef)
    {
        *mRef -= v;
    }
    else
    {
        mVar -= v;
    }

    return *this;
}

Token & Token::operator*=(const Token & other)
{
    Variable v = (other.mRef) ? (*other.mRef) : (other.mVar);

    if(mRef)
    {
        *mRef *= v;
    }
    else
    {
        mVar *= v;
    }

    return *this;
}

Token & Token::operator/=(const Token & other)
{
    Variable v = (other.mRef) ? (*other.mRef) : (other.mVar);

    if(mRef)
    {
        *mRef /= v;
    }
    else
    {
        mVar /= v;
    }

    return *this;
}

Token Token::operator+(const Token & B) const
{
    Variable a = (mRef) ? (*mRef) : (mVar);
    Variable b = (B.mRef) ? (*B.mRef) : (B.mVar);
    Variable c = a + b;
    return c;
}

Token Token::operator-(const Token & B) const
{
    Variable a = (mRef) ? (*mRef) : (mVar);
    Variable b = (B.mRef) ? (*B.mRef) : (B.mVar);
    Variable c = a - b;
    return c;
}

Token Token::operator*(const Token & B) const
{
    Variable a = (mRef) ? (*mRef) : (mVar);
    Variable b = (B.mRef) ? (*B.mRef) : (B.mVar);
    Variable c = a * b;
    return c;
}

Token Token::operator/(const Token & B) const
{
    Variable a = (mRef) ? (*mRef) : (mVar);
    Variable b = (B.mRef) ? (*B.mRef) : (B.mVar);
    Variable c = a / b;
    return c;
}

//get the variable value
Variable Token::getVar() const
{
    return (mRef) ? (*mRef) : (mVar);
}

//debug
std::ostream & operator<<(std::ostream & os, const Token & tok)
{
    os << tok.getVar().toStr();
    return os;
}
