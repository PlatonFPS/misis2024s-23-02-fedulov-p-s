#include "commands.hpp"

std::string PrintError(const std::string& message) {
  return "OOPS: " + message + '\n';
}

std::unique_ptr<Command> GoWest::ParseFromLine(const std::string& line) {
  if (line.find("GW") == -1) {
    //error
  }
}
