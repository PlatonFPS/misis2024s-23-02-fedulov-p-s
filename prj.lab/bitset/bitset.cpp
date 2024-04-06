#include "bitset.hpp"

#include <stdexcept>
#include <cstdint>
#include <fstream>

void BitSet::Write(std::ofstream& out) const {
  for (uint32_t bit : bits_) {
    out.write((char*)&bit, sizeof(uint32_t));
  }
  //out.write((char*)&size_, sizeof(int32_t));
}

void BitSet::Read(std::ifstream& in) const {
  char* buf = new char[sizeof(uint32_t)];
  for(uint32_t bit : bits_) {
    in.read(buf, sizeof(uint32_t));
    bit = *reinterpret_cast<uint32_t*>(buf);
  }
  delete[] buf;
  //char* size = new char[sizeof(int32_t)];
  //in.read(size, sizeof(size_));
  //auto it = *reinterpret_cast<int32_t*>(size);
  //size_ = 2;
}

BitSet::BiA::BiA(BitSet& bitset, const int32_t index)
  : bitset_(bitset)
  , index_(index) {
}

BitSet::BiA::operator bool() const {
  return bitset_.Get(index_);
}

void BitSet::BiA::operator=(const bool value) {
  bitset_.Set(index_, value);
}

BitSet::BiA BitSet::operator[](int32_t index) {
  return BitSet::BiA(*this, index);
}

BitSet::BitSet(int32_t size)
  : bits_(size)
  , size_(size) {
}

BitSet::BitSet(const BitSet& other)
  : bits_(other.bits_)
  , size_(other.size_) {
}

BitSet::BitSet(BitSet&& other) noexcept {
  std::swap(bits_, other.bits_);
  std::swap(size_, other.size_);
}

BitSet& BitSet::operator=(const BitSet& other) {
  bits_ = other.bits_;
  size_ = other.size_;
  return *this;
}

BitSet& BitSet::operator=(BitSet&& other) noexcept {
  bits_ = std::move(other.bits_);
  size_ = other.size_;
  other.Clear();
  return *this;
}

void BitSet::Clear() {
  bits_.clear();
  size_ = 0;
}

int32_t BitSet::Size() const {
  return size_;
}

void BitSet::Resize(const int32_t size) {
  bits_.resize((size - 1) / 32 + 1);
  if (size > size_) {
    bits_[size/32] &= ~(0) << (31 - size % 32);
  }
  size_ = size;
}

bool BitSet::Get(const int32_t index) const {
  if(index < 0 || index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return (bits_[index / 32] >> (31 - index % 32 )) & 1;
}

void BitSet::Set(const int32_t index, const bool value) {
  if(index < 0 || index >= size_) {
    throw std::out_of_range("Index out of range");
  }
  if (value) {
    bits_[index/32] |= 1 << (31 - index % 32);
  } else {
    bits_[index/32] &= ~(1 << (31 - index % 32));
  }
}

bool BitSet::operator==(const BitSet& other) const {
  if (size_ != other.size_) {
    return false;
  }
  for (size_t i = 0; i < bits_.size(); ++i) {
    if (bits_[i] != other.bits_[i]) {
      return false;
    }
  }
  return true;
}

bool BitSet::operator!=(const BitSet& other) const {
  return !(*this == other);
}

BitSet BitSet::operator~() const {
  BitSet result(*this);
  for (size_t i = 0; i < result.bits_.size(); ++i) {
    result.bits_[i] = ~result.bits_[i];
  }
  return result;
}

BitSet BitSet::operator&(const BitSet& other) const {
  if(size_ != other.size_) {
    throw std::invalid_argument("BitSets have different sizes");
  }
  BitSet result(*this);
  for (size_t i = 0; i < result.bits_.size(); ++i) {
    result.bits_[i] &= other.bits_[i];
  }
  return result;
}

BitSet& BitSet::operator&=(const BitSet& other) {
  if (size_ != other.size_) {
    throw std::invalid_argument("BitSets have different sizes");
  }
  for (size_t i = 0; i < other.bits_.size(); ++i) {
    bits_[i] &= other.bits_[i];
  }
  return *this;
}

BitSet BitSet::operator|(const BitSet& other) const {
  if (size_ != other.size_) {
    throw std::invalid_argument("BitSets have different sizes");
  }
  BitSet result(*this);
  for (size_t i = 0; i < result.bits_.size(); ++i) {
    result.bits_[i] |= other.bits_[i];
  }
  return result;
}

BitSet& BitSet::operator|=(const BitSet& other) {
  if (size_ != other.size_) {
    throw std::invalid_argument("BitSets have different sizes");
  }
  for (size_t i = 0; i < other.bits_.size(); ++i) {
    bits_[i] |= other.bits_[i];
  }
  return *this;
}

BitSet BitSet::operator^(const BitSet& other) const {
  if (size_ != other.size_) {
    throw std::invalid_argument("BitSets have different sizes");
  }
  BitSet result(*this);
  for (size_t i = 0; i < result.bits_.size(); ++i) {
    result.bits_[i] ^= other.bits_[i];
  }
  return result;
}

BitSet& BitSet::operator^=(const BitSet& other) {
  if (size_ != other.size_) {
    throw std::invalid_argument("BitSets have different sizes");
  }
  for (size_t i = 0; i < other.bits_.size(); ++i) {
    bits_[i] ^= other.bits_[i];
  }
  return *this;
}
