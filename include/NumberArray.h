#ifndef NUMBER_ARRAY_H
#define NUMBER_ARRAY_H

#include <limits>
#include <cstddef>

template<typename T>
class NumberArray {
  /// size of the array in terms of total number of double elements
  size_t size_m;

  /// the dynamically allocated array of size size_m of doubles
  T *data_m;
public:
  /// An extrememly unlikely to be used value; it might be better to use a 
  /// flag, but this will work just as well %99.99... of the time.
  static constexpr double INVALID = std::numeric_limits<double>::denorm_min();

  /// Default array size when the constructor is not passed a specific size.
  static const size_t DEFAULT_SIZE = 128;

  /// - size_t size : defaults to NumberArray::DEFAULT_SIZE, the size of the
  ///  array you want allocated in terms of the number of elements.
  ///  
  /// Instantiates a NumberArray class, which allows dynamic allocation of an
  /// array of type T. The size argument indicates the number of type T
  /// elements you want to be able to fit in the array maximally.  
  NumberArray(size_t size = DEFAULT_SIZE);

  NumberArray(const NumberArray& other);

  NumberArray& operator=(const NumberArray& other);

  /// Deallocates the dynamically allocated double array, and prints a message
  /// which indicates that has been done.
  ~NumberArray();

  /// returns the size of the array, the total number of double elements the
  /// array has space for.
  size_t size() const; 

  /// - size_t index : the index of the array which is assigned value.
  /// - double value : the value which is assigned to the given index of the
  /// array.
  ///
  /// The index given must be valid relative to the total size of the array.
  /// Assigns the element at index to value.
  void setNumber(size_t index, T value);

  /// - size_t index
  ///
  /// The index given must be valid relative to the total size of the array.
  /// Returns the type T value present in the array at the given index.
  T getNumber(size_t index) const;

  /// Returns the smallest number in the array.
  T getMin() const;

  /// Returns the largest number in the array.
  T getMax() const;

  /// Returns a type T value that is the average across all elements of the
  /// array.
  T getAverage() const;

  /// Prints out all the values in the array.
  void print() const;
};

#endif
