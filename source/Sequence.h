/* CLASS FOR HOLDING FASTA DATA */

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <time.h>

class Sequence
{
    private:
        std::string name;
        std::string sequence;

    public:
        Sequence(std::string name, std::string sequence);
        std::string getName();
        std::string getSequence();
};

std::string printSequences(std::vector<Sequence*> sequences);

#endif
