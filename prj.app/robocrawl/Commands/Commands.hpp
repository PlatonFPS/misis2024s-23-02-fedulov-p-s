#include <iostream>
#include <string>

std::string PrintError(const std::string& message);

class Command {
public:
  virtual ~Command() = default;

  virtual std::unique_ptr<Command> ParseFromLine(const std::string& line) = 0;
};

class MovementCommand : public Command {
public:
  virtual ~MovementCommand() = default;

protected:
  double lenght;
};

class GoWest : public MovementCommand {
public:
  GoWest() = default;
  ~GoWest() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line) override;
};

class GoEast : public MovementCommand {
public:
  GoEast() = default;
  ~GoEast() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line) override;
};

class GoNorth : public MovementCommand {
public:
  GoNorth() = default;
  ~GoNorth() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line) override;
};

class GoSouth : public MovementCommand {
public:
  GoSouth() = default;
  ~GoSouth() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line) override;
};