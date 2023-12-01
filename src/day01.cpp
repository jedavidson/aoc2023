#include <algorithm>
#include <functional>
#include <numeric>
#include <regex>
#include <string>
#include <string_view>

#include <utils.hpp>

int str_to_digit(std::string_view str) {
    constexpr std::array<std::string_view, 20> digits = {
        "0",    "1",    "2",   "3",     "4",     "5",   "6",
        "7",    "8",    "9",   "zero",  "one",   "two", "three",
        "four", "five", "six", "seven", "eight", "nine"};
    auto it = std::find(digits.begin(), digits.end(), str);
    return std::distance(digits.begin(), it) % 10;
}

int simple_calibration_value(std::string_view line) {
    auto is_digit = [](char ch) { return std::isdigit(ch); };
    auto first_it = std::find_if(line.begin(), line.end(), is_digit);
    auto last_it = std::find_if(line.rbegin(), line.rend(), is_digit);
    return 10 * (*first_it - '0') + (*last_it - '0');
}

int complex_calibration_value(std::string_view line) {
    constexpr std::string_view pattern =
        "1|2|3|4|5|6|7|8|9|one|two|three|four|five|six|seven|eight|nine";
    const std::regex first_re(pattern.begin(), pattern.end());
    const std::regex last_re(pattern.rbegin(), pattern.rend());

    std::match_results<decltype(line.begin())> first_match;
    std::regex_search(line.begin(), line.end(), first_match, first_re);
    std::string first_match_str = first_match.str();

    std::match_results<decltype(line.rbegin())> last_match;
    std::regex_search(line.rbegin(), line.rend(), last_match, last_re);
    std::string last_match_str = last_match.str();
    std::reverse(last_match_str.begin(), last_match_str.end());

    return 10 * str_to_digit(first_match_str) + str_to_digit(last_match_str);
}

int calibration_value_sum(const std::vector<std::string> &document,
                          std::function<int(std::string_view)> f) {
    auto acc = [&](int sum, std::string_view line) { return sum + f(line); };
    return std::accumulate(document.begin(), document.end(), 0, acc);
}

int main() {
    const auto document = utils::read_lines("inputs/day01/full.txt");
    std::cout << "Part 1: Simple calibration sum is "
              << calibration_value_sum(document, simple_calibration_value)
              << "\n";
    std::cout << "Part 2: Complex calibration sum is "
              << calibration_value_sum(document, complex_calibration_value)
              << "\n";
}
