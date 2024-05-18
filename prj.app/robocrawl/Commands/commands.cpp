#include "commands.hpp"

std::string_view PrintError(const std::string& message) {
  return std::string_view("OOPS: " + message + '\n');
}

MovementCommand::MovementCommand(double lenght)
  : lenght_(lenght) {
}

MovementCommand::MovementCommand(std::istream& in, std::ostream& out) {
  double lenght = 0;
  if (!(in >> lenght)) {
    out << PrintError("Invalid lenght argument " + std::to_string(lenght));
    lenght = 0;
  }
  lenght_ = lenght;
}