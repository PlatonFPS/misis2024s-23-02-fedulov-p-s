#ifndef DYNARR_HPP
#define DYNARR_HPP

#include <stdexcept>
#include <cstddef>
#include <memory>

class DynArr {
public:
  [[nodiscard]] DynArr() = default;
  [[nodiscard]] explicit DynArr(const DynArr& copy);
  [[nodiscard]] DynArr(DynArr&& other) noexcept;
  [[nodiscard]] explicit DynArr(const ptrdiff_t size);
  ~DynArr();

  DynArr& operator=(const DynArr& value);
  DynArr& operator=(DynArr&& other) noexcept;

  [[nodiscard]] std::ptrdiff_t Size() const noexcept { return size_; }
  [[nodiscard]] std::ptrdiff_t Capacity() const noexcept { return capacity_; }

  void Resize(const std::ptrdiff_t size);

  [[nodiscard]] float& operator[](const std::ptrdiff_t i);
  [[nodiscard]] const float& operator[](const std::ptrdiff_t i) const;

private:
  std::ptrdiff_t size_ = 0;
  std::ptrdiff_t capacity_ = 0;
  std::unique_ptr<float[]> data_;
  float default_value = 0;
};

#endif //DYNARR_HPP