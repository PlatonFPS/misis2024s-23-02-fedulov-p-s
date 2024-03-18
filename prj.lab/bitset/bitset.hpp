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

  bool operator==(const BitSet& other) const;
  bool operator!=(const BitSet& other) const;

  BitSet operator~() const;
  BitSet operator&(const BitSet& other) const;
  BitSet& operator&=(const BitSet& other);
  BitSet operator|(const BitSet& other) const;
  BitSet& operator|=(const BitSet& other);
  BitSet operator^(const BitSet& other) const;
  BitSet& operator^=(const BitSet& other);
  
private:
  std::vector<uint32_t> bits_;
  int32_t size_ = 0;
};

