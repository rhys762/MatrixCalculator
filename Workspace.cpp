#include "Workspace.hpp"
		
//retrieve variable name
Matrix & Workspace::operator[](const std::string & str)
{
	return variables[str];
}
