/*
 * Maximum path sum II
 *
 * By starting at the top of the triangle below and moving to adjacent
 * numbers on the row below, the maximum total from top to bottom is 23.
 *
 *    3
 *   7 4
 *  2 4 6
 * 8 5 9 3
 *
 * That is, 3 + 7 + 4 + 9 = 23.
 *
 * Find the maximum total from top to bottom in p067_triangle.txt, a 15K text
 * file containing a triangle with one-hundred rows.
 *
 * NOTE: This is a much more difficult version of Problem 18. It is not
 * possible to try every route to solve this problem, as there are 2^99
 * altogether! If you could check one trillion (10^12) routes every second, it
 * would take over twenty billion years to check them all. There is an
 * efficient algorithm to solve it. ;o)
 */

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std::string_literals;

// Forward declaration
std::vector<int> readFile(const char *filename) throw(std::runtime_error);

const char *const defaultName = "p067_triangle.txt";

int main(int argc, char **argv) {
    if(argc > 2 || (argc == 2 && argv[1] == "--help"s)) {
        std::cerr << "Usage: " << argv[0] << " [ filename ]\n";
        std::cerr << "  The default file name is " << defaultName << '\n';
        return 2;
    }

    // All numbers in the triangle from left to right and top to bottom.
    // When finished, will hold the maximum sum from the top to every element.
    std::vector<int> tri;

    try {
        using Index = decltype(tri)::size_type;

        tri = readFile(argc == 2 ? argv[1] : defaultName);
        // Check that there really is a full triangle in the file
        auto rows = static_cast<Index>(std::sqrt(8 * tri.size() + 1) - 1) / 2;
        auto expectedLength = rows * (rows + 1) / 2;
        if(expectedLength != tri.size()) {
            throw std::runtime_error("Triangle file is incomplete.");
        }
    } catch(std::runtime_error &ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    // The current row
    std::size_t row = 1;
    // Iterator to the first element in the current row
    auto first = tri.begin() + 1;

    while(first != tri.end()) {
        auto last = first + row;
        // First and last (leftmost and rightmost) numbers only have one parent
        *first += *(first - row);
        *last += *(first - 1);
        // Go through every child and add the maximum parent
        for(auto child = first + 1; child != last; ++child) {
            // Iterator to the left parent
            auto left = child - row - 1;
            *child += std::max(*left, *(left + 1));
        }
        row++;
        first += row;
    }

    // Now that we have the sum of the maximum path for every single element,
    // we just need to pick the largest one from the bottom row
    auto lastRow = row * (row - 1) / 2;
    auto max = *std::max_element(tri.begin() + lastRow, tri.end());

    std::cout << "Project Euler - Problem 67: Maximum path sum II\n\n";
    std::cout << "The greatest sum over any path from top to bottom (" << row
              << " rows) is\n"
              << max << '\n';
}

/**
 * Read all numbers from the specified file into a vector.
 *
 * @param filename The name of the file containing numbers to be read.
 * @return A vector of all numbers in the file.
 *
 * @throws std::runtime_error If the file cannot be opened.
 */
std::vector<int> readFile(const char *filename) throw(std::runtime_error) {
    std::ifstream in(filename);
    if(!in) {
        throw std::runtime_error("Failed to open triangle file.");
    }
    std::vector<int> result;
    int num;
    while(in >> num) {
        result.push_back(num);
    }
    return result;
}
