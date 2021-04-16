#include "IO.h"

// reads the file and returns a vector of Sequence*'s
std::vector<Sequence*> readSequences(const std::string& file_name)
{
    // vector of Sequence*'s that will hold the inputs and be returned at the end of the function
    std::vector<Sequence*> inputs;

    // open the input file
    std::ifstream source;
    source.open(file_name);

    if (!source) // if the file does not open successfully, exit with error
        exit(1);

    std::vector<std::string> lines;
    std::string line;
    std::vector<int> nameLines;
    int index = 0;

    // read through the whole file
    while (std::getline(source, line))
    {
        if (line.at(0) == '>')
            nameLines.push_back(index); // keep track of lines that start with '>'

        lines.push_back(line); // store all lines
        index++;
    }

    std::string name, sequence;

    // separate the lines into names and sequences, then store them as a Sequence* in the return vector
    for (int i = 0; i < nameLines.size(); i++)
    {
        int pos = nameLines.at(i);
        name = lines.at(pos);

        if (i == nameLines.size() - 1) // last FASTA record in the file
        {
            for (int j = pos + 1; j < lines.size(); j++)
                sequence += lines.at(j);

            inputs.push_back(new Sequence(name, sequence));

        } else { // anything but the last FASTA record in the file

            for (int j = pos + 1; j < nameLines.at(i + 1); j++)
                sequence += lines.at(j);

            inputs.push_back(new Sequence(name, sequence));
            name.clear();
            sequence.clear();
        }
    }

    // close the file
    source.close();

    // return vector of input Sequence*'s
    return inputs;
}

// writes sequences to a file
std::string writeSequencesToOutput(std::string file_name, std::vector<Sequence*> sequences)
{
    // get the current date
    time_t now = std::time(nullptr);
    tm *ltm = localtime(&now);
    std::string month = std::to_string(1 + ltm->tm_mon);
    std::string day = std::to_string(ltm->tm_mday);
    std::string year = std::to_string(1900 + ltm->tm_year);

    // add the date, a scalar, and ".fasta" to the end of the file name (to avoid overwriting output files)
    int scalar = 1;
    file_name += "_" + month + "-" + day + "-" + year + "_" + std::to_string(scalar) + ".fasta";

    // while the file name already exists
    while (std::ifstream(file_name))
    {
        // edit the name by incrementing the scalar number that comes before ".fasta"
        int nameLength = file_name.length();
        int intLength = std::to_string(scalar).length();
        file_name.erase(nameLength - intLength - 6, intLength + 6);

        file_name += std::to_string(scalar++) + ".fasta";
    }

    // open the file
    std::ofstream new_file(file_name);

    if (!new_file) // if the file does not open, return an empty string
        return "";

    // add the sequences to the file
    new_file << printSequences(sequences);

    // close the file
    new_file.close();

    // return the file name to be used later and to signify a successful write
    return file_name;
}

// reads in the distance matrix and adjusts it for UPGMA, returned as a string
std::string readDistanceMatrix(const std::string& file_name)
{
    // open the input file
    std::ifstream source;
    source.open(file_name);

    if (!source) // if the file does not open successfully, exit with error
        exit(1);

    // create vector to hold names of sequences and string to read file line-by-line
    std::vector<std::string> names;
    std::string line;

    // read the first two lines
    std::getline(source, line); // "Distance Matrix" title line; unnecessary, so ignore
    std::getline(source, line); // second line in PHYLIP format is the number of sequences
    int count = std::stoi(line); // cast and store

    // create a 2D array of dimension count x count + 1
    std::string** matrix = new std::string*[count];
    for (int i = 0; i < count; i++)
        matrix[i] = new std::string[count + 1];

    // keep track of the longest label name
    int longestLength = 0;

    // initialize a row variable
    int row = 0;
    while (std::getline(source, line)) // read each line in the file
    {
        // delimit the lines by space
        std::istringstream delimit(line);
        std::string item;

        // initialize/reset a column variable per row loop
        int column = -1;
        while (delimit >> item) // store the element in item
        {
            if (column == -1) // first column is the name
            {
                matrix[row][column + 1] = item;

                // keep track of the longest length
                if (item.length() > longestLength)
                    longestLength = item.length();

            } else { // otherwise

                if (row >= column) // set to 0 if element is on or below the diagonal
                    matrix[row][column + 1] = "0.00000";
                else // otherwise set to its value
                    matrix[row][column + 1] = item;
            }

            // increment column
            column++;
        }

        // increment row
        row++;
    }

    // close the file
    source.close();

    // matrix string to return
    std::string matrixString = "";

    // loop through the created matrix
    for (int i = 0 ; i< count; i++)
    {
        for (int j = 0; j < count + 1; j++)
        {
            // if it is the first column, which are the label names
            if (j == 0)
            {
                // adjust the length with buffer spaces to right-align all the label names
                int length = matrix[i][j].length();
                std::string buffer = "";

                for (int i = 0; i < longestLength - length; i++)
                    buffer += " ";

                matrixString += buffer + matrix[i][j] + " ";
            } else // otherwise add the matrix value
                matrixString += matrix[i][j] + " ";
        }

        matrixString += "\n";
    }

    // return the matrix string
    return matrixString;
}

// writes the adjusted matrix to an output file
std::string writeMatrixToOutput(std::string file_name, std::string matrix)
{
    // get the current date
    time_t now = std::time(nullptr);
    tm *ltm = localtime(&now);
    std::string month = std::to_string(1 + ltm->tm_mon);
    std::string day = std::to_string(ltm->tm_mday);
    std::string year = std::to_string(1900 + ltm->tm_year);

    // add the date, a scalar, and ".txt" to the end of the file name (to avoid overwriting output files)
    int scalar = 1;
    file_name += "_" + month + "-" + day + "-" + year + "_" + std::to_string(scalar) + ".txt";

    // while the file name already exists
    while (std::ifstream(file_name))
    {
        // edit the name by incrementing the scalar number that comes before ".txt"
        int nameLength = file_name.length();
        int intLength = std::to_string(scalar).length();
        file_name.erase(nameLength - intLength - 4, intLength + 4);

        file_name += std::to_string(scalar++) + ".txt";
    }

    // open the file
    std::ofstream new_file(file_name);

    if (!new_file) // if the file does not open, return an empty string
        return "";

    // add the matrix to the file
    new_file << matrix;

    // close the file
    new_file.close();

    // return the file name to be used later and to signify a successful write
    return file_name;
}
