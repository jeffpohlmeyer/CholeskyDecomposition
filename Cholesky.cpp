#include "Cholesky.hpp"
#include "Data.hpp"

std::vector<std::vector<float> > cholesky(const std::vector<std::vector<float> >& data, const bool& csv)
{
	// Logic taken from https://en.wikipedia.org/wiki/Cholesky_decomposition#The_Cholesky.E2.80.93Banachiewicz_and_Cholesky.E2.80.93Crout_algorithms
	// Calculation performed via the Cholesky-Banachiewicz (row-by-row) algorithm

	// Initialize the output matrix
	std::vector<std::vector<float> > L(data.size(), std::vector<float>(data[0].size(), 0));

	// Set the first diagonal value equal to the square root of the first diagonal of the input matrix
	L[0][0] = sqrt(data[0][0]);

	// Iterate through rows
	for (unsigned int i = 1; i < L.size(); ++i)
	{
		// Iterate through columns
		for (unsigned int j = 0; j <= i; ++j)
		{
			// Create sum variable to account for summed "prior" entries that may be necessary to include
			float sum_elements = 0;
			// Diagonal entry logic
			if (i == j)
			{
				// Calculate the squares of prior entries in the i-th row
				for (unsigned int k = 0; k < j; ++k)
				{
					sum_elements += pow(L[j][k], 2);
				}
				// Input diagonal value minus sum of squares of other row entries
				L[i][j] = sqrt(data[i][j] - sum_elements);
			}
			else
			{
				// This part was included to deal with the "k < j" part of the loop.  If we're at the first column of a given row then "sum_elements" should stay = 0
				if (j != 0)
				{
					for (unsigned int k = 0; k < j; ++k)
					{
						sum_elements += (L[i][k] * L[j][k]);
					}
				}
				L[i][j] = (1 / L[j][j]) * (data[i][j] - sum_elements);
			}
		}
	}
	if (csv)
		to_csv(data, L);
	return L;
}
