#include <iostream>
#include <vector>

#include "aoc/utils.hpp"

typedef uint64_t input_t;

void part_1(std::vector<input_t> const& inputs)
{
  for (auto num1_ptr = inputs.cbegin(); num1_ptr < inputs.cend() - 1; num1_ptr++)
  {
    for (auto num2_ptr = num1_ptr + 1; num2_ptr < inputs.cend(); num2_ptr++)
    {
      {
        std::cout
          << "Found numbers " << *num1_ptr << " and " << *num2_ptr
          << " that sum to 2020. Result is " << *num1_ptr * *num2_ptr << std::endl;
        return;
      }
    }
  }
}

void part_2(std::vector<input_t> const& inputs)
{
  for (auto num1_ptr = inputs.cbegin(); num1_ptr < inputs.cend() - 2; num1_ptr++)
  {
    for (auto num2_ptr = num1_ptr + 1; num2_ptr < inputs.cend() - 1; num2_ptr++)
    {
      for (auto num3_ptr = num2_ptr + 1; num3_ptr < inputs.cend(); num3_ptr++)
      {
        if (*num1_ptr + *num2_ptr + *num3_ptr == 2020)
        {
          std::cout << "Found numbers " << *num1_ptr << " + " << *num2_ptr << " + "
                    << *num3_ptr << " that sum to 2020. Result is "
                    << *num1_ptr * *num2_ptr * *num3_ptr << std::endl;
        }
      }
    }
  }
}

int main()
{
  std::vector const inputs = utils::read_input<input_t>(__FILE__);

  part_1(inputs);

  part_2(inputs);
}
