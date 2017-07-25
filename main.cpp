// This is a very basic function to compute the Cholesky decomposition of a matrix using the Cholesky-Banachiewicz algorithm.
// The program checks for symmetry and positive-definiteness of the matrix.
// The initial intent was to create a GUI where the user can choose whether to print the REF and whether to print from CSV but as of submission I have not had time to finish that.

#include <iomanip>
#include <math.h>
#include "Conditions.hpp"
#include "Cholesky.hpp"
#include "Data.hpp"
#include "Exceptions.hpp"

int main()
{
	// Variable initialization
	std::vector <std::vector <float> > data, cholesky_matrix;
	bool symmetric, pos_def, print_RREF = true, csv = true;
	std::string file_name;

	std::cout << "Enter the name of the file with the original matrix to be decomposed (default is matrix.csv)." << std::endl;
	getline(std::cin, file_name);

	// Read the input matrix
	data = data_acquisition(file_name);

	std::cout << "Input matrix" << std::endl;
	print(data);
//	std::cout << std::endl;

	// Check to see if the matrix is symmetric
	symmetric_check(data);

	// Check for positive-definiteness and run decomposition and print the REF steps (hence the print_RREF boolean)
	pos_def_check(data, print_RREF);

	// If we have made it this far, calculate the decomposition and write to csv in the process (hence the csv boolean)
	// Then print the decomposed matrix
	cholesky_matrix = cholesky(data,csv);
	std::cout << "Cholesky decomposition lower triangular matrix" << std::endl;
	print(cholesky_matrix);
	std::cout << std::endl;

	return 0;
}