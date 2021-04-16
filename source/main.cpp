#include "IO.h"

// main function that takes in command line inputs
int main(int argc, char * argv[])
{
    if (argc < 1) // if there is less than one arguments, exit without error
    {
        std::cout << " Not enough arguments." << std::endl;
        exit(0);
    } else if (argc > 1) { // if there are too many arguments, exit without error
        std::cout << " Too many arguments." << std::endl;
        exit(0);
    } else { // if exactly one argument, continue

        // print welcome message
        std::cout << " RRRRRRRRRRRRRRRRR                  AAA         TTTTTTTTTTTTTTTTTTTTTTT\n"
                     " R::::::::::::::::R                A:::A        T:::::::::::::::::::::T\n"
                     " R::::::RRRRRR:::::R              A:::::A       T:::::::::::::::::::::T\n"
                     " RR:::::R     R:::::R            A:::::::A      T:::::TT:::::::TT:::::T\n"
                     "   R::::R     R:::::R           A:::::::::A     TTTTTT  T:::::T  TTTTTT\n"
                     "   R::::R     R:::::R          A:::::A:::::A            T:::::T        \n"
                     "   R::::RRRRRR:::::R          A:::::A A:::::A           T:::::T        \n"
                     "   R:::::::::::::RR          A:::::A   A:::::A          T:::::T        \n"
                     "   R::::RRRRRR:::::R        A:::::A     A:::::A         T:::::T        \n"
                     "   R::::R     R:::::R      A:::::AAAAAAAAA:::::A        T:::::T        \n"
                     "   R::::R     R:::::R     A:::::::::::::::::::::A       T:::::T        \n"
                     "   R::::R     R:::::R    A:::::AAAAAAAAAAAAA:::::A      T:::::T        \n"
                     " RR:::::R     R:::::R   A:::::A             A:::::A   TT:::::::TT      \n"
                     " R::::::R     R:::::R  A:::::A               A:::::A  T:::::::::T      \n"
                     " R::::::R     R:::::R A:::::A                 A:::::A T:::::::::T      \n"
                     " RRRRRRRR     RRRRRRRAAAAAAA                   AAAAAAATTTTTTTTTTT      \n" << std::endl;
        std::cout << " Welcome to Ryan's (Bioinformatics Data) Analysis Tool (RAT)!" << std::endl << std::endl;

        // create input variable and while loop for it
        int input = -1;
        while (input != 0)
        {
            // list the possible options
            std::cout << " Choose an option number:\n"
                         "\t1. Randomly split FASTA sequences into training and testing data files (80% and 20% respectively)\n"
                         "\t2. Adjust a distance matrix for UPGMA tree creation\n"
                         "\t0. Exit the program\n";

            std::cout << " > ";

            // take in user input
            std::cin >> input;

            // if the input is not valid
            if (input < 0 || input > 2)
            {
                // print an error message and continue to the next loop cycle
                std::cout << std::endl << " Invalid option.";
                continue;
            }

            // if the input is 0, print an exit message
            if (input == 0)
                std::cout << std::endl << " Exiting program." << std::endl;
            // if the input is 1
            else if (input == 1)
            {
                // take in the fasta file name
                std::string filename;
                std::cout << std::endl << " Input the FASTA file name (ex. samples.fasta):" << std::endl;
                std::cout << " Incorrect file names will exit the program." << std::endl;
                std::cout << " > ";
                std::cin >> filename;

                // read the sequences and shuffle them
                std::vector<Sequence*> sequences = readSequences(filename);
                std::random_shuffle(sequences.begin(), sequences.end());

                // calculates the number of testing sequences and prepares vectors for testing and training data respectively
                int numTest = sequences.size() / 5;
                std::vector<Sequence*> test;
                std::vector<Sequence*> train;

                // the first 80% of samples are for training while the final 20% are for testing
                for (int i = 0; i < sequences.size(); i++)
                    if (i < sequences.size() - numTest)
                        train.push_back(sequences[i]);
                    else
                        test.push_back(sequences[i]);

                // create a vector for success strings, the final file names
                std::vector<std::string> success;

                // add the file names to the vector
                success.push_back(writeSequencesToOutput("test-data", test));
                success.push_back(writeSequencesToOutput("train-data", train));

                // if both of the return strings are not empty, operation was successful and an informational message is displayed
                if (!success[0].empty() && !success[1].empty())
                    std::cout << std::endl << " Success! Refer to \"" << success[0] << "\" and \"" << success[1]
                              << "\"\n for results (located in the same directory as 123Bproject.exe)." << std::endl << std::endl;
                else // else print an error message
                    std::cout << " Error occurred. Output files could not be created/opened." << std::endl << std::endl;

                std::cout << " -------------------------------------------------------------------------------------" << std::endl << std::endl;

            } else {
                std::string filename;
                std::cout << std::endl << " Go to http://bar.utoronto.ca/webphylip/ to get a distance matrix from an aligned FASTA file." << std::endl;
                std::cout << " Please save the entire distance matrix to a txt file, including the title and number of sequences." << std::endl;
                std::cout << " Input the distance matrix txt file name (ex. distance.txt):" << std::endl;
                std::cout << " Incorrect file names will exit the program." << std::endl;
                std::cout << " > ";
                std::cin >> filename;

                std::string matrix = readDistanceMatrix(filename);
                std::string success = writeMatrixToOutput("adjusted-distance-matrix", matrix);

                // if the return string is not empty, operation was successful and an informational message is displayed
                if (!success.empty())
                    std::cout << std::endl << " Success! Refer to \"" << success << "\""
                              << "\n for results (located in the same directory as 123Bproject.exe)." << std::endl << std::endl;
                else // else print an error message
                    std::cout << " Error occurred. Output files could not be created/opened." << std::endl << std::endl;

                std::cout << " -------------------------------------------------------------------------------------" << std::endl << std::endl;
            }
        }
    }

    return 0;
}