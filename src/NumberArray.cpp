#include "NumberArray.h"
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <format>

template<typename T>
NumberArray<T>::NumberArray(size_t size) 
{
  // allocate array and initialize all elements to zero
  data_m = new T[size] {};   
  size_m = size;
}


template<typename T>
NumberArray<T>::NumberArray(const NumberArray& other)
  // set size and alloc zeroed array
  : size_m(other.size_m), data_m(new T[other.size_m] {})
{
  for (int i {}; i < size_m; ++i)
    data_m[i] = other.data_m[i];
}

template<typename T>
NumberArray<T>& NumberArray<T>::operator=(const NumberArray& other) 
{
  // self assignment check
  if (this == &other) 
    return *this;

  size_m = other.size_m;

  delete [] data_m;
  data_m = new T[other.size_m] {};

  for (int i {}; i < size_m; ++i)
    data_m[i] = other.data_m[i];  

  return *this;
}

template<typename T>
NumberArray<T>::~NumberArray() 
{
  // de-alloc the array
  delete [] data_m;  
  std::cout << "Deallocated data array" << std::endl;
}

template<typename T>
size_t NumberArray<T>::size() const 
{
  return size_m;
}

template<typename T>
void NumberArray<T>::setNumber(size_t index, T value) 
{
  // index validity check
  if (index >= size_m || index < 0) 
    throw std::out_of_range(
      std::format("Error; Index: {}, Size: {}", index, size_m)); 

  data_m[index] = value;
}

template<typename T>
T NumberArray<T>::getNumber(size_t index) const 
{
  // index validity check
  if (index >= size_m || index < 0) 
    throw std::out_of_range(
      std::format("Error; Index: {}, Size: {}", index, size_m)); 
  
  return data_m[index];
}

template<typename T>
T NumberArray<T>::getMin() const 
{
  // init min to the first element in the array
  T min { data_m[0] };

  // check for the smallest element in the array
  for (size_t i { 1 }; i < size_m; ++i)
  {
    if (data_m[i] < min) 
    {
      min = data_m[i];
    }
  }

  return min;
}

template<typename T>
T NumberArray<T>::getMax() const 
{
  // init max to first element in array
  T max { data_m[0] };

  // check for largest element in array
  for (size_t i { 1 }; i < size_m; ++i)
  {
    if (data_m[i] > max)
    {
      max = data_m[i];
    }
  }

  return max;
}

template<typename T>
T NumberArray<T>::getAverage() const 
{
  // might not be big enough for large arrays
  T average {};  

  // sum the array into the average var
  for (size_t i {}; i < size_m; ++i)
  {
    average += data_m[i];
  }

  // divide by num elements to get average
  return average /= size_m;  
}

template<typename T>
void NumberArray<T>::print() const 
{
  // print all the array elements
  for (size_t i {}; i < size_m; ++i)
  {
    std::cout << data_m[i] << ' ';
  }

  // flush and print a newline
  std::cout << std::endl;
}
