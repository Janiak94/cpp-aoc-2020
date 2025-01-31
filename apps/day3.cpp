#include <cstddef>
#include <iostream>

#include "aoc/utils.hpp"

template <typename C>
class Grid {
 public:
  Grid(std::string const& input) : grid(input), _width(0), _height(0) {
    for (auto i = input.cbegin(); *i != '\n'; i++) {
      _width++;
    }
    _height = grid.size() / (_width + 1) + 1;
  }

  C operator[](std::pair<int, int> const idx) const {
    return grid[idx.first * (width() + 1) + idx.second];
  }

  size_t width() const { return _width; }

  size_t height() const { return _height; }

 private:
  std::string grid;
  size_t _width, _height;
};

struct Direction {
  int right, down;
};

int check_slope(Grid<char> const& grid, Direction const dir) {
  auto idx = std::make_pair(size_t{0}, size_t{0});
  int count = 0;
  while (idx.first < grid.height()) {
    if (grid[idx] == '#') {
      count++;
    }
    idx = std::make_pair(idx.first + dir.down,
                         (idx.second + dir.right) % grid.width());
  }
  return count;
}

int part_1(std::string const& input) {
  Grid<char> const grid(input);
  Direction const dir{3, 1};

  return check_slope(grid, dir);
}

long int part_2(std::string const& input) {
  Grid<char> const grid(input);
  std::array<Direction, 5> directions{{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}}};

  long int prod = 1;
  for (auto const& dir : directions) {
    prod *= check_slope(grid, dir);
  }
  return prod;
}

int main() {
  std::string input = utils::read_input(__FILE__);
  int tree_count;

  tree_count = part_1(input);
  std::cout << "Part 1: " << tree_count << std::endl;

  long int const prod = part_2(input);
  std::cout << "Part 2: " << prod << std::endl;
}
