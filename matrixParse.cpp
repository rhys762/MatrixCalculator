#include "matrixParse.hpp"
#include <vector>
#include <sstream>
#include <iostream>

//parse a matrix from a string, expects it to be of the form "1, 2; 3, 4" with commas being optional
Matrix matrixParse(const std::string & input)
{
	//stream for extracting from the string
	std::stringstream inputStream(input);
	//string to put each 'row' in
	std::string rowStr;
	//place elems in here until we're ready to create a matrix
	std::vector<std::vector<double>> elems;
	
	//the dimensions of the matrix we will be returning
	int rows = 0, columns = -1;

	//semi colon seperates rows
	while(getline(inputStream, rowStr, ';'))
	{
		//add an extra row
		rows++;
		elems.emplace_back();

		//change all comma's to spaces, its convienent but not efficient \o/
		for(auto & c : rowStr)
		{
			if(c == ',')
			{
				c = ' ';
			}
		}

		//now turn the row string into a string stream and extract each number 1 by 1
		std::stringstream rowStream(rowStr);
		std::string elem;
	
		while(rowStream >> elem)
		{
			elems[rows-1].push_back(std::stod(elem));
		}

		if(columns < 0)
		{
			columns = elems[rows-1].size();
		}
		else
		{
			if(elems[rows-1].size() != columns)
			{
				throw 1;
			}
		}
	}


	//string has been parsed and columns of each row match, create and fill matrix:	
	Matrix output (rows, columns);

	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < columns; c++)
		{
			output.access(r,c) = elems[r][c];
		}
	}

	return output;
}
