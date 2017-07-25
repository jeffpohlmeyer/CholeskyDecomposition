#ifndef CONDITIONS_HPP
#define CONDITIONS_HPP

#include <iostream>
#include <vector>

bool symmetric_matrix(const std::vector<std::vector<float> >&);
bool positive_definite(const std::vector<std::vector<float> >&,const bool&);
std::vector<std::vector<float> > row_reduce(const std::vector<std::vector<float> >&, const bool&);

void symmetric_check(const std::vector<std::vector<float> >&);
void pos_def_check(const std::vector<std::vector<float> >&, const bool&);

#endif // !CONDITIONS_HPP
