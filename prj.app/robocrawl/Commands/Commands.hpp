#include <iostream>
#include <string>

void PrintError(std::string_view message);

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

class GoWest : public MovementCommand {
public:
  GoWest(double lenght) : MovementCommand(lenght) {}
  GoWest(std::istream& in) : MovementCommand(in) {}

  std::pair<double, double> GetDelta() override {
    return std::make_pair(-GetLenght(), 0.0);
  }
};

class GoEast : public MovementCommand {
public:
  GoEast(double lenght) : MovementCommand(lenght) {}
  GoEast(std::istream& in) : MovementCommand(in) {}

  std::pair<double, double> GetDelta() override {
    return std::make_pair(GetLenght(), 0.0);
  }
};

class GoNorth : public MovementCommand {
public:
  GoNorth(double lenght) : MovementCommand(lenght) {}
  GoNorth(std::istream& in) : MovementCommand(in) {}

  std::pair<double, double> GetDelta() override {
    return std::make_pair(0.0, GetLenght());
  }
};

class GoSouth : public MovementCommand {
public:
  GoSouth(double lenght) : MovementCommand(lenght) {}
  GoSouth(std::istream& in) : MovementCommand(in) {}

  std::pair<double, double> GetDelta() override {
    return std::make_pair(0.0, -GetLenght());
  }
};