#ifndef MATRIX_HPP
#define MATRIX_HPP

/*
 *  Rhys Trueman || 29/11/2020
 *
 *  Minimal matrix class for now, may need to be expanded
 *  also TODO needs a move constructor probably
 */

#include <exception>
#include <string>
#include <iostream>

class Matrix
{
	public:
		//default for equation, gives an empty Matrix
		Matrix();
		//r by c matrix, 0 for all elements
		Matrix(int r, int c);
		//copy
		Matrix(const Matrix & m);
		//des
		~Matrix();
		//assignment
		Matrix & operator=(const Matrix & m);

		//access
		double & access(int r, int c);
		double access(int r, int c) const;
	
		//arith
		Matrix & operator+=(const Matrix & m);
		Matrix & operator-=(const Matrix & m);
		Matrix & operator*=(const Matrix & m);
		Matrix & operator/=(const Matrix & m);

		//print
		friend std::ostream & operator<<(std::ostream & os, const Matrix & m);
		//convert to string
		std::string toStr();
	private:
		double * mElements = nullptr;
		int mSize = 0, mRows = 0, mColumns = 0;
};



#endif
