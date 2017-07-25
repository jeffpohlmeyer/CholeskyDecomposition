#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <vector>
#include <string>

std::vector<std::vector<float> > read_csv(std::string);
void print(const std::vector<std::vector<float> >&);

void to_csv(const std::vector<std::vector<float> >&, const std::vector<std::vector<float> >&);	// Prints original and lower triangular matrix to csv
void to_csv(const std::vector<std::vector<float> >&, const std::string&);						// Prints one matrix with matrix name to csv

std::vector<std::vector<float> > data_acquisition(const std::string&);


#endif // !DATA_HPP
