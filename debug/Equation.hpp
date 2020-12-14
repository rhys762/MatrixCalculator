#ifndef EQUATION_HPP
#define EQUATION_HPP

/*
 *  Rhys Trueman 29/11/2020 ish
 *
 *  Calculates the results of equations according to BEDMAS or BODMAS or whatever its called now.
 *
 *  Requirements for the template are +, -, *, /, =
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
			T * value = nullptr;
			char op;
			token()
			{}

			~token()
			{
				delete value;
			}

			token(const token & t)
			{
				type = t.type;
				if(t.value)
				{
					value = new T (*t.value);
				}
				op = t.op;
			}

			token & operator=(const token & t)
			{
				delete value;
				value = nullptr;
				type = t.type;
				if(t.value)
				{
					value = new T (*t.value);
				}
				op = t.op;
				return *this;
			}

			token & operator=(const T & t)
			{
				delete value;
				type = T_VALUE;
				value = new T(t);
				return *this;
			}
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
	tok.value = new T (val);
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
			os << *t.value;
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
		return *mEquation[0].value;
	}

	throw std::out_of_range("could not reduce equation");
}
		
//perform an operation at index param, returns the number of tokens removed
template <typename T>
int Equation<T>::performOperationAt(int i)
{
    //the jist of this is (brackets and assignment are an exception, with brackets being extra complicated)
    //we want to resolve the equation "A + B"
    //create a new token C = A + B
    //insert C before A leaving the equation as "C A + B"
    //remove 3 elements leaving "C"
    //done

    //why not just do A += B, remove "+ B"? (like it was originally)
    //because the Token class needs to be able to represent a reference to a variable, which can modify the variable it refers to
    //in which case the equation A + 5 would actually modify the value at A which is not what i want

    //= is another exception, in that we dont actually need to insert a new token

    //jesus christ i wish i knew how to write code

    //C above is newToken
    token newToken;
    newToken.type = T_VALUE;

    //after we perform the op a varying number of elements will need to be removed
    int elementsToErase = 0;

    //used in bracket case
    int end;

	switch(mEquation[i].op)
	{
		case '(':
			end = findClosingBracket(i);
			solve(i+1, end);
			//now we should have something like ( VALUE )
            //insert the new token to the left of the left bracket (which is i)
            newToken = *mEquation[i+1].value;
            mEquation.insert(mEquation.begin() + i, newToken);
			//because the erase call removes i, which is now VALUE, increment i
			//now the number of things we removed is end - i, but we only want to remove 2
            mEquation.erase(mEquation.begin() + i + 1, mEquation.begin() + i + 4);
            return end - i - 1;
			break;
		case '*':
            newToken = *mEquation[i-1].value * *mEquation[i+1].value;
			break;
		case '/':
            newToken = *mEquation[i-1].value / *mEquation[i+1].value;
			break;
		case '+':
            newToken = *mEquation[i-1].value + *mEquation[i+1].value;
			break;
		case '-':
            newToken = *mEquation[i-1].value - *mEquation[i+1].value;
			break;
        case '=':
            *mEquation[i-1].value = *mEquation[i+1].value;
            mEquation.erase(mEquation.begin() + i, mEquation.begin() + i + 2);
            return 2;
            break;
	}

    //insert the new token
    mEquation.insert(mEquation.begin() + i - 1, newToken);

	//remove the parts of the equaiton we no longer need
    mEquation.erase(mEquation.begin() + i, mEquation.begin() + i + 3);

    return 2;//we have removed 3 tokens but added 1 for a net removal of 2
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
    performOperationsIn('=', start, end);
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
