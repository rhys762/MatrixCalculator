#ifndef MATRIXPARSE_HPP
#define MATRIXPARSE_HPP

#include "Matrix.hpp"
#include <string>

//parse a matrix from a string, expects it to be of the form "[1, 2; 3, 4]" with commas being optional
Matrix matrixParse(const std::string & input);

#endif
