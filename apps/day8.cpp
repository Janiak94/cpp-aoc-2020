#include <memory>
#include <optional>
#include "aoc/utils.hpp"

class Instruction {
 public:
  virtual void execute() = 0;

  bool is_executed() const { return m_is_executed; }

 protected:
  bool m_is_executed = false;
  int m_val;
};

class AccInstruction : public Instruction {
 public:
  AccInstruction(int const val, int& acc_ref) : m_acc_ref(acc_ref) {
    m_val = val;
  }

  virtual void execute() override {
    m_is_executed = true;
    m_acc_ref += m_val;
  }

 private:
  int& m_acc_ref;
};

class JmpInstruction : public Instruction {
 public:
  JmpInstruction(int const val, int& idx_ref) : m_idx_ref(idx_ref) {
    m_val = val;
  }

  virtual void execute() override {
    m_is_executed = true;
    m_idx_ref += m_val - 1;
  }

 private:
  int& m_idx_ref;
};

class NopInstruction : public Instruction {
 public:
  NopInstruction(int const val) { m_val = val; }
  virtual void execute() { m_is_executed = true; }
};

class InstructionSet {
 public:
  InstructionSet(std::vector<std::string> instructions) {
    for (auto const& instruction_str : instructions) {
      auto splitat = instruction_str.find(' ');
      std::string id, op;
      id = instruction_str.substr(0, splitat);
      op = instruction_str.substr(splitat + 1);

      if (id == "acc") {
        m_instructions.push_back(
            std::make_unique<AccInstruction>(std::stoi(op), m_acc));
      } else if (id == "jmp") {
        m_instructions.push_back(
            std::make_unique<JmpInstruction>(std::stoi(op), m_current_idx));
      } else {
        m_instructions.push_back(
            std::make_unique<NopInstruction>(std::stoi(op)));
      }
    }
  }

  int execute() {
    while (true) {
      auto& inst = m_instructions[m_current_idx];
      if (inst->is_executed()) {
        return m_current_idx;
      }
      inst->execute();
      m_current_idx++;
      if (m_current_idx == static_cast<int>(m_instructions.size())) {
        return m_current_idx;
      }
    }
  }

  int acc() const { return m_acc; }

 protected:
  std::vector<std::unique_ptr<Instruction>> m_instructions;

 private:
  int m_acc = 0;
  int m_current_idx = 0;
};

void part_1(std::vector<std::string> const& input) {
  InstructionSet is = InstructionSet(input);
  is.execute();
  std::cout << "Part 1: " << is.acc() << std::endl;
}

std::optional<std::string> flip_instruction(
    std::string const& instruction_str) {
  auto const splitat = instruction_str.find(' ');
  auto const id = instruction_str.substr(0, splitat);
  if (id == "acc") {
    return {};
  }
  auto const op = std::stoi(instruction_str.substr(splitat + 1));
  if (id == "jmp") {
    return "nop " + std::to_string(op);
  } else {
    return "jmp " + std::to_string(op);
  }
}

void part_2(std::vector<std::string> const& input) {
  int acc;
  for (int i = 0; i < static_cast<int>(input.size()); i++) {
    auto const flipped = flip_instruction(input[i]);
    if (!flipped.has_value()) {
      continue;
    }
    std::vector<std::string> input_copy = input;
    input_copy[i] = flipped.value();
    InstructionSet is = InstructionSet(input_copy);
    if (is.execute() == static_cast<int>(input.size())) {
      std::cout << "Part 2: " << is.acc() << std::endl;
      break;
    }
  }
}

int main() {
  auto reader = utils::InputReader(__FILE__);
  auto const input = reader.getlines();

  part_1(input);

  part_2(input);
}
