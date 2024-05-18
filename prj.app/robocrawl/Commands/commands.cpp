#include "commands.hpp"

void PrintError(std::string_view message) {
  std::cout << "OOPS: " << message << '\n';
}

MovementCommand::MovementCommand(double lenght)
  : lenght_(lenght) {
}

MovementCommand::MovementCommand(std::istream& in) {
  double lenght = 0;
  if (!(in >> lenght)) {
    PrintError("Invalid lenght argument " + std::to_string(lenght));
    lenght = 0;
  }
  lenght_ = lenght;
}