#include "commands.hpp"

#include <sstream>

std::vector<std::unique_ptr<Command>> MemoryCommand::commands = std::vector<std::unique_ptr<Command>>();

std::string PrintError(const std::string& message) {
  return "OOPS: " + message + '\n';
}

std::vector<std::unique_ptr<Command>> memoryCommands;
std::vector<std::unique_ptr<Command>> execCommands;
void InitializeParseVectors() {
  memoryCommands.emplace_back(new GoWest());
  memoryCommands.emplace_back(new GoNorth());
  memoryCommands.emplace_back(new GoSouth());
  memoryCommands.emplace_back(new GoEast());

  execCommands.emplace_back(new Go());
  execCommands.emplace_back(new Re());
}

bool ParseFromLine(const std::string& line, std::ostream& out) {
  if (memoryCommands.empty() || execCommands.empty()) {
    InitializeParseVectors();
  }
  
  bool found = false;
  bool success = true;
  for (int i = 0; i < memoryCommands.size(); i += 1) {
    std::unique_ptr<Command> ptr(std::move(memoryCommands[i].get()->ParseFromLine(line, success, out)));
    if (ptr.get() == nullptr) {
      continue;
    }
    if (!success) {
      return success;
    }
    found = true;
    MemoryCommand::commands.emplace_back(std::move(ptr));
    break;
  }

  if (found) return found;

  for (int i = 0; i < execCommands.size(); i += 1) {
    std::unique_ptr<Command> ptr(std::move(execCommands[i].get()->ParseFromLine(line, success, out)));
    if (ptr.get() == nullptr) {
      continue;
    }
    if (!success) {
      return success;
    }
    found = true;
    std::pair<double, double> result = ptr.get()->Execute(success, out);
    return success;
  }

  if (!found) {
    out << PrintError("Invalid command: " + line);
  }

  return success && found;
}

std::unique_ptr<Command> Go::ParseFromLine(const std::string& line, bool& success, std::ostream& out) {
  if (line.find(name) == -1) {
    return std::unique_ptr<Command>(nullptr);
  }
  std::vector<double> result(std::move(ParseArguments<double>(2, line, success, out)));
  if (!success) return std::unique_ptr<Command>(new Go());
  return std::unique_ptr<Command>(new Go(result[0], result[1]));
}

std::pair<double, double> Go::Execute(bool& success, std::ostream& out) {
  double x = x_;
  double y = y_;
  std::pair<double, double> temp;
  for (int i = 0; i < MemoryCommand::commands.size(); i++) {
    temp = MemoryCommand::commands[i].get()->Execute(success, out);
    x += temp.first;
    y += temp.second;
  }
  out << x << ' ' << y << '\n';
  return { 0.0, 0.0 };
}

std::unique_ptr<Command> Re::ParseFromLine(const std::string& line, bool& success, std::ostream& out) {
  if (line.find(name) == -1) {
    return std::unique_ptr<Command>(nullptr);
  }
  std::vector<int> result(std::move(ParseArguments<int>(1, line, success, out)));
  if(!success) return std::unique_ptr<Command>(new Re());
  return std::unique_ptr<Command>(new Re(result[0]));
}

std::pair<double, double> Re::Execute(bool& success, std::ostream& out) {
  if (count_ > MemoryCommand::commands.size()) {
    out << PrintError("Can't revert " + std::to_string(count_) + " commands; only " + 
      std::to_string(MemoryCommand::commands.size()) + " are present");
    success = false;
    return { 0.0, 0.0 };
  }
  MemoryCommand::commands.resize(MemoryCommand::commands.size() - count_);
  return { 0.0, 0.0 };
}

std::unique_ptr<Command> GoWest::ParseFromLine(const std::string& line, bool& success, std::ostream& out) {
  if (line.find(name) == -1) {
    return std::unique_ptr<Command>(nullptr);
  }
  std::vector<double> result(std::move(ParseArguments<double>(1, line, success, out)));
  if (!success) return std::unique_ptr<Command>(new GoWest());
  return std::unique_ptr<Command>(new GoWest(result[0]));
}

std::pair<double, double> GoWest::Execute(bool& success, std::ostream& out) {
  return { x_, y_ };
}

std::unique_ptr<Command> GoNorth::ParseFromLine(const std::string& line, bool& success, std::ostream& out) {
  if (line.find(name) == -1) {
    return std::unique_ptr<Command>(nullptr);
  }
  std::vector<double> result(std::move(ParseArguments<double>(1, line, success, out)));
  if (!success) return std::unique_ptr<Command>(new GoNorth());
  return std::unique_ptr<Command>(new GoNorth(result[0]));
}

std::pair<double, double> GoNorth::Execute(bool& success, std::ostream& out) {
  return { x_, y_ };
}

std::unique_ptr<Command> GoSouth::ParseFromLine(const std::string& line, bool& success, std::ostream& out) {
  if (line.find(name) == -1) {
    return std::unique_ptr<Command>(nullptr);
  }
  std::vector<double> result(std::move(ParseArguments<double>(1, line, success, out)));
  if (!success) return std::unique_ptr<Command>(new GoSouth());
  return std::unique_ptr<Command>(new GoSouth(result[0]));
}

std::pair<double, double> GoSouth::Execute(bool& success, std::ostream& out) {
  return { x_, y_ };
}

std::unique_ptr<Command> GoEast::ParseFromLine(const std::string& line, bool& success, std::ostream& out) {
  if (line.find(name) == -1) {
    return std::unique_ptr<Command>(nullptr);
  }
  std::vector<double> result(std::move(ParseArguments<double>(1, line, success, out)));
  if (!success) return std::unique_ptr<Command>(new GoEast());
  return std::unique_ptr<Command>(new GoEast(result[0]));
}

std::pair<double, double> GoEast::Execute(bool& success, std::ostream& out) {
  return { x_, y_ };
}