#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iosfwd>
#include <stdexcept>

struct Complex {
  Complex() = default;
  explicit Complex(const double real);
  explicit Complex(const double real, const double imaginary);
  Complex(const Complex& copy) = default;
  Complex(Complex&& copy) noexcept = default;

  ~Complex() = default;

  inline Complex Conjugate() const noexcept;

  Complex& operator=(const Complex& copy) = default;
  Complex& operator=(Complex&& copy) noexcept = default;

  [[nodiscard]] Complex operator-() const noexcept { return Complex(-re, -im); }

  [[nodiscard]] bool operator==(const Complex& rhs) noexcept;
  [[nodiscard]] bool operator!=(const Complex& rhs) noexcept;

  Complex& operator+=(const Complex& rhs) noexcept;
  Complex& operator+=(const double rhs) noexcept;

  Complex& operator-=(const Complex& rhs) noexcept;
  Complex& operator-=(const double rhs) noexcept;

  Complex& operator*=(const Complex& rhs) noexcept;
  Complex& operator*=(const double rhs) noexcept;

  Complex& operator/=(double rhs);
  Complex& operator/=(const Complex& rhs);

  std::ostream& WriteToStream(std::ostream& ostrm) const noexcept;
  std::istream& ReadFromStream(std::istream& istrm) noexcept;

  double re{ 0.0 };
  double im{ 0.0 };

  static const char leftBrace{ '{' };
  static const char separator{ ',' };
  static const char rightBrace{ '}' };
};

[[nodiscard]] bool operator==(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] bool operator!=(const Complex& lhs, const Complex& rhs) noexcept;

[[nodiscard]] Complex operator+(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator+(const Complex& lhs, const double rhs) noexcept;
[[nodiscard]] Complex operator+(const double lhs, const Complex& rhs) noexcept;

[[nodiscard]] Complex operator-(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator-(const Complex& lhs, const double rhs) noexcept;
[[nodiscard]] Complex operator-(const double lhs, const Complex& rhs) noexcept;

[[nodiscard]] Complex operator*(const Complex& lhs, const Complex& rhs) noexcept;
[[nodiscard]] Complex operator*(const Complex& lhs, const double rhs) noexcept;
[[nodiscard]] Complex operator*(const double lhs, const Complex& rhs) noexcept;

[[nodiscard]] Complex operator/(const Complex& lhs, const Complex& rhs);
[[nodiscard]] Complex operator/(const Complex& lhs, const double rhs);
[[nodiscard]] Complex operator/(const double lhs, const Complex& rhs);

[[nodiscard]] bool TestParse(const std::string& str) noexcept;

inline std::istream& operator>>(std::istream& istrm, Complex& rhs) noexcept {
  return rhs.ReadFromStream(istrm);
}

inline std::ostream& operator<<(std::ostream& ostrm, const Complex& rhs) noexcept {
  return rhs.WriteToStream(ostrm);
}
#endif //COMPLEX_HPP