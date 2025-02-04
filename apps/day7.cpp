#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "aoc/utils.hpp"

std::string parse_id(std::string const& descriptor) {
  std::stringstream ss(descriptor);
  std::string buf{}, out{};
  for (int i = 0; i < 2; ++i) {
    ss >> buf;
    if (!out.empty()) {
      out += " ";
    }
    out += std::move(buf);
  }
  return out;
}

std::vector<std::pair<std::string, int>> parse_can_contain(
    std::string const& descriptor) {
  std::vector<std::pair<std::string, int>> contents;
  std::stringstream ss(descriptor);
  std::string buf{};
  // Skip first four words.
  for (int i = 0; i < 4; ++i) {
    ss >> buf;
  }
  while (!ss.eof()) {
    ss >> buf;
    if (buf == "no") {
      return {};
    }
    std::string id_other;
    int count = std::stoi(buf.c_str());
    ss >> id_other;  // Read directly to id_other initially.
    ss >> buf;
    id_other += " " + std::move(buf);
    ss >> buf;
    contents.emplace_back(std::pair{id_other, count});
  }
  return contents;
}

class Bag {
 public:
  Bag() = delete;

  std::string const id() const { return m_id; }
  std::vector<std::pair<Bag*, int>> contents() const { return m_can_contain; }

  // TODO: Make immutable getter.
  static Bag& get_instance(std::string const& id) {
    assert(s_instances.find(id) != s_instances.end());
    return s_instances.at(id);
  }

  static std::vector<const Bag*> get_all_instances() {
    std::vector<const Bag*> instances;
    for (auto const& instance : s_instances) {
      instances.push_back(&instance.second);
    }
    return instances;
  }

  static void create_instances(std::vector<std::string> descriptors) {
    for (auto const& descriptor : descriptors) {
      auto const id = parse_id(descriptor);
      Bag b{id};
      s_instances.insert({id, Bag{id}});
    }
    for (auto const& descriptor : descriptors) {
      auto const id = parse_id(descriptor);
      auto contents = parse_can_contain(descriptor);
      Bag& bag = get_instance(id);
      for (auto const& [id_other, count] : contents) {
        bag.m_can_contain.push_back(
            std::make_pair(&get_instance(id_other), count));
      }
    }
  }

 private:
  static std::map<std::string, Bag> s_instances;
  std::string m_id;
  std::vector<std::pair<Bag*, int>> m_can_contain;

  Bag(std::string const& id) : m_id{id} {}
};

std::map<std::string, Bag> Bag::s_instances{};

void print_bags(std::vector<std::string> const& descriptors) {
  for (auto const& descriptor : descriptors) {
    auto const& bag = Bag::get_instance(parse_id(descriptor));
    std::cout << "bag: " << bag.id() << std::endl;
    for (auto const& [bag_other, count] : bag.contents()) {
      std::cout << "  can contain: " << bag_other->id() << " " << count
                << std::endl;
    }
    std::cout << std::endl;
  }
}

int get_count(Bag const& bag, std::string const& id) {
  int total_count = 0;
  for (auto const& [bag_other, count] : bag.contents()) {
    if (bag_other->id() == id) {
      total_count += count;
    }
    total_count += count * get_count(*bag_other, id);
  }
  return total_count;
}

int get_total_count(Bag const& bag) {
  int total_count = 1;
  for (auto const& [bag_other, count] : bag.contents()) {
    total_count += count * get_total_count(*bag_other);
  }
  return total_count;
}

void part_1(std::vector<std::string> const& input) {
  auto descriptors = input;
  descriptors.pop_back();
  Bag::create_instances(descriptors);

  auto const bags = Bag::get_all_instances();

  int total_count = 0;
  for (auto const* bag_ptr : bags) {
    int count = get_count(*bag_ptr, "shiny gold");
    std::cout << bag_ptr->id() << " contains " << count << std::endl;
    total_count += (count != 0 ? 1 : 0);
  }
  std::cout << total_count << std::endl;
}

void part_2() {
  auto const& bag = Bag::get_instance("shiny gold");
  int total_count = get_total_count(bag) - 1;
  std::cout << total_count << std::endl;
}

int main() {
  utils::InputReader reader(__FILE__);
  auto const input = reader.getlines();

  part_1(input);

  part_2();
}
