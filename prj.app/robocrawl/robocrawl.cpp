#include <commands/commands.hpp>

#include <iostream>
#include <fstream>
#include <stack>
#include <memory>

class CommandStack {
public:
  CommandStack() = default;

  ~CommandStack() = default;

  void Push(std::unique_ptr<MovementCommand> ptr);
  void Pop(int count);

  void PrintCurrentPosition(double x, double y, std::ostream& out);
private:
  std::stack<std::unique_ptr<MovementCommand>> commands;
  double x_ = 0;
  double y_ = 0;
};

void CommandStack::Push(std::unique_ptr<MovementCommand> ptr){
  x_ += ptr.get()->GetDelta().first;
  y_ += ptr.get()->GetDelta().second;
  commands.push(std::move(ptr));
}

void CommandStack::Pop(int count) {
  while (count > 0 && !commands.empty()) {
    x_ -= commands.top()->GetDelta().first;
    y_ -= commands.top()->GetDelta().second;
    commands.pop();
    ++count;
  }
}

void CommandStack::PrintCurrentPosition(double x, double y, std::ostream& out) {
  out << x + x_ << ' ' << y + y_ << '\n';
}

int main(int argc, char** argv) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " <input file>" << '\n';
    std::cerr << "Invalid amount of arguments: " << argc << '\n';
    return 1;
  }

  std::ifstream in;
  std::ofstream out;

  if (std::string(argv[1]) == "-i") {
    in.open(std::string(argv[2]));
  }
  else if(std::string(argv[1]) == "-o") {
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
  }

  if (!out.is_open()) {
    std::cerr << "Could not open output file\n";
  }

  CommandStack stack;

  std::string command;
  while (in >> command) {
    if (command == "GO") {
      double x = 0;
      double y = 0;
      if (!(in >> x)) {
        out << PrintError("Invalid x argument " + std::to_string(x));
        continue;
      }
      if (!(in >> y)) {
        out << PrintError("Invalid y argument " + std::to_string(y));
        continue;
      }
      stack.PrintCurrentPosition(x, y, out);
    }
    else if (command == "RE") {
      int count = 0;
      if (!(in >> count)) {
        out << PrintError("Invalid count argument " + std::to_string(count));
        continue;
      }
      stack.Pop(count);
    }
    else if (command == "GW") {
      stack.Push(std::make_unique<GoWest>(GoWest(in, out)));
    }
    else if (command == "GN") {
      stack.Push(std::make_unique<GoNorth>(GoNorth(in, out)));
    }
    else if (command == "GS") {
      stack.Push(std::make_unique<GoSouth>(GoSouth(in, out)));
    }
    else if (command == "GE") {
      stack.Push(std::make_unique<GoEast>(GoEast(in, out)));
    }
    else {
      out << PrintError("Invalid command " + command);
      break;
    }
  }

  in.close();
  out.close();
  return 0;
}