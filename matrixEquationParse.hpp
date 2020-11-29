#ifndef MATRIXEQUATIONPARSE_HPP
#define MATRIXEQUATIONPARSE_HPP

/*
 *  Rhys Trueman || 29/11/2020 ish
 *
 *  parses a string into an equation that can be solved
 * /

#include "Equation.hpp"
#include "Matrix.hpp"
#include <string>
#include "Workspace.hpp"

//return an equation parsed from a string, which is copied by value
Equation<Matrix> matrixEquationParse(std::string str, Workspace & w);

#endif
