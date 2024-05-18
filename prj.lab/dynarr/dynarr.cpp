#include "dynarr.hpp"

#include <cstring>

DynArr::DynArr(const DynArr& copy) 
  : size_(copy.Size())
  , capacity_(size_) {
  data_ = std::make_unique<float[]>(size_);
  std::memcpy(data_.get(), copy.data_.get(), sizeof(float) * size_);
}

DynArr::DynArr(DynArr&& other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

DynArr::DynArr(const ptrdiff_t size) {
  if (size <= 0) {
    throw std::invalid_argument("Positive size is required");
  }
  size_ = size;
  capacity_ = size_;
  data_ = std::make_unique<float[]>(size_);
  std::memset(data_.get(), default_value, sizeof(float) * size_);
}

void DynArr::Resize(const std::ptrdiff_t size) {
  if (size <= 0) {
    throw std::invalid_argument("Positive size is required");
  } 
  if (capacity_ > size) {
    for (int i_float = size; i_float < size_; i_float += 1) {
      *(data_.get() + i_float) = default_value;
    }
  } else {
    float* temp_data = new float[size];
    for (int i_float = 0; i_float < size_; i_float += 1) {
      *(temp_data + i_float) = *(data_.get() + i_float);
    }
    for (int i_float = size_; i_float < size; i_float += 1) {
      *(temp_data + i_float) = default_value;
    }
    data_.release();
    data_.reset(temp_data);
    capacity_ = size;
  }
  size_ = size;
  return;
}

DynArr& DynArr::operator=(const DynArr& value) {
  if (this != &value) {
    data_.release();
    size_ = value.Size();
    capacity_ = value.Capacity();
    data_ = std::make_unique<float[]>(size_);
    std::memcpy(data_.get(), value.data_.get(), sizeof(float) * size_);
  }
  return *this;
}

DynArr& DynArr::operator=(DynArr&& value) noexcept {
  if(this != &value) {
    data_ = std::move(value.data_);
    size_ = value.size_;
    capacity_ = value.capacity_;
    value.data_.release();
    value.size_ = 0;
    value.capacity_ = 0;
  }
  return *this;
}

float& DynArr::operator[](const std::ptrdiff_t index) {
  if (index >= size_ || index < 0) {
    throw std::invalid_argument("Index out of range");
  }
  return *(data_.get() + index);
}

const float& DynArr::operator[](const std::ptrdiff_t index) const {
  if (index >= size_ || index < 0) {
    throw std::invalid_argument("Index out of range");
  }
  return *(data_.get() + index);
}

