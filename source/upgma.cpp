#include "upgma.h"

// returns the root of the phylogenetic tree
PhyloNode* upgma(std::string** matrix)
{
    // get the rows and columns
        // DOES NOT WORK DUE TO HOW std::string** WORKS
    int rows = sizeof matrix / sizeof matrix[0];
    int columns = sizeof matrix[0] / sizeof matrix[0][0];
    PhyloNode* root = nullptr; // create a nullptr PhyloNode* to be the root

    // while there are more than 2 columns left in the matrix
    while (columns > 2)
    {
        int index;
        float min = std::numeric_limits<float>::max();

        // loop through the first row, except for the first element
        for (int i = 1; i < columns; i++)
        {
            float value = std::stof(matrix[0][i]);

            if (value < min)
            {
                // find the minimum and keep track of its index
                min = value;
                index = i;
            }
        }

        // update the root
        root = createTree(matrix, rows, columns, min, index, root);

        // simplify the matrix
        matrix = simplifyMatrix(matrix, rows, columns, index);

        // decrement rows and columns accordingly
        rows -= 2;
        columns -= 1;
    }

    // return the root of the final tree
    return root;
}

// creates each branch of the tree
PhyloNode* createTree(std::string** matrix, int rows, int columns, float min, int index, PhyloNode* root)
{
    // calculate the height
    float height = min / 2;

    // create a new PhyloNode from using the height and index
    PhyloNode* left = new PhyloNode(0, nullptr, nullptr, matrix[rows - 1][index]);

    // if the root is nullptr, add the first element as a node and join them
    if (root == nullptr)
    {
        PhyloNode* right = new PhyloNode(0, nullptr, nullptr, matrix[rows - 1][0]);
        return new PhyloNode(height, left, right, "");
    } else { // if there is a root, just join the nodes
        return new PhyloNode(height, left, root, "");
    }
}

// simplifies the matrix for each
std::string** simplifyMatrix(std::string** matrix, int rows, int columns, int index)
{
    // create a 2D array of dimension rows - 2 x columns - 1
    std::string** simplified = new std::string*[rows - 2];
    for (int i = 0; i < rows - 2; i++)
        matrix[i] = new std::string[columns - 1];

    // vector for holding averages for the new column
    std::vector<float> averages;

    // loop through the columns, excluding the first one which would be blank/0
    for (int i = 1; i < columns; i++)
    {
        // ignore the column that is index
        if (i == index)
            continue;

        // calculate and store the average between the (0th row, ith column) and (index row, ith column)
        averages.push_back((std::stof(matrix[0][i]) + std::stof(matrix[index][i])) / 2);
    }

    // create indexing variables for the simplified matrix
    int x = 0;
    int y = 0;
    for (int i = 1; i < rows; i++) // loop through the rows of the original matrix
    {
        // skip the row that has index
        if (i == index)
            continue;

        for (int j = 1; j < columns; j++) // loop through the columns of the original matrix
        {
            // if it is the final column, take the respective value from averages
            if (y == columns - 1)
                simplified[x][y] = std::to_string(averages[x]);
            else // otherwise take the original matrix's value
                simplified[x][y] = matrix[i][j];

            // increment y
            y++;
        }

        // increment x
        x++;
    }

    // return the simplified matrix
    return simplified;
}