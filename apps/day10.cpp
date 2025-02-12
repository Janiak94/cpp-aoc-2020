#include <iterator>
#include <list>
#include <map>
#include <numeric>
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

number_t get_my_rating(std::vector<number_t> const& input) {
  return *std::max_element(input.begin(), input.end()) + 3;
}

void part_1(std::vector<number_t> const& input) {
  auto const my_rating = get_my_rating(input);

  std::vector<number_t> solution = input;
  solution.push_back(my_rating);
  std::sort(solution.begin(), solution.end());

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

number_t get_path_count(std::vector<number_t>::const_iterator const start_node,
                        std::vector<number_t>::const_iterator const end,
                        std::map<number_t, number_t>& cache) {
  if (start_node + 1 == end) {
    return 1;
  }
  if (auto const search = cache.find(*start_node); search != cache.end()) {
    return search->second;
  }
  std::vector<number_t> next_nodes{};
  std::copy_if(start_node + 1, end, std::back_inserter(next_nodes),
               [&start_node](auto num) {
                 return (num >= *start_node + 1) && (num <= *start_node + 3);
               });
  assert(next_nodes.size() > 0);
  number_t count = 0;
  for (auto it = next_nodes.cbegin(); it != next_nodes.cend(); it++) {
    auto start = std::find(start_node, end, *it);
    count += get_path_count(start, end, cache);
  }
  cache[*start_node] = count;
  return count;
}

void part_2(std::vector<number_t> const& input) {
  auto const my_rating = get_my_rating(input);

  std::vector<number_t> solution = input;
  solution.push_back(my_rating);
  solution.insert(solution.begin(), 0);
  std::sort(solution.begin(), solution.end());

  std::map<number_t, number_t> cache;
  auto count = get_path_count(solution.cbegin(), solution.cend(), cache);

  std::cout << "Part 2: " << count << std::endl;
}

int main() {
  auto reader = utils::InputReader(__FILE__);
  auto input_str = reader.getlines();
  std::vector<number_t> input;
  std::transform(input_str.begin(), input_str.end(), std::back_inserter(input),
                 str_to_num);

  // Quicker to find a solution.
  part_1(input);

  part_2(input);
}
