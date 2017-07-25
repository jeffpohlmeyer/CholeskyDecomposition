// This file includes the necessary functions for reading from and writing to csv files, as well as printing a matrix in the console.

#include "Data.hpp"
#include "Exceptions.hpp"
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <iomanip>

// A function to read the matrix from a csv into a vector of vector of floats.  Includes error handling for non-numeric matrix entries.
std::vector<std::vector<float> > read_csv(std::string file_name)
{
	std::vector <std::vector <float> > data;
	// Read in the matrix from the csv file - taken from http://www.cplusplus.com/forum/general/17771/#msg89650
	// Modified slightly to read in floats instead of std::strings
	std::ifstream infile(file_name);
	if (infile)
	{
		float entry;

		while (infile)
		{
			std::string s;
			if (!std::getline(infile, s)) break;

			std::stringstream ss(s);
			std::vector <float> record;

			while (ss)
			{
				std::string s;
				if (!getline(ss, s, ',')) break;
				try
				{
					std::istringstream sin(s);
					float input_var;
					sin >> input_var;
					if (sin)
					{
						entry = std::stof(s.c_str());
						record.push_back(entry);
					}
					else
					{
						throw NonFloatInMatrixException();
					}
				}
				catch (NonFloatInMatrixException& NFE)
				{
					std::cout << NFE.GetMessage() << std::endl;
					std::exit(EXIT_FAILURE);
				}
			}

			data.push_back(record);
		}
	}
	else 
	{
		throw FileReadException();
	}

	if (!infile.eof())
	{
		std::cerr << "Error reading file\n";
	}
	return data;
}

// A basic print function for the matrix.
void print(const std::vector<std::vector<float> >& data)
{
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		for (unsigned int j = 0; j < data[i].size(); ++j)
		{
			std::cout << std::setw(7) << std::setprecision(4) << data[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

// A file to write the original and decomposed lower triangular matrices to a csv with a pre-defined file name
void to_csv(const std::vector<std::vector<float> >& data, const std::vector<std::vector<float> >& L)
{
	std::ofstream file;
	file.open("CholeskyDecomp.csv");
	file << "Original Matrix" << std::endl;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		for (unsigned int j = 0; j < data[i].size(); ++j)
		{
			file << data[i][j];
			if (j != data.size())
				file << ", ";
		}
		file << std::endl;
	}
	file << std::endl << "Decomposition Lower Triangular Matrix" << std::endl;
	for (unsigned int i = 0; i < L.size(); ++i)
	{
		for (unsigned int j = 0; j < L[i].size(); ++j)
		{
			file << L[i][j];
			if (j != L.size())
				file << ", ";
		}
		file << std::endl;
	}
	file.close();
}

// A file to write only one matrix (the user can choose) to a csv with a pre-defined file name
void to_csv(const std::vector<std::vector<float> >& data, const std::string& name)
{
	std::ofstream file;
	file.open("CholeskyDecomp.csv");
	file << name << std::endl;
	for (unsigned int i = 0; i < data.size(); ++i)
	{
		for (unsigned int j = 0; j < data[i].size(); ++j)
		{
			file << data[i][j];
			if (j != data.size())
				file << ", ";
		}
		file << std::endl;
	}
	file.close();
}

// Function to pull in data from csv file taking an input of file_name and calling on read_csv.  This incorporates error handling in case the file name chosen does not exist.
std::vector<std::vector<float> > data_acquisition(const std::string& file_name)
{
	std::vector<std::vector<float> > data;
	if (file_name.empty())
	{
		try
		{
			data = read_csv("matrix.csv");
		}
		catch (FileReadException& FRE)
		{
			std::cout << FRE.GetMessage() << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
	else
	{
		try
		{
			data = read_csv(file_name);
		}
		catch (FileReadException& FRE)
		{
			std::cout << FRE.GetMessage() << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
	return data;
}