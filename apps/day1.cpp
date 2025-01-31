#include <iostream>
#include <tuple>
#include <vector>

#include "aoc/utils.hpp"

typedef uint64_t input_t;

std::tuple<input_t, input_t> part_1(std::vector<input_t> const& inputs)
{
  for (auto num1_ptr = inputs.cbegin(); num1_ptr < inputs.cend() - 1; num1_ptr++)
  {
    for (auto num2_ptr = num1_ptr + 1; num2_ptr < inputs.cend(); num2_ptr++)
    {
      if (*num1_ptr + *num2_ptr == 2020)
      {
        return {*num1_ptr, *num2_ptr};
      }
    }
  }
  return {};
}

std::tuple<input_t, input_t, input_t> part_2(std::vector<input_t> const& inputs)
{
  for (auto num1_ptr = inputs.cbegin(); num1_ptr < inputs.cend() - 2; num1_ptr++)
  {
    for (auto num2_ptr = num1_ptr + 1; num2_ptr < inputs.cend() - 1; num2_ptr++)
    {
      for (auto num3_ptr = num2_ptr + 1; num3_ptr < inputs.cend(); num3_ptr++)
      {
        if (*num1_ptr + *num2_ptr + *num3_ptr == 2020)
        {
          return {*num1_ptr, *num2_ptr, *num3_ptr};
        }
      }
    }
  }
  return {};
}

int main()
{
  std::vector const inputs = utils::read_input_to_vector<input_t>(__FILE__);

  input_t num1, num2, num3;
  std::tie(num1, num2) = part_1(inputs);
  std::cout << "Part 1: " << num1 << " * " << num2 << " = " << num1 * num2 << std::endl;

  std::tie(num1, num2, num3) = part_2(inputs);
  std::cout << "Part 2: " << num1 << " * " << num2 << " * " << num3 << " = "
            << num1 * num2 * num3 << std::endl;
}
