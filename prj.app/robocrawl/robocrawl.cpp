#include <commands/commands.hpp>

#include <iostream>
#include <stack>

class CommandStack {
public:
  CommandStack() = default;

  void Push(MovementCommand* ptr);
  void Pop(int count);

  void PrintCurrentPosition(double x, double y);
private:
  std::stack<MovementCommand*> commands;
  double x_ = 0;
  double y_ = 0;
};

void CommandStack::Push(MovementCommand* ptr){
  commands.push(ptr);
  x_ += ptr->GetDelta().first;
  y_ += ptr->GetDelta().second;
}

void CommandStack::Pop(int count) {
  while (count > 0 && !commands.empty()) {
    x_ -= commands.top()->GetDelta().first;
    y_ -= commands.top()->GetDelta().second;
    commands.pop();
    ++count;
  }
}

void CommandStack::PrintCurrentPosition(double x, double y) {
  std::cout << x + x_ << ' ' << y + y_ << '\n';
}

int main() {
  CommandStack stack;

  std::string command;
  while (std::cin >> command) {
    if (command == "GO") {
      double x = 0;
      double y = 0;
      if (!(std::cin >> x)) {
        PrintError("Invalid x argument " + std::to_string(x));
        continue;
      }
      if (!(std::cin >> y)) {
        PrintError("Invalid y argument " + std::to_string(y));
        continue;
      }
      stack.PrintCurrentPosition(x, y);
    }
    else if (command == "RE") {
      int count = 0;
      if (!(std::cin >> count)) {
        PrintError("Invalid count argument " + std::to_string(count));
        continue;
      }
      stack.Pop(count);
    }
    else if (command == "GW") {
      stack.Push(new GoWest(std::cin));
    }
    else if (command == "GN") {
      stack.Push(new GoNorth(std::cin));
    }
    else if (command == "GS") {
      stack.Push(new GoSouth(std::cin));
    }
    else if (command == "GE") {
      stack.Push(new GoEast(std::cin));
    }
    else {
      PrintError("Invalid command " + command);
      break;
    }
  }
}