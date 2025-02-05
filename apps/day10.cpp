#include <iomanip>
#include <list>
#include <vector>
#include "aoc/utils.hpp"

using number_t = long int;

number_t str_to_num(std::string const& str) {
  return std::stol(str);
}

bool find_solution(std::list<number_t>& solution,
                   std::vector<number_t>& remaining, int depth = 0) {
  if (remaining.empty()) {
    return true;
  }

  int current_rating = solution.empty() ? 0 : solution.back();
  for (auto it = remaining.begin(); it != remaining.end();) {
    auto const diff = *it - current_rating;
    if (diff >= 1 && diff <= 3) /* is this right? */ {

      auto const val = *it;
      solution.push_back(val);
      it = remaining.erase(it);

      auto sol = find_solution(solution, remaining, depth + 1);
      if (sol) {
        return true;
      } else {
        it = remaining.insert(it, val);
        solution.pop_back();
      }
    }
    ++it;
  }
  return false;
}

void part_1(std::vector<number_t> const& input) {
  auto const my_rating = *std::max_element(input.begin(), input.end()) + 3;
  std::list<number_t> solution;
  std::vector<number_t> remaining{input.begin(), input.end()};

  auto has_solution = find_solution(solution, remaining);
  assert(has_solution);

  solution.push_back(my_rating);

  number_t prev = 0;
  std::pair<number_t, number_t> diffs{0, 0};
  for (auto it = solution.begin(); it != solution.end(); ++it) {
    if (*it - prev == 1) {
      diffs.first++;
    } else if (*it - prev == 3) {
      diffs.second++;
    }
    prev = *it;
  }
  std::cout << "Part 1: " << diffs.first * diffs.second << std::endl;
}

int main() {
  auto reader = utils::InputReader(__FILE__);
  auto input_str = reader.getlines();
  std::vector<number_t> input;
  std::transform(input_str.begin(), input_str.end(), std::back_inserter(input),
                 str_to_num);

  // Quicker to find a solution.
  std::sort(input.begin(), input.end());
  part_1(input);
}
