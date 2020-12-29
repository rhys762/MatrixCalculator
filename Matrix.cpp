#include "Matrix.hpp"
#include <exception>	
#include "MatCalcExcep.hpp"

//default for equation, gives an empty Matrix
Matrix::Matrix()
:mElements{nullptr}, mSize{0}, mRows{0}, mColumns{0}
{}
	
//r by c matrix, 0 for all elements
Matrix::Matrix(int r, int c)
:mElements{new double [r*c]}, mSize{r*c}, mRows{r}, mColumns{c} 
{
	for(int i = 0; i < mSize; i++)
	{
		mElements[i] = 0;
	}
}

//copy
Matrix::Matrix(const Matrix & m)
:mElements{new double [m.mSize]}, mSize{m.mSize}, mRows{m.mRows}, mColumns{m.mColumns}
{
	for(int i = 0; i < mSize; i++)
	{
		mElements[i] = m.mElements[i];
	}	
}
		
//des
Matrix::~Matrix()
{
	delete [] mElements;
    mElements = nullptr;
}

//assignment
Matrix & Matrix::operator=(const Matrix & m)
{
    //clear old data
    delete [] mElements;
    mElements = nullptr;
	
    //assign new
	mSize = m.mSize;
	mRows = m.mRows;
	mColumns = m.mColumns;
	mElements = new double [mSize];

	for(int i = 0; i < mSize; i++)
	{	
		mElements[i] = m.mElements[i];	
	}
	

	return *this;
}
		
//access
double & Matrix::access(int r, int c)
{
	return mElements[r * mColumns + c];
}

double Matrix::access(int r, int c) const
{
	return mElements[r * mColumns + c];
}

double & Matrix::access(int i)
{
    return mElements[i];
}

double Matrix::access(int i) const
{
    return mElements[i];
}

//arith
Matrix & Matrix::operator+=(const Matrix & m)
{
	if(m.mRows != mRows || m.mColumns != mColumns)
	{
        throw MatCalcExcep("Matrix+: invalid matrix sizes");
	}

	for(int i = 0; i < mSize; i++)
	{
		mElements[i] += m.mElements[i];
	}

	return *this;
}

Matrix & Matrix::operator-=(const Matrix & m)
{
	if(m.mRows != mRows || m.mColumns != mColumns)
	{
        throw MatCalcExcep("Matrix-: invalid matrix sizes");
	}

	for(int i = 0; i < mSize; i++)
	{
		mElements[i] -= m.mElements[i];
	}

	return *this;
}

Matrix & Matrix::operator*=(const Matrix & m)
{
	if(mColumns != m.mRows)
	{
        throw MatCalcExcep("Matrix*: LHS column did not match RHS row");
	}

	Matrix result (mRows, m.mColumns);
	
	for(int r = 0; r < result.mRows; r++)
	{
		for(int c = 0; c < result.mColumns; c++)
		{
			double sum = 0;

			for(int i = 0; i < mColumns; i++)
			{
				sum += (access(r, i) * m.access(i, c));
			}

			result.access(r, c) = sum;
		}
	}

	*this = result;

	return *this;
}
Matrix & Matrix::operator/=(const Matrix & m)
{
    throw MatCalcExcep("Matrix/: matricies cant be multiplied");
}
		
//print
std::ostream & operator<<(std::ostream & os, const Matrix & m)
{
    auto printRow = [&](int r)
    {
        for(int c = 0; c < m.mColumns; c++)
        {
            os << m.access(r, c) << ' ';
        }
    };

    os << '[';

    for(int r = 0; r < m.mRows - 1; r++)
	{
        printRow(r);
        os << ';';
	}
    printRow(m.mRows-1);

    os << ']';

	return os;
}
		
//convert to string
std::string Matrix::toStr()
{
	auto printRow = [&](int i)
	{
		std::string result;
		int j;
		for(j = 0; j < (mColumns-1); j++)
		{
			result += (std::to_string(access(i, j)) + ", ");
		}
		result += std::to_string(access(i, j));

		return result;
	};

	std::string str = " [" + printRow(0);
	
	for(int r = 1; r < mRows; r++)
	{
        str += ("<br>  " + printRow(r));
	}
	
    str += "]<br>";
	return str;
}

int Matrix::size() const
{
    return mSize;
}

Matrix operator+(Matrix A, const Matrix & B)
{
    return A += B;
}

Matrix operator-(Matrix A, const Matrix & B)
{
    return A -= B;
}

Matrix operator*(Matrix A, const Matrix & B)
{
    return A *= B;
}

Matrix operator/(Matrix A, const Matrix & B)
{
    return A /= B;
}
