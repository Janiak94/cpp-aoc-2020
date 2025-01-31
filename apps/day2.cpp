#include <cstdio>
#include <iostream>

#include "aoc/utils.hpp"

bool is_password_valid_part_1(
  std::string const& password, char const ch, int const min, int const max)
{
  int count{};
  for (char const _ch : password)
  {
    if (_ch == ch)
    {
      count++;
    }
    if (count > max)
    {
      return false;
    }
  }
  return count >= min;
}

bool is_password_valid_part_2(
  std::string const& password, char const ch, int const pos1, int const pos2)
{
  return (password[pos1 - 1] == ch) + (password[pos2 - 1] == ch) == 1;
}

struct Policy
{
  std::string password;
  char ch;
  int min, max;

  Policy from_line(std::string const& line)
  {
    char buf[100];
    std::sscanf(line.c_str(), "%d-%d %c: %s", &min, &max, &ch, buf);
    password = std::move(buf);
    return *this;
  }
};

int part_1(std::vector<std::string> const& lines)
{
  int count{};
  for (auto const& line : lines)
  {
    Policy policy;
    policy.from_line(line);
    if (is_password_valid_part_1(policy.password, policy.ch, policy.min, policy.max))
    {
      count++;
    }
  }
  return count;
}

int part_2(std::vector<std::string> const& lines)
{
  int count{};
  for (auto const& line : lines)
  {
    Policy policy;
    policy.from_line(line);
    if (is_password_valid_part_2(policy.password, policy.ch, policy.min, policy.max))
    {
      count++;
    }
  }
  return count;
}

int main()
{
  std::vector<std::string> const lines = utils::read_input_lines(__FILE__);

  int num_valid;

  num_valid = part_1(lines);
  std::cout << "Part 1: " << num_valid << std::endl;

  num_valid = part_2(lines);
  std::cout << "Part 2: " << num_valid << std::endl;
}
