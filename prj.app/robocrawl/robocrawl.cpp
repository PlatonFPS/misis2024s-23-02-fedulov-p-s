#include <commands/commands.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

int CheckArgs(int argc, char** argv, std::ifstream& in, std::ofstream& out) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " <input file>" << '\n';
    std::cerr << "Invalid amount of arguments: " << argc << '\n';
    return 1;
  }

  if (std::string(argv[1]) == "-i") {
    in.open(std::string(argv[2]));
  }
  else if (std::string(argv[1]) == "-o") {
    out.open(std::string(argv[2]));
  }
  else {
    std::cerr << "Invalid argument: " << argv[1] << '\n';
    return 1;
  }

  if (std::string(argv[3]) == "-i") {
    in.open(std::string(argv[4]));
  }
  else if (std::string(argv[3]) == "-o") {
    out.open(std::string(argv[4]));
  }
  else {
    std::cerr << "Invalid argument: " << argv[3] << '\n';
    return 1;
  }

  if (!in.is_open()) {
    std::cerr << "Could not open input file\n";
    return 1;
  }

  if (!out.is_open()) {
    std::cerr << "Could not open output file\n";
    return 1;
  }
}

int main(int argc, char** argv) {
  std::ifstream in;
  std::ofstream out;
  
  int check = CheckArgs(argc, argv, in, out);
  if (check != 0) return check;

  std::vector<std::unique_ptr<Command>> commandTypes;
  commandTypes.emplace_back(std::make_unique<GoWest>());
  commandTypes.emplace_back(std::make_unique<GoNorth>());
  commandTypes.emplace_back(std::make_unique<GoSouth>());
  commandTypes.emplace_back(std::make_unique<GoEast>());

  std::vector<std::unique_ptr<Command>> commands;
  std::string line;
  while (std::getline(in, line)) {

  }

  in.close();
  out.close();
  return 0;
}