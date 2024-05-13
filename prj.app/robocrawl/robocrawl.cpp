#include <iostream>
#include <stack>

class MovementCommand {
public:
  MovementCommand(double lenght);
  MovementCommand(std::istream& in);
  virtual ~MovementCommand() = default;

  virtual std::pair<double, double> GetDelta() = 0;

  double GetLenght() const { return lenght_; }
private:
  double lenght_ = 0;
};

MovementCommand::MovementCommand(double lenght) 
  : lenght_(lenght) {
}

MovementCommand::MovementCommand(std::istream& in) {
  double lenght = 0;
  if (!(in >> lenght)) {
    std::cout << "Invalid Argument\n";
    lenght = 0;
  }
  lenght_ = lenght;
}

class GoWest : public MovementCommand {
public:
  GoWest(double lenght) : MovementCommand(lenght) {}
  GoWest(std::istream& in) : MovementCommand(in) {}
  ~GoWest() override = default;

  std::pair<double, double> GetDelta() override {
    return std::make_pair(-GetLenght(), 0.0);
  }
};

class GoEast : public MovementCommand {
public:
  GoEast(double lenght) : MovementCommand(lenght) {}
  GoEast(std::istream& in) : MovementCommand(in) {}
  ~GoEast() override = default;

  std::pair<double, double> GetDelta() override {
    return std::make_pair(GetLenght(), 0.0);
  }
};

class GoNorth : public MovementCommand {
public:
  GoNorth(double lenght) : MovementCommand(lenght) {}
  GoNorth(std::istream& in) : MovementCommand(in) {}
  ~GoNorth() override = default;

  std::pair<double, double> GetDelta() override {
    return std::make_pair(0.0, GetLenght());
  }
};

class GoSouth : public MovementCommand {
public:
  GoSouth(double lenght) : MovementCommand(lenght) {}
  GoSouth(std::istream& in) : MovementCommand(in) {}
  ~GoSouth() override = default;

  std::pair<double, double> GetDelta() override {
    return std::make_pair(0.0, -GetLenght());
  }
};

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
      std::cin >> x >> y;
      stack.PrintCurrentPosition(x, y);
    }
    else if (command == "RE") {
      int count = 0;
      std::cin >> count;
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
  }
}