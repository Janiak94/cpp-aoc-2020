#include <algorithm>
#include "aoc/utils.hpp"

using number_t = long int;

int str_to_num(std::string const& s) {
  return std::stol(s);
}

template <typename Iter>
bool follows_rule(Iter const first, Iter const last) {
  int const target = *last;
  for (auto it1 = first; it1 != last - 1; it1++) {
    for (auto it2 = it1 + 1; it2 != last; it2++) {
      if (*it1 + *it2 == target) {
        return true;
      }
    }
  }
  return false;
}

template <typename Iter>
bool follows_rule_range(Iter const first, Iter const last,
                        number_t const target) {
  number_t sum = 0;
  for (auto it = first; it != last; it++) {
    sum += *it;
  }
  return sum == target;
}

number_t part_1(std::vector<number_t> const& input) {
  constexpr number_t offset = 25;
  for (auto begin = input.begin() + offset; begin < input.end(); begin++) {
    if (!follows_rule(begin - offset, begin)) {
      return *begin;
    }
  }
  throw std::runtime_error("No answer found");
}

number_t part_2(std::vector<number_t> const& input,
                number_t const& invalid_num) {
  std::vector<number_t> range;
  for (number_t offset = 1; offset < input.size(); offset++) {
    for (auto begin = input.begin(); begin + offset != input.end(); begin++) {
      if (follows_rule_range(begin, begin + offset, invalid_num)) {
        range = {begin, begin + offset};
        break;
      }
    }
  }
  auto const [min, max] = std::minmax_element(range.begin(), range.end());
  return *min + *max;
}

int main() {
  auto reader = utils::InputReader(__FILE__);
  auto const input_str = reader.getlines();
  std::vector<number_t> input;
  std::transform(input_str.begin(), input_str.end(), std::back_inserter(input),
                 str_to_num);

  number_t const invalid_num = part_1(input);
  std::cout << "Part 1: " << invalid_num << std::endl;

  number_t const weakness = part_2(input, invalid_num);
  std::cout << "Part 2: " << weakness << std::endl;
}
