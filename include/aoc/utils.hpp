#include <cassert>
#include <filesystem>
#include <fstream>
#include <vector>

namespace utils
{
namespace
{
typedef std::filesystem::path path_t;

std::filesystem::path parse_source_path(std::filesystem::path const& source_file)
{
  assert(std::filesystem::exists(source_file));
  if (!std::filesystem::exists(source_file))
  {
    throw std::runtime_error("Source file does not exist");
  }
  auto source_dir = source_file.parent_path().parent_path();
  auto input_file = source_dir / "inputs" / (source_file.stem().string() + ".txt");
  assert(std::filesystem::exists(input_file));
  if (!std::filesystem::exists(input_file))
  {
    throw std::runtime_error("Input file does not exist");
  }
  return input_file;
}
}  // namespace

inline std::string read_input(path_t const& source_path)
{
  auto input_file = parse_source_path(source_path);
  std::ifstream input_stream(input_file);
  std::string buf, input_str;
  while (input_stream >> buf)
  {
    if (!input_str.empty())
    {
      input_str += '\n';
    }
    if (!buf.empty())
    {
      input_str += buf;
    }
  }
  return input_str;
}

inline std::vector<std::string> read_input_lines(path_t const& source_path)
{
  auto input_file = parse_source_path(source_path);
  std::ifstream input_stream(input_file);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input_stream, line))
  {
    if (!line.empty())
    {
      lines.push_back(std::move(line));
    }
  }
  return lines;
}

template <typename T>
std::vector<T> read_input_to_vector(std::filesystem::path const& source_path)
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
