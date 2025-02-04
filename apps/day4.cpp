#include <cstdarg>
#include <cstddef>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

#include "aoc/utils.hpp"

using entry_t = std::pair<std::string, std::string>;
using record_t = std::vector<entry_t>;

template <typename T>
bool is_in_range(T const& value, T const& min, T const& max) {
  return (value >= min && value <= max);
}

bool validate_entry(std::string const& key, std::string const& value) {
  if (key == "byr") {
    int const year = std::stoi(value.c_str());
    if (value.size() != 4 || !is_in_range(year, 1920, 2002)) {
      return false;
    }
  } else if (key == "iyr") {
    int const year = std::stoi(value.c_str());
    if (value.size() != 4 || !is_in_range(year, 2010, 2020)) {
      return false;
    }
  } else if (key == "eyr") {
    int const year = std::stoi(value.c_str());
    if (value.size() != 4 || !is_in_range(year, 2020, 2030)) {
      return false;
    }
  } else if (key == "hgt") {
    try {
      std::string const suffix(value.end() - 2, value.end());
      int const height = std::stoi(std::string(value.begin(), value.end() - 2));
      if (suffix == "cm" && !is_in_range(height, 150, 193)) {
        return false;
      } else if (suffix == "in" && !is_in_range(height, 59, 76)) {
        return false;
      }
    } catch (std::invalid_argument) {
      return false;
    } catch (std::length_error) {
      return false;
    }
  } else if (key == "hcl") {
    char buf[15];
    auto res = std::sscanf(value.c_str(), "#%[0-9a-z]", buf);
    if (value[0] != '#' || value.size() != 7 || !res) {
      return false;
    }
  } else if (key == "ecl") {
    std::set<std::string> valid_colors{"amb", "blu", "brn", "gry",
                                       "grn", "hzl", "oth"};
    if (valid_colors.find(value) == valid_colors.end()) {
      return false;
    }
  } else if (key == "pid") {
    char buf[15];
    if (!std::sscanf(value.c_str(), "%[0-9]", buf) || value.size() != 9) {
      return false;
    }
  }
  return true;
}

bool is_valid(record_t const& record,
              std::vector<std::string> const& required_fields,
              std::function<bool(std::string, std::string)> entry_validator) {
  std::set<std::string> required_fields_set(required_fields.begin(),
                                            required_fields.end());
  std::set<std::string> fields;
  for (auto const& entry : record) {
    if (entry_validator != NULL &&
        !entry_validator(entry.first, entry.second)) {
      std::cout << "Failed validation for " << entry.first << ": "
                << entry.second << std::endl;
      return false;
    }
    fields.insert(entry.first);
  }
  for (auto const& f : required_fields) {
    if (fields.find(f) == fields.end()) {
      return false;
    }
  }
  return true;
}

std::vector<entry_t> filter_lines(std::string const& line) {
  std::vector<entry_t> entries;
  std::string buf;
  std::stringstream stream(line);
  while (std::getline(stream, buf, ' ')) {
    auto const splitat = buf.find(':');
    entries.emplace_back(buf.substr(0, splitat), buf.substr(splitat + 1));
  }
  return entries;
}

int count_valid(
    std::string const& input,
    std::function<bool(std::string, std::string)> entry_validator = NULL) {
  std::vector<std::string> const required_fields = {
      {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}};
  std::vector<record_t> records;
  record_t record;
  int count = 0;
  utils::Lines const lines(input);
  for (auto const& line : lines) {
    if (!line.empty()) {
      std::vector<entry_t> parsed_line = filter_lines(line);
      record.insert(record.end(), parsed_line.begin(), parsed_line.end());
    } else {
      if (is_valid(record, required_fields, entry_validator)) {
        count++;
      }
      record = {};
    }
  }
  if (is_valid(record, required_fields, entry_validator)) {
    count++;
  }
  return count;
}

int part_1(std::string const& input) {
  return count_valid(input);
}

int part_2(std::string const& input) {
  return count_valid(input, validate_entry);
}

int main() {
  std::string input = utils::read_input(__FILE__);

  int num_valid = part_1(input);
  std::cout << "Part 1: " << num_valid << std::endl;

  num_valid = part_2(input);
  std::cout << "Part 2: " << num_valid << std::endl;
}
