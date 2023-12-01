#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace utils {

inline std::vector<std::string> read_lines(const std::string &path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Couldn't open input file " << path << "\n";
        std::exit(EXIT_FAILURE);
    }

    std::vector<std::string> lines;
    std::copy(std::istream_iterator<std::string>(file),
              std::istream_iterator<std::string>(), std::back_inserter(lines));
    return lines;
}

} // namespace utils