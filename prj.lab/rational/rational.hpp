#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <cstdint>
#include <iosfwd>

class Rational final {
public:
  Rational() = default;
  explicit Rational(const int64_t number);
  Rational(const int64_t number, const int64_t denominator);
  Rational(const Rational& c) = default;
  Rational(Rational&& copy) noexcept = default;

  ~Rational() = default;

  [[nodiscard]] int64_t num() const noexcept { return num_; }
  [[nodiscard]] int64_t den() const noexcept { return den_; }

  Rational& operator=(const Rational& copy) = default;
  Rational& operator=(Rational&& copy) noexcept = default;

  [[nodiscard]] Rational operator-() const noexcept { return { -num_, den_ }; }

  [[nodiscard]] bool operator==(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator==(const int64_t rhs) const noexcept;
  [[nodiscard]] bool operator!=(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator!=(const int64_t rhs) const noexcept;
  [[nodiscard]] bool operator<(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator<(const int64_t rhs) const noexcept;
  [[nodiscard]] bool operator<=(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator<=(const int64_t rhs) const noexcept;
  [[nodiscard]] bool operator>(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator>(const int64_t rhs) const noexcept;
  [[nodiscard]] bool operator>=(const Rational& rhs) const noexcept;
  [[nodiscard]] bool operator>=(const int64_t rhs) const noexcept;

  Rational& operator+=(const Rational& rhs) noexcept;
  Rational& operator+=(const int64_t rhs) noexcept { return operator+=(Rational(rhs)); }

  Rational& operator-=(const Rational& rhs) noexcept;
  Rational& operator-=(const int64_t rhs) noexcept { return operator-=(Rational(rhs)); }

  Rational& operator*=(const Rational& rhs) noexcept;
  Rational& operator*=(const int64_t rhs) noexcept { return operator*=(Rational(rhs)); }

  Rational& operator/=(const Rational& rhs);
  Rational& operator/=(const int64_t rhs) { return operator/=(Rational(rhs)); }

  std::ostream& WriteTo(std::ostream& ostrm) const noexcept;
  std::istream& ReadFrom(std::istream& istrm) noexcept;
private:
  int64_t num_ = 0;
  int64_t den_ = 1;
  static const char separator = '/';

  void CheckSign() noexcept;
  void SimplifyFraction() noexcept;
};

[[nodiscard]] Rational operator+(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator+(const Rational& lhs, const int64_t rhs) noexcept;
[[nodiscard]] Rational operator+(const int64_t lhs, const Rational& rhs) noexcept;

[[nodiscard]] Rational operator-(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator-(const Rational& lhs, const int64_t rhs) noexcept;
[[nodiscard]] Rational operator-(const int64_t lhs, const Rational& rhs) noexcept;

[[nodiscard]] Rational operator*(const Rational& lhs, const Rational& rhs) noexcept;
[[nodiscard]] Rational operator*(const Rational& lhs, const int64_t rhs) noexcept;
[[nodiscard]] Rational operator*(const int64_t lhs, const Rational& rhs) noexcept;

[[nodiscard]] Rational operator/(const Rational& lhs, const Rational& rhs);
[[nodiscard]] Rational operator/(const Rational& lhs, const int64_t rhs);
[[nodiscard]] Rational operator/(const int64_t lhs, const Rational& rhs);

inline std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
  return rhs.WriteTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
  return rhs.ReadFrom(istrm);
}
#endif //RATIONAL_HPP