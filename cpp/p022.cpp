/*
 * Names scores
 *
 * Using names.txt, a 46K text file containing over five-thousand first names,
 * begin by sorting it into alphabetical order. Then working out the
 * alphabetical value for each name, multiply this value by its alphabetical
 * position in the list to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which
 * is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN
 * would obtain a score of 938 × 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 */

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std::string_literals;

std::vector<std::string> readFile(const char *filename) throw(
        std::runtime_error);

const char *const defaultName = "p022_names.txt";

int main(int argc, char **argv) {
    if(argc > 2 || (argc == 2 && argv[1] == "--help"s)) {
        std::cerr << "Usage: " << argv[0] << " [ filename ]\n";
        std::cerr << "  The default file name is " << defaultName << '\n';
        return 2;
    }

    std::vector<std::string> names;
    try {
        names = readFile(argc == 2 ? argv[1] : defaultName);
    } catch(std::runtime_error &ex) {
        std::cerr << ex.what() << '\n';
        return 1;
    }
    std::sort(names.begin(), names.end());

    auto nameScore = [i = 1](unsigned total, const std::string &name) mutable {
        auto score = std::accumulate(name.begin(), name.end(), 0,
                [](int sum, char c) { return sum + (c - 'A' + 1); });
        return total + score * i++;
    };
    auto total = std::accumulate(names.begin(), names.end(), 0u, nameScore);

    std::cout << "Project Euler - Problem 22: Names scores\n\n";
    std::cout << "The total score is " << total << '\n';
}

/**
 * Read all names from the specified file into a vector.
 *
 * @param filename The name of the file containing names to be read.
 * @return A vector of all names in the file.
 *
 * @throws std::runtime_error If the file cannot be opened.
 */
std::vector<std::string> readFile(const char *filename) throw(
        std::runtime_error) {
    std::ifstream in(filename);
    if(!in) {
        throw std::runtime_error("Failed to open file.");
    }
    std::vector<std::string> result;
    std::string tmp;
    do {
        if(in >> std::quoted(tmp)) {
            result.emplace_back(tmp);
        }
    } while(in.ignore());
    return result;
}
