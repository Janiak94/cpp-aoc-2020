#include <set>
#include <string>
#include <vector>
#include "aoc/utils.hpp"

using input_t = std::vector<std::string>;

class Group {

 public:
  using answer_t = std::string;

  Group() : m_answers() {}

  size_t size() const { return m_answers.size(); }
  bool empty() const { return m_answers.size() == 0; }

  std::vector<answer_t> answers() const { return m_answers; }
  answer_t answers_str() const {
    answer_t buf{};
    for (auto const& answer : m_answers) {
      buf += answer;
    }
    return buf;
  }

  Group& operator+=(answer_t const& answers) {
    m_answers.push_back(answers);
    return *this;
  }

 private:
  std::vector<answer_t> m_answers;
};

void flush_buffer(Group& group, std::vector<Group>& collection) {
  if (!group.empty()) {
    collection.push_back(std::move(group));
  }
}

std::vector<Group> parse_groups(input_t const& input) {
  std::vector<Group> groups;
  Group group{};
  for (auto const& line : input) {
    if (!line.empty()) {
      group += line;
    } else {
      flush_buffer(group, groups);
    }
  }
  flush_buffer(group, groups);
  return groups;
}

int part_1(std::vector<Group> const& input) {
  int sum{0};
  for (auto const& group : input) {
    std::string answers = group.answers_str();
    std::set<char> group_questions(answers.begin(), answers.end());
    sum += group_questions.size();
  }
  return sum;
}

int part_2(std::vector<Group> const& input) {
  int sum{0};
  for (auto const& group : input) {
    // Only need to check one group.
    std::string answers = group.answers()[0];
    for (auto const ch : answers) {
      int count{0};
      for (auto const& answer : group.answers()) {
        if (answer.find(ch) != std::string::npos) {
          count++;
        }
      }
      if (count == static_cast<int>(group.size())) {
        sum++;
      }
    }
  }
  return sum;
}

int main() {
  utils::InputReader reader(__FILE__);
  auto const input = reader.getlines();
  auto const groups = parse_groups(input);

  int sum = part_1(groups);
  std::cout << "Part 1: " << sum << std::endl;

  sum = part_2(groups);
  std::cout << "Part 2: " << sum << std::endl;
}
