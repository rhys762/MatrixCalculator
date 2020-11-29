#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include <map>
#include <string>
#include "Matrix.hpp"

class Workspace
{
	public:
		//retrieve variable name
		Matrix & operator[](const std::string & str);		
	private:
		//the list of variables in the workspace
		std::map<std::string, Matrix> variables;

};

#endif
