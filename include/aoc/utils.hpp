#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace utils
{
namespace
{
std::filesystem::path parse_source_path(std::filesystem::path const& source_file)
{
  assert(std::filesystem::exists(source_file));
  auto source_dir = source_file.parent_path().parent_path();
  auto input_file = source_dir / "inputs" / (source_file.stem().string() + ".txt");
  assert(std::filesystem::exists(input_file));
  return input_file;
}
}  // namespace

template <typename T>
std::vector<T> read_input(std::filesystem::path const& source_path)
{
  auto input_file = parse_source_path(source_path);
  std::ifstream input_stream(input_file);
  std::vector<T> input_items;
  T item;
  while (input_stream >> item)
  {
    input_items.push_back(item);
  }
  return input_items;
}
}  // namespace utils
