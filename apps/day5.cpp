#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include "aoc/utils.hpp"

using row_t = std::string;

enum class Instruction : char { B = 'B', F = 'F', L = 'L', R = 'R' };

struct Location {
  size_t row_low, row_high, column_low, column_high;
};

constexpr Location s_loc{0, 127, 0, 7};

/// Remove empty lines.
std::vector<row_t> filter_lines(std::vector<row_t> input) {
  auto const end =
      std::remove_if(input.begin(), input.end(),
                     [](auto const& item) { return item.empty(); });
  return std::vector<row_t>(input.begin(), end);
}

size_t convert_seat_id(size_t const row, size_t const column) {
  return row * 8 + column;
}

std::pair<size_t, size_t> find_location(std::string instructions,
                                        Location loc_cur) {
  for (auto const i_ch : instructions) {
    Instruction const i = Instruction(i_ch);

    size_t half_w, half_h;
    switch (i) {
      case Instruction::B:
        half_h = (loc_cur.row_high - loc_cur.row_low + 1) / 2;
        loc_cur.row_low += half_h;
        break;
      case Instruction::F:
        half_h = (loc_cur.row_high - loc_cur.row_low + 1) / 2;
        loc_cur.row_high -= half_h;
        break;
      case Instruction::R:
        half_w = (loc_cur.column_high - loc_cur.column_low + 1) / 2;
        loc_cur.column_low += half_w;
        break;
      case Instruction::L:
        half_w = (loc_cur.column_high - loc_cur.column_low + 1) / 2;
        loc_cur.column_high -= half_w;
        break;
    }
    // std::cout << "Rows: Low: " << loc_cur.row_low
    //           << ", High: " << loc_cur.row_high;
    // std::cout << ", Cols: Low: " << loc_cur.column_low
    //           << ", High: " << loc_cur.column_high << std::endl;
  }
  assert(loc_cur.row_low == loc_cur.row_high);
  assert(loc_cur.column_low == loc_cur.column_high);
  return {loc_cur.row_low, loc_cur.column_low};
}

size_t part_1(std::vector<row_t> const& input) {
  size_t max_seat_id{};
  for (auto const& line : input) {
    auto const loc_exact = find_location(line, s_loc);
    size_t seat_id = convert_seat_id(loc_exact.first, loc_exact.second);
    max_seat_id = std::max(max_seat_id, seat_id);
  }

  return max_seat_id;
}

void part_2(std::vector<row_t> const& input) {
  std::vector<size_t> seat_ids{};

  for (auto const& line : input) {
    auto const loc_exact = find_location(line, s_loc);
    size_t seat_id = convert_seat_id(loc_exact.first, loc_exact.second);
    seat_ids.push_back(seat_id);
  }

  std::sort(seat_ids.begin(), seat_ids.end());
  for (size_t i = 0; i < seat_ids.size() - 1; i++) {
    if (seat_ids[i] + 2 == seat_ids[i + 1]) {
      std::cout << "Part 2: " << seat_ids[i] + 1 << std::endl;
    }
  }
}

int main() {
  auto const input = filter_lines(utils::read_input_to_vector<row_t>(__FILE__));
  // std::vector<row_t> input{{"FBFBBFFRLR"}};

  size_t seat_id = part_1(input);
  std::cout << "Part 1: " << seat_id << std::endl;

  part_2(input);
}
