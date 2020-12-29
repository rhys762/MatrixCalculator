#ifndef MATCALC_HPP
#define MATCALC_HPP

/*
 *  Rhys Trueman || 29/11/2020
 *  Holds the interface avaliable to the user
 *  should handle user text input (check)
 *  save and load workspaces (variable sets essentially) (TODO)
 */

#include "Workspace.hpp"
#include <string>
#include <vector>

class MatCalc
{
	public:
		//the input for the user, returns a vector of strings which holds the output
		std::string input(const std::string & userInput);

        //save the current workspace to the destination path
        void saveWorkspace(const std::string & path);

        //opens a workspace from a destination path
        void openWorkspace(const std::string & path);
	private:
        //the workspace currently open
        Workspace mWork;
};

#endif
