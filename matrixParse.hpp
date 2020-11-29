#ifndef MATRIXPARSE_HPP
#define MATRIXPARSE_HPP

/*
 *  Rhys Trueman || 29/11/2020
 *
 *  Parses an equation from a string
 */

#include "Matrix.hpp"
#include <string>

//parse a matrix from a string, expects it to be of the form "1, 2; 3, 4" with commas being optional
Matrix matrixParse(const std::string & input);

#endif
