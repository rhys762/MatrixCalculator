#include "Workspace.hpp"
		
//retrieve variable name
Variable & Workspace::operator[](const std::string & str)
{
	return variables[str];
}
