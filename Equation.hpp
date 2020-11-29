#ifndef EQUATION_HPP
#define EQUATION_HPP

/*
 *  Rhys Trueman 29/11/2020 ish
 *
 *  Calculates the results of equations according to BEDMAS or BODMAS or whatever its called now.
 *  Oh but it cant do operators yet
 */

#include <iostream>
#include <vector>
#include <exception>

template <typename T>
class Equation
{
	public:
		//append an op to the equation
		void appendOp(char op);
		//append a value to the equation
		void appendValue(const T & val);

		//print
		template <typename U>
		friend std::ostream & operator<<(std::ostream & os, const Equation<U> & eq);

		//solve the equation, throws exception if it cant reduce the equation to a single value token
		T solve();
	private:
		//enum for tokens
		enum TYPE
		{
			T_VALUE,
			T_OPERATOR
		};

		//tokens, for tokenizing the equation
		struct token
		{
			TYPE type;
			T value;
			char op;
		};

		//the equation to be solved
		std::vector<token> mEquation;

		//perform an operation at index param, returns the number of tokens removed
		int performOperationAt(int i);

		//perform all operations of type op, on [start, end), which serve as in out paramaters
		void performOperationsIn(char op, int & start, int & end);

		//solve the equation (ie calculate operators in bedmas) on [start, end)
		void solve(int start, int end);

		//find the closing bracket, to the bracket open at i, returns -1 on no close
		int findClosingBracket(int i);
};
		
//append an op to the equation
template <typename T>
void Equation<T>::appendOp(char op)
{
	token tok;
	tok.type = T_OPERATOR;
	tok.op = op;
	mEquation.push_back(tok);
}

//append a value to the equation
template <typename T>
void Equation<T>::appendValue(const T & val)
{
	token tok;
	tok.type = T_VALUE;
	tok.value = val;
	mEquation.push_back(tok);
}

//print
template <typename U>
std::ostream & operator<<(std::ostream & os, const Equation<U> & eq)
{
	for(auto & t : eq.mEquation)
	{
		if(t.type == Equation<U>::T_VALUE)
		{
			os << t.value;
		}
		else if(t.type == Equation<U>::T_OPERATOR)
		{
			os << t.op;
		}
	}
	return os;
}
		
//solve the equation, throws exception if it cant reduce the equation to a single value token
template <typename T>
T Equation<T>::solve()
{
	solve(0, mEquation.size());

	if(mEquation.size() == 1 && mEquation[0].type == T_VALUE)
	{
		return mEquation[0].value;
	}

	throw std::out_of_range("could not reduce equation");
}
		
//perform an operation at index param, returns the number of tokens removed
template <typename T>
int Equation<T>::performOperationAt(int i)
{
	//after we perform the op a varying number of elements will need to be removed
	int elementsToErase = 0;
	int end;

	switch(mEquation[i].op)
	{
		case '(':
			end = findClosingBracket(i);
			i++;
			solve(i, end);
			//now we should have something like ( VALUE )
			//move the value to the left bracket (which is i)
			mEquation[i-1] = mEquation[i];
			//because the erase call removes i, which is now VALUE, increment i
			//now the number of things we removed is end - i, but we only want to remove 2
			mEquation.erase(mEquation.begin() + i, mEquation.begin() + i + 2);
			return end - i;
			break;
		case '*':
			mEquation[i-1].value *= mEquation[i+1].value;
			elementsToErase = 2;
			break;
		case '/':
			mEquation[i-1].value /= mEquation[i+1].value;
			elementsToErase = 2;
			break;
		case '+':
			mEquation[i-1].value += mEquation[i+1].value;
			elementsToErase = 2;
			break;
		case '-':
			mEquation[i-1].value -= mEquation[i+1].value;
			elementsToErase = 2;
			break;
	}

	//remove the parts of the equaiton we no longer need
	mEquation.erase(mEquation.begin() + i, mEquation.begin() + i + elementsToErase);
	return elementsToErase;
}
		
//perform all operations of type op, on [start, end), which serve as in out paramaters
template <typename T>
void Equation<T>::performOperationsIn(char op, int & start, int & end)
{
	int i = end;

	while(--i >= start)
	{
		if(mEquation[i].type == T_OPERATOR && mEquation[i].op == op)
		{
			end -= performOperationAt(i);//update end
		}
	}
}
		
//solve the equation (ie calculate operators in bedmas) on [start, end)
template <typename T>
void Equation<T>::solve(int start, int end)
{
	performOperationsIn('(', start, end);
	performOperationsIn('*', start, end);
	performOperationsIn('/', start, end);
	performOperationsIn('+', start, end);
	performOperationsIn('-', start, end);
}
		
//find the closing bracket, to the bracket open at i, returns -1 on no close
template <typename T>
int Equation<T>::findClosingBracket(int i)
{
	int openBracks = 1;
	const int sz = mEquation.size();//returns size_t, doing cast every iteration seems dumb

	while(++i < sz)
	{
		if(mEquation[i].type == T_OPERATOR)
		{
			if(mEquation[i].op == '(')
			{
				openBracks++;
			}
			else if(mEquation[i].op == ')')
			{
				openBracks--;
				if(!openBracks)//if zero then we've found the closing bracket
				{
					return i;
				}
			}
		}
	}

	return -1;//err
}

#endif
