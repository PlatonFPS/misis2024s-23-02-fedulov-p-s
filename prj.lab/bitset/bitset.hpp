#pragma once

#include <vector>
#include <cstdint>

class BitSet {
public:
  BitSet() = default;
  BitSet(int32_t size);
  BitSet(const BitSet& other);
  BitSet(BitSet&& other) noexcept;
  ~BitSet() = default;

  BitSet& operator=(const BitSet& other);
  BitSet& operator=(BitSet&& other) noexcept;

  void Clear();

  int32_t Size() const;
  void Resize(const int32_t size);

  bool Get(const int32_t index) const;
  void Set(const int32_t index, const bool value);

  BitSet operator~() const;
  
private:
  std::vector<uint32_t> bits_;
  int32_t size_ = 0;
};