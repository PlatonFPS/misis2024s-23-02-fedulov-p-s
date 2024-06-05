#pragma once

#include <vector>
#include <cstdint>
#include <iosfwd>

class BitSet {
public:
  class BiA {
  public:
    BiA() = delete;
    BiA(const BiA& bia) = delete;
    BiA(BiA&& bia) noexcept = default;
    BiA(BitSet& bitset, const int32_t index);
    ~BiA() = default;

    operator bool() const { return bitset_.Get(index_); }

    BiA& operator=(const bool value);

    BiA& operator=(const BiA& bia);
    BiA& operator=(BiA&& bia) noexcept;

  private:
    BitSet& bitset_;
    int32_t index_;
  };

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

  BiA operator[](const int32_t index);

  void Write(std::ofstream& out) const;
  void Read(std::ifstream& in);

  std::ostream& WriteToStream(std::ostream& out) const;
  std::istream& ReadFromStream(std::istream& in);

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

inline std::ostream& operator<<(std::ostream& out, const BitSet& bitset) {
  return bitset.WriteToStream(out);
}

inline std::istream& operator>>(std::istream& in, BitSet& bitset) {
  return bitset.ReadFromStream(in);
}