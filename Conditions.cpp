// This file contains all functions used to determine whether the input matrix meets all needed conditions to be able to calculate the Cholesky decomposition

#include "Conditions.hpp"
#include "Data.hpp"
#include "Exceptions.hpp"
#include <ctime>

// A function which checks the lower triangular part of the matrix against its corresponding upper triangular entries to determine symmetry.
bool symmetric_matrix(const std::vector<std::vector<float> >& data)
{
	bool symmetric = true;
	int count = 0, vec_size;

	vec_size = data.size() * data[0].size();
	// Check to see if the matrix is square, if not then it cannot be symmetric
	if (data.size() != data[0].size())
		symmetric = false;
	// Run through the std::vector and check to see symmetry of values via swapped indices
	while ((count < vec_size) && symmetric)
	{
		// Iterate through the rows
		for (unsigned int i = 0; i < data.size(); ++i)
		{
			// Iterate through the columns
			for (unsigned int j = 0; j < i; ++j)
			{
				if (data[i][j] != data[j][i])
					symmetric = false;
				++count;
			}
		}
	}

	return symmetric;
}

// Error handling for checking whether a matrix is symmetric.
void symmetric_check(const std::vector<std::vector<float> >& data)
{
	bool symmetric;
	try
	{
		symmetric = symmetric_matrix(data);
		if (!symmetric)
			throw NonSymmetricMatrixException();
	}
	catch (NonSymmetricMatrixException& NSE)
	{
		std::cout << NSE.GetMessage() << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

// A function to check whether a matrix is positive definite.
// It calculates the REF of the matrix and then checks whether there are any negative pivots.
// If there are negative pivots then it returns false.
bool positive_definite(const std::vector<std::vector<float> >& data, const bool& print_RREF)
{
	bool pos_def = true;
	std::vector<std::vector<float> > RREF;
	RREF = row_reduce(data,print_RREF);
	for (unsigned int i = 0; i < RREF.size(); ++i)
	{
		if (RREF[i][i] < 0)
		{
			pos_def = false;
		}
	}
	return pos_def;
}

// Error handling for checking whether a matrix is positive definite.
void pos_def_check(const std::vector<std::vector<float> >& data, const bool& print_RREF)
{
	bool pos_def;
	try
	{
		pos_def = positive_definite(data, print_RREF);
		if (!pos_def)
			throw PositiveDefiniteMatrixException();
	}
	catch (PositiveDefiniteMatrixException& PDE)
	{
		std::cout << PDE.GetMessage() << std::endl;
		std::exit(EXIT_FAILURE);
	}

}

// This function calculates the reduced echelon form of the original matrix.
std::vector<std::vector<float> > row_reduce(const std::vector<std::vector<float> >& data, const bool& print_RREF)
{
	std::vector<std::vector<float> > RREF = data;
	const int rows = RREF.size();
	const int cols = RREF[0].size();
	bool non_zero_row = true;
	int lead = 0;

	clock_t start;
	double duration;

	start = clock();
	while (lead < rows && non_zero_row == true)
	{
		float d, m;

		for (int i = 0; i < rows; ++i) 
		{ // for each row ...
		  /* calculate divisor and multiplier */
			d = RREF[lead][lead];
			m = RREF[i][lead] / RREF[lead][lead];

			for (int j = 0; j < cols; ++j)
			{ // for each column ...
				if (i == lead)
					RREF[i][j] /= 1;
				else
					RREF[i][j] -= RREF[lead][j] * m;				// make subdiagonal non-pivot entries = 0
				if (std::abs(RREF[i][j]) < 0.00001) RREF[i][j] = 0;	// Replace very small values by 0
			}
		}

		for (unsigned int i = 0; i < RREF.size(); ++i)
		{
			float row_sum = 0;
			for (unsigned int j = 0; j < RREF[i].size(); ++j)
			{
				row_sum += RREF[i][j];
			}
			if (row_sum == 0)
				non_zero_row = false;
		}

		lead++;
		if (print_RREF)
		{
			std::cout << std::endl << "RREF Iteration " << lead << std::endl;
			print(RREF);
		}
	}
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Reduced Echelon Form Duration: " << duration << std::endl << std::endl;
	return RREF;
}