#include <iostream>
#include <string>
#include <vector>

std::string PrintError(const std::string& message);

class Command {
public:
  virtual ~Command() = default;

  virtual std::unique_ptr<Command> ParseFromLine(const std::string& line, bool& success, std::ostream& out) = 0;
  virtual std::pair<double, double> Execute(bool& success, std::ostream& out) = 0;
protected:
  std::string name;
};

bool ParseFromLine(const std::string& line, std::ostream& out);

class ExecCommand : public Command {
public:
  virtual ~ExecCommand() = default;
};

class Go : public Command {
public:
  Go() = default;
  Go(double x, double y) : x_(x), y_(y) {}
  ~Go() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line, bool& success, std::ostream& out) override;
  std::pair<double, double> Execute(bool& success, std::ostream& out) override;
private:
  double x_ = 0;
  double y_ = 0;
  std::string name = "GO";
};

class Re : public Command {
public:
  Re() = default;
  Re(int count) : count_(count) {}
  ~Re() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line, bool& success, std::ostream& out) override;
  std::pair<double, double> Execute(bool& success, std::ostream& out) override;
private:
  std::string name = "RE";
  int count_ = 0;
};

class MemoryCommand : public Command {
public:
  virtual ~MemoryCommand() = default;

  static std::vector<std::unique_ptr<Command>> commands;
};

class GoWest : public MemoryCommand {
public:
  GoWest() = default;
  GoWest(double lenght) : x_(-lenght), y_(0) {}
  ~GoWest() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line, bool& success, std::ostream& out) override;
  std::pair<double, double> Execute(bool& success, std::ostream& out) override;

private:
  double x_ = 0;
  double y_ = 0;
  std::string name = "GW";
};

class GoEast : public MemoryCommand {
public:
  GoEast() = default;
  GoEast(double lenght) : x_(lenght), y_(0) {}
  ~GoEast() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line, bool& success, std::ostream& out) override;
  std::pair<double, double> Execute(bool& success, std::ostream& out) override;

private:
  double x_ = 0;
  double y_ = 0;
  std::string name = "GE";
};

class GoNorth : public MemoryCommand {
public:
  GoNorth() = default;
  GoNorth(double lenght) : x_(0), y_(lenght) {}
  ~GoNorth() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line, bool& success, std::ostream& out) override;
  std::pair<double, double> Execute(bool& success, std::ostream& out) override;

private:
  double x_ = 0;
  double y_ = 0;
  std::string name = "GN";
};

class GoSouth : public MemoryCommand {
public:
  GoSouth() = default;
  GoSouth(double lenght) : x_(0), y_(-lenght) {}
  ~GoSouth() = default;

  std::unique_ptr<Command> ParseFromLine(const std::string& line, bool& success, std::ostream& out) override;
  std::pair<double, double> Execute(bool& success, std::ostream& out) override;

private:
  double x_ = 0;
  double y_ = 0;
  std::string name = "GS";
};