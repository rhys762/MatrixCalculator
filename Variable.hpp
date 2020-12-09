#ifndef VARAIBLE_HPP
#define VARAIBLE_HPP

/*
 *  Rhys Trueman || 9/12/2020
 *
 *  A dynamic varaible that can be either a Matrix or a double, possibly others later
 */

#include "Matrix.hpp"

class Variable
{
    public:
        //public scope because returned from pub method, possibly be moved private later
        enum TYPE
        {
            DOUBLE,
            MATRIX,
            NONE
        };

        //trivial default
        Variable();

        //create the variable and set it to a particular value
        Variable(double d);
        Variable(Matrix * m);//takes ownership so should be a unique ptr sorry bjarne xox

        //copy
        Variable(const Variable & other);

        //assignment
        Variable & operator=(const Variable & other);

        //arith
        Variable & operator+=(const Variable & other);
        Variable & operator-=(const Variable & other);
        Variable & operator*=(const Variable & other);
        Variable & operator/=(const Variable & other);

        //get the type of variable
        TYPE getType() const;
        std::string toStr() const;
    private:
        TYPE mType = NONE;
        double mDouble = 0;
        Matrix * mMatrix = nullptr;
};

//external arith
Variable operator+(Variable A, const Variable & B);
Variable operator-(Variable A, const Variable & B);
Variable operator*(Variable A, const Variable & B);
Variable operator/(Variable A, const Variable & B);

#endif
