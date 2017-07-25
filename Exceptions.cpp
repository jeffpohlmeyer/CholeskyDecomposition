// This file contains all of the derived error handling classes

#include "Exceptions.hpp"
#include <sstream>
#include <string>

// Base class
Exception::Exception() {}
Exception::~Exception() {}

// Derived class for a non-numeric matrix entry
NonFloatInMatrixException::NonFloatInMatrixException() {}
NonFloatInMatrixException::~NonFloatInMatrixException() {}

std::string NonFloatInMatrixException::GetMessage() const 
{
	std::stringstream ss;
	ss << "Error: There was a non-numeric value in the matrix.";
	return ss.str();
}

// Derived class for a non-symmetric matrix
NonSymmetricMatrixException::NonSymmetricMatrixException() {}
NonSymmetricMatrixException::~NonSymmetricMatrixException() {}

std::string NonSymmetricMatrixException::GetMessage() const 
{
	std::stringstream ss;
	ss << "Error: The matrix is not symmetric.";
	return ss.str();
}

// Derived class for a non-positive definite matrix
PositiveDefiniteMatrixException::PositiveDefiniteMatrixException() {}
PositiveDefiniteMatrixException::~PositiveDefiniteMatrixException() {}

std::string PositiveDefiniteMatrixException::GetMessage() const 
{
	std::stringstream ss;
	ss << "Error: The matrix is not positive definite.";
	return ss.str();
}

// Derived class for when the file to be read from csv is not in the working directory
FileReadException::FileReadException() {}
FileReadException::~FileReadException() {}

std::string FileReadException::GetMessage() const 
{
	std::stringstream ss;
	ss << "Error: The file does not exist.";
	return ss.str();
}