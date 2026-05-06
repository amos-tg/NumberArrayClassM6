#ifndef NUMBER_ARRAY_H
#define NUMBER_ARRAY_H

#include <cstddef>
#include <iostream>
#include <format>
#include <stdexcept>

template<typename T>
class NumberArray {
  /// size of the array in terms of total number of type T elements
  size_t size_m;

  /// the dynamically allocated array of size size_m of type T
  T *data_m;
public:
  /// Default array size when the constructor is not passed a specific size.
  static const size_t DEFAULT_SIZE = 128;

  /// - size_t size : defaults to NumberArray::DEFAULT_SIZE, the size of the
  ///  array you want allocated in terms of the number of elements.
  ///  
  /// Instantiates a NumberArray class, which allows dynamic allocation of an
  /// array of type T. The size argument indicates the number of type T
  /// elements you want to be able to fit in the array maximally.  
  NumberArray(size_t size = DEFAULT_SIZE) 
  {
    // allocate array and initialize all elements to zero
    data_m = new T[size] {};   
    size_m = size;
  }

  /// copy constructor
  NumberArray(const NumberArray<T>& other)
    // set size and alloc zeroed array
    : size_m(other.size_m), data_m(new T[other.size_m] {})
  {
    for (int i {}; i < size_m; ++i)
      data_m[i] = other.data_m[i];
  }

  /// copy assignment operator
  NumberArray& operator=(const NumberArray<T>& other)
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

  /// Deallocates the dynamically allocated array, and prints a message
  /// which indicates that has been done.
  ~NumberArray()
  {
    // de-alloc the array
    delete [] data_m;  
    std::cout << "Deallocated data array" << std::endl;
  }

  /// returns the size of the array, the total number of Type T elements the
  /// array has space for.
  inline size_t size() const
  { return size_m; }

  /// - size_t index : the index of the array which is assigned value.
  /// - Type T value : the value which is assigned to the given index of the
  /// array.
  ///
  /// The index given must be valid relative to the total size of the array.
  /// Assigns the element at index to value.
  void setNumber(size_t index, T value)
  {
    // index validity check
    if (index >= size_m) 
      throw std::out_of_range(
        std::format("NumberArray::setNumber: Index: {}, Size: {}", index, size_m)); 

    data_m[index] = value;
  }

  /// - size_t index
  ///
  /// The index given must be valid relative to the total size of the array.
  /// Returns the type T value present in the array at the given index.
  T getNumber(size_t index) const
  {
    // index validity check
    if (index >= size_m) 
      throw std::out_of_range(
        std::format("NumberArray::getNumber: Index: {}, Size: {}", index, size_m)); 
    
    return data_m[index];
  }

  /// Returns the smallest number in the array.
  T getMin() const
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

  /// Returns the largest number in the array.
  T getMax() const
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

  /// Returns a type T value that is the average across all elements of the
  /// array.
  T getAverage() const
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

  /// Prints out all the values in the array.
  void print() const
  {
    // print all the array elements
    for (size_t i {}; i < size_m; ++i)
    {
      std::cout << data_m[i] << ' ';
    }

    // flush and print a newline
    std::cout << std::endl;
  }
};

#endif
