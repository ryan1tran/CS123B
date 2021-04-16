/* HEADER FILE FOR INPUT/OUTPUT FUNCTIONS */

#ifndef IO_H
#define IO_H

#include "Sequence.h"
#include <fstream>
#include <iomanip>
#include <sstream>

std::vector<Sequence*> readSequences(const std::string& file_name);
std::string writeSequencesToOutput(std::string file_name, std::vector<Sequence*> sequences);
std::string readDistanceMatrix(const std::string& file_name);
std::string writeMatrixToOutput(std::string file_name, std::string matrix);

#endif
