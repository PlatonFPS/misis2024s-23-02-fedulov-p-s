#include "bitset.hpp"

#include <stdexcept>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>

const uint32_t BeginMarker = 0;
const uint32_t EndMarker = -1;

void BitSet::Write(std::ofstream& out) const {
  out.write((char*)&BeginMarker, sizeof(uint32_t));

  out.write((char*)&size_, sizeof(int32_t));

  uint32_t control_sum = 0;
  for (int i_bit = 0; i_bit < bits_.size(); i_bit += 1) {
    out.write((char*)&bits_[i_bit], sizeof(uint32_t));
    control_sum ^= bits_[i_bit];
  }
  out.write((char*)&control_sum, sizeof(uint32_t));

  out.write((char*)&EndMarker, sizeof(uint32_t));
}

void BitSet::Read(std::ifstream& in) {
  char* marker = new char[sizeof(uint32_t)];
  in.read((char*)marker, sizeof(uint32_t));
  int marker_int = *reinterpret_cast<uint32_t*>(marker);
  if(marker_int != BeginMarker) {
    std::cout << "Missing begin marker" << '\n';
    throw std::invalid_argument("Missing begin marker");
  }

  char* size_buf = new char[sizeof(int32_t)];
  in.read(size_buf, sizeof(int32_t));
  int32_t size = *reinterpret_cast<int32_t*>(size_buf);
  delete[] size_buf;
  Resize(size);

  uint32_t sum = 0;
  char* buf = new char[sizeof(uint32_t)];
  for (int i_bit = 0; i_bit < bits_.size(); i_bit += 1) {
    in.read(buf, sizeof(uint32_t));
    bits_[i_bit] = *reinterpret_cast<uint32_t*>(buf);
    sum ^= bits_[i_bit];
  }
  delete[] buf;

  char* control_sum = new char[sizeof(uint32_t)];
  in.read(control_sum, sizeof(uint32_t));
  uint32_t control_sum_int = *reinterpret_cast<uint32_t*>(control_sum);
  if (control_sum_int != sum) {
    std::cout << "Sum of bits is not equal to control sum" << '\n';
    throw std::invalid_argument("Sum of bits is not equal to control sum");
  }

  marker = new char[sizeof(uint32_t)];
  in.read((char*)marker, sizeof(uint32_t));
  marker_int = *reinterpret_cast<uint32_t*>(marker);
  if (marker_int != EndMarker) {
    std::cout << "Missing end marker" << '\n';
    throw std::invalid_argument("Missing end marker");
  }
  delete[] marker;
}

const int bits_in_line = 32;

std::ostream& BitSet::WriteToStream(std::ostream& out) const {
  out << size_ << '\n';
  if (size_ == 0) {
    return out;
  }
  int i = 0;
  for (i = 0; i < size_; i += 1) {
    out << Get(i);
    if (i % bits_in_line == bits_in_line - 1) {
      out << " " << (i / bits_in_line) * bits_in_line + 1 << '-'
                 << (i / bits_in_line + 1) * bits_in_line << '\n';
    }
  }
  
  if (size_ % bits_in_line != 0) {
    for (int j = 0; j <= bits_in_line - i % bits_in_line; j += 1) {
      out << ' ';
    }
    out << (i / bits_in_line) * bits_in_line + 1 << '-' << size_ << '\n';
  }
  return out;
}

std::istream& BitSet::ReadFromStream(std::istream& in) {
  if (in.good()) {
    in >> size_;
    Resize(size_);
    std::string line;
    std::getline(in, line);
    for (int i_line = 0; i_line < size_ / bits_in_line; i_line += 1) {
      std::getline(in, line);
      for (int i_bit = 0; i_bit < bits_in_line; i_bit += 1) {
        Set(i_bit + i_line * bits_in_line, line[i_bit] == '1');
      }
    }
    if (size_ % bits_in_line != 0) {
      std::getline(in, line);
      for (int i_bit = 0; i_bit < size_ % bits_in_line; i_bit += 1) {
        Set(i_bit + (size_ / bits_in_line) * bits_in_line, line[i_bit] == '1');
      }
    }
  }
  return in;
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
