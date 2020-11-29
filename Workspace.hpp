#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

/*
 *  Rhys Trueman || 29/11/2020
 *
 *  Just a pointless wrapper for a stdmap at the moment, but will eventually have functions,
 *  somehow....
 */

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
