#include "matrixEquationParse.hpp"
#include "matrixParse.hpp"
#include "isChar.hpp"
#include "MatCalcExcep.hpp"

//return an equation parsed from a string, which is copied by value
Equation<Token> matrixEquationParse(std::string str, Workspace & w)
{

	//the equation we will build up over the parse
    Equation<Token> output;
	
	//for loops and substrs
	size_t start = 0;
	size_t len;

	//for checking operators
    const std::string operators = "*/+-()=";

	//iterate over the string
	while(start < str.length())
	{
		if(operators.find(str[start]) != std::string::npos)
		{
			//if true then str[start] is an operator
			output.appendOp(str[start]);
			start++;
		}
		else if(str[start] == '[')
		{
			//matrix open
			//iterate forward until ']'
			len = 1;
			start++;
			while((start + len) < str.length() && str[start + len] != ']')
			{
				len++;
			}
			//after exiting above, we've either found the closing bracket or hit end, which means weve got an unclosed bracket
			if(start + len == str.length())
			{
                throw MatCalcExcep("Couldnt find closing bracket", str, start - 1);
			}

			//if it was the closing bracket, send the contents to matrixParse and append to equation
            output.appendValue(Token(Variable(matrixParse(str.substr(start, len)))));
			//now move start forward
            start += (len + 1);
		}
		else if(isChar(str[start]))
		{
			//variable name
			len = 1;
			while((start + len) < str.length() && isCharOrNumber(str[start+len]))
			{
				len++;
			}

            output.appendValue(Token(&w[str.substr(start, len)]));
			start += len;
		}
		else if(str[start] == ' ')
		{
			//otherwise whitespace maybe?
			start++;
		}
		else
		{
			//unexpected char :(
            throw MatCalcExcep("unexpected character", str, start);
		}
	}

	return output;
}
