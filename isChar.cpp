#include "isChar.hpp"

//returns true if the character is a letter
bool isChar(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//true if char or number
bool isCharOrNumber(char c)
{
	return isChar(c) || (c >= '0' && c <= '9'); 
}

