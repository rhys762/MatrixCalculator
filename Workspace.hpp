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
#include "Variable.hpp"

class Workspace
{
	public:
		//retrieve variable name
        Variable & operator[](const std::string & str);

        //write the workspace to file
        void writeToFile(const std::string & path);

        //read a workspace from file
        void readFromFile(const std::string & path);
	private:
		//the list of variables in the workspace
        std::map<std::string, Variable> mVariables;

};

#endif
