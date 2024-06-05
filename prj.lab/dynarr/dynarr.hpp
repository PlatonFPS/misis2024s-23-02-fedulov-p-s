#ifndef DYNARR_HPP
#define DYNARR_HPP

#include <stdexcept>
#include <cstddef>
#include <memory>

class DynArr final {
public:
  DynArr() = default;
  DynArr(const DynArr& copy);
  DynArr(DynArr&& other) noexcept;
  explicit DynArr(const ptrdiff_t size);
  ~DynArr() = default;

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