#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

namespace utils {
namespace {
typedef std::filesystem::path path_t;

std::filesystem::path parse_source_path(
    std::filesystem::path const& source_file) {
  assert(std::filesystem::exists(source_file));
  if (!std::filesystem::exists(source_file)) {
    throw std::runtime_error("Source file does not exist");
  }
  auto source_dir = source_file.parent_path().parent_path();
  auto input_file =
      source_dir / "inputs" / (source_file.stem().string() + ".txt");
  assert(std::filesystem::exists(input_file));
  if (!std::filesystem::exists(input_file)) {
    throw std::runtime_error("Input file does not exist");
  }
  return input_file;
}
}  // namespace

inline std::string read_input(path_t const& source_path) {
  auto input_file = parse_source_path(source_path);
  std::ifstream input_stream(input_file);
  std::string buf, input_str;
  while (std::getline(input_stream, buf)) {
    if (!input_str.empty()) {
      input_str += '\n';
    }
    if (!buf.empty()) {
      input_str += buf;
    }
  }
  return input_str;
}

inline std::vector<std::string> read_input_lines(path_t const& source_path) {
  auto input_file = parse_source_path(source_path);
  std::ifstream input_stream(input_file);
  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input_stream, line)) {
    if (!line.empty()) {
      lines.push_back(std::move(line));
    }
  }
  return lines;
}

template <typename T>
std::vector<T> read_input_to_vector(std::filesystem::path const& source_path) {
  auto input_file = parse_source_path(source_path);
  std::ifstream input_stream(input_file);
  std::vector<T> input_items;
  T item;
  while (input_stream >> item) {
    input_items.push_back(item);
  }
  return input_items;
}

class Lines {
 public:
  class iterator {
   public:
    using iterator_category = std::input_iterator_tag;
    using value_type = std::string;
    using reference = std::string&;
    using pointer = std::string*;
    using difference_type = std::ptrdiff_t;

    iterator(std::string::const_iterator b, std::string::const_iterator e)
        : _begin(b), _end(e) {}
    iterator& operator++() {
      while (*_begin != '\n' && _begin != _end) {
        ++_begin;
      }
      if (*_begin == '\n') {
        ++_begin;
      }
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++*this;
      return tmp;
    }
    value_type operator*() {
      iterator end{*this};
      end++;
      return std::string(_begin, end._begin - 1);
    }
    bool operator==(iterator const& other) const {
      return _begin == other._begin && _end == other._end;
    }
    bool operator!=(iterator const& other) const { return !(*this == other); }

   private:
    std::string::const_iterator _begin;
    std::string::const_iterator _end;
  };

  Lines(std::string const& data) : data(data) {}

  iterator begin() const { return iterator(data.begin(), data.end()); }
  iterator end() const { return iterator(data.end(), data.end()); }

 private:
  std::string data;
};

class InputReader {
 public:
  InputReader(std::string const& source_filename) {
    auto const input_path = parse_source_path(source_filename);
    m_stream = std::ifstream(input_path);
  }
  ~InputReader() { m_stream.close(); }

  std::vector<std::string> getlines() {
    std::vector<std::string> lines{};
    std::string buf{};
    while (std::getline(m_stream, buf, '\n')) {
      lines.push_back(std::move(buf));
    }
    return lines;
  }

 private:
  std::ifstream m_stream;
};
}  // namespace utils
