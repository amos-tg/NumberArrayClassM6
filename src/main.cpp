#include "NumberArray.h"
#include <cassert>
#include <iostream>
#include <cstddef>
#include <random>
#include <stdexcept>

using namespace std;

const char *TEST_PASS = "Passed";

const char *DEFAULT_CONSTRUCTOR_TEST = "Test (NumberArray<double> constructor): "; 
const char *PARAM_CONSTRUCTOR_TEST = 
  "Test (NumberArray<double> Parameterized constructor): ";
const char *SET_GET_NUMBER_TESTS = "Test (NumberArray<double> {set,get}Number methods): "; 
const char *STATISTICAL_TESTS = 
  "Test (NumberArray<double> {min,max,average}Number methods): ";
const char *PRINT_TEST = "Test (NumberArray<double> print method): ";
const char *EDGE_CASE_TEST = "Test (NumberArray<double> edge case tests): ";
const char *COPY_CONSTRUCTOR_TEST = "Test (NumberArray<double> copy constructor tests): ";
const char *ASSIGNMENT_OPERATOR_TEST = "Test (NumberArray<double> assignment operator tests): ";
const char *DESTRUCT_LIFETIME_TEST = "Test (NumberArray<double> destructor lifetime tests): ";

// The test functions follow the testing documents specifications in order,
// both internally, and in terms of their calling sequence in main().

/// tests the default constructor of the NumberArray<{double,int}> 
/// template class instantiations
void defaultConstructorTest(void);

/// tests the parameterized constructor of NumberArray<{double, int}>
/// template class intantiations 
void paramConstructorTest(void);

/// tests the set and get Number methods of the NumberArray<double> class
void setGetNumberTests(void);

/// tests the {min,max,average}Number methods of the NumberArray<double> class
void statisticalTests(void);

/// tests the print method of the NumberArray<double> class
void printTests(void);

/// tests the edge case uses of the NumberArray<double> class
void edgeCaseTests(void);

/// tests the copy constructor of the NumberArray<double> class
void copyConstructorTests(void);

/// tests the assignment operator of the NumberArray<double> class
void assignmenOpTests(void);

/// tests that lifetimes are properly handled by the destructor.
void destructLifetimeTests(void);

int main(void)
{
  defaultConstructorTest();  
  cout << '\n';
  paramConstructorTest();
  cout << '\n';
  setGetNumberTests();
  cout << '\n';
  statisticalTests();
  cout << '\n';
  printTests();
  cout << '\n';
  edgeCaseTests();
  cout << '\n';
  copyConstructorTests();
  cout << '\n';
  assignmenOpTests();
  cout << '\n';
  destructLifetimeTests();

  return 0;
}

void defaultConstructorTest(void) 
{
  cout << DEFAULT_CONSTRUCTOR_TEST;

  // M6 test create NumberArray<{int,double}> and verify both compile and run
  NumberArray<int> def_iarr {}; 
  NumberArray<int> iarr { 15 };
  NumberArray<double> def_darr {};
  NumberArray<double> darr { 15 };

  assert(def_darr.size() == NumberArray<double>::DEFAULT_SIZE);

  for (int i {}; i < def_darr.size(); ++i)
    assert(def_darr.getNumber(i) == 0.0);

  cout << '\n';
  def_darr.print();
  cout << TEST_PASS << endl;
} 

void paramConstructorTest(void)
{
  cout << PARAM_CONSTRUCTOR_TEST;

  const size_t SET_SIZE { 10 };

  NumberArray<double> test { SET_SIZE };
  NumberArray<int> test2 { SET_SIZE };
  
  assert(test.size() == SET_SIZE);
  assert(test2.size() == SET_SIZE);

  for (int i {}; i < test.size(); ++i)
    assert(test.getNumber(i) == 0.0);

  cout << TEST_PASS << endl;
}

void setGetNumberTests(void) 
{
  cout << SET_GET_NUMBER_TESTS;

  NumberArray<int> def_iarr {}; 
  NumberArray<double> def_darr {};
  
  // check the sizes are the default size
  assert(
    (def_iarr.size() & def_darr.size()) == NumberArray<int>::DEFAULT_SIZE);

  // access valid indexes
  try {
    assert(def_iarr.getNumber(0) == 0);  
    assert(def_darr.getNumber(0) == 0.0);
  } catch (const out_of_range& err) {
    cerr << err.what() << endl;
    terminate();
  }

  // access invalid index, int=T
  bool caught { false };  
  try {
    // should throw, out of range by one
    def_iarr.getNumber(NumberArray<int>::DEFAULT_SIZE);    
  } catch (const out_of_range& err) {
    caught = true;
  }
  assert(caught);

  // access invalid index, double=T
  caught = false;  
  try {
    // should throw, size_t implicit casted -1 wraps to max
    def_darr.getNumber(-1);    
  } catch (const out_of_range& err) {
    caught = true;
  }
  assert(caught);

  cout << '\n' << TEST_PASS << endl;
}

void statisticalTests(void)
{
  cout << STATISTICAL_TESTS;
  NumberArray<double> tested { 10 };
  double max, min, average;

  // using preset values
  for (int i {}, set { 1 }; i < tested.size(); ++i, ++set)
  {
    tested.setNumber(i, set);
  }
  
  assert(tested.getMax() == 10.0);
  assert(tested.getMin() == 1.0);
  assert(tested.getAverage() == 5.5);

  // using random values, pseudo-random gen seeded with random gen, only random
  // on certain platforms.
  random_device rand;  
  mt19937 prand { rand() };
  uniform_real_distribution<> gen(0.0, 30.0);
  for (int i {}; i < tested.size(); ++i)
  {
    tested.setNumber(i, gen(prand));
  }

  max = tested.getMax();
  min = tested.getMin();
  average = tested.getAverage();

  assert(min <= average && average <= max);

  cout << '\n' 
    << "Minimum: " << min << '\n'
    << "Maximum: " << max << '\n'
    << "Average: " << average << '\n';

  cout << TEST_PASS << endl;
}

void printTests(void) 
{
  cout << PRINT_TEST;
  NumberArray<double> test {};
  cout << '\n';
  test.print();

  for (int i {}, set { 1 }; i < test.size(); ++i, ++set)
  {
    test.setNumber(i, set);
  }
  test.print();

  cout << TEST_PASS << endl;
}

void edgeCaseTests(void)
{
  cout << EDGE_CASE_TEST;
  NumberArray<double> test { 1 };
  assert(test.getNumber(0) == 0.0);
  test.setNumber(0, 10.0);
  assert(test.getNumber(0) == 10.0);
  test.setNumber(0, -11.123);
  assert(test.getNumber(0) == -11.123);
  assert(test.getMax() == -11.123);
  assert(test.getMin() == -11.123);
  assert(test.getAverage() == -11.123);
  cout << '\n';
  test.print();

  // make sure zero size arrays don't crash
  bool caught { false };
  try 
  {
    NumberArray<double> zero { 0 }; 
    zero.setNumber(0, 1.0);
  }
  catch (const out_of_range& err)
  { 
    caught = true;
  }

  assert(caught);
  

  // larger array size
  size_t big_size { 1'000'000 };
  NumberArray<double> big { big_size };
  assert(big.size() == big_size);

  {
    NumberArray<double> big2 { big };
    {
      // copy constructor and assignment operator
      // copy constructor (big3 = big2...) 
      // assignment operator (...big2 = big)
      NumberArray<double> big3 = big2 = big;
    }
  }

  cout << TEST_PASS << endl;
}

void copyConstructorTests(void)
{
  cout << COPY_CONSTRUCTOR_TEST;
  
  // create a new object
  size_t size { 20 };
  NumberArray<double> orig { size };

  // put some values in original object
  for (int i {}; i < size; ++i)
    orig.setNumber(i, i);

  // copy original object with copy constructor
  NumberArray<double> copied { orig };
  assert(orig.size() == copied.size());

  // verify values were copied
  for (int i {}; i < size; ++i)
    assert(copied.getNumber(i) == orig.getNumber(i));

  //  modify orig. and confirm copy doesn't change
  orig.setNumber(size / 2, 25.555555);
  assert(copied.getNumber(size / 2) != 25.555555);

  // modify copy and confirm orig. doesn't change
  copied.setNumber(size / 3, 21.21);
  assert(orig.getNumber(size / 3) != 21.21);

  cout << TEST_PASS << endl;
}

void assignmenOpTests(void)
{
  cout << ASSIGNMENT_OPERATOR_TEST;
  
  // create two objs of the same size 
  size_t size { 25 };
  NumberArray<double> assigned { size };
  NumberArray<double> source { size };

  // give some values to obj1
  for (int i {}; i < size; ++i)
    source.setNumber(i, 11.11);

  // assign one to other
  assigned = source; 

  // verify correct copy
  for (int i {}; i < size; ++i)
    assert(assigned.getNumber(i) == source.getNumber(i));

  // modify source object & confirm assigned object doesn't change
  source.setNumber(size / 2, 22.9181); 
  assert(assigned.getNumber(size / 2) != 22.9181);

  // modify assigned object & confirm source object doesn't change
  assigned.setNumber(size / 2, 423.12848); 
  assert(source.getNumber(size / 2) != 423.12848);

  // size difference test
  size_t size_1 { 20 }, size_2 { 40 };
  NumberArray<double> obj1 { size_1 }, obj2 { size_2 };

  obj2.setNumber(0, 10.0);
  obj2.setNumber(size_2 - 1, 10.0);

  // assign larger to smaller
  obj1 = obj2;

  // check that the size changed and that values are copied correctly
  assert(obj1.size() == size_2);
  assert(obj1.getNumber(size_2 - 1) == 10.0);
  assert(obj1.getNumber(0) == 10.0);

  // self assignment test
  obj1 = obj1;
  
  // data remains unchanged 
  assert(obj1.size() == size_2);
  assert(obj1.getNumber(size_2 - 1) == 10.0);
  assert(obj1.getNumber(0) == 10.0);

  cout << TEST_PASS << endl;
}

void destructLifetimeTests(void)
{
  cout << DESTRUCT_LIFETIME_TEST << endl;
  // create objects inside a block scope
  {
    NumberArray<double> obj1, obj2;

    // tests assignment chaining as well
    obj1 = obj2 = NumberArray<double>{};
  }

  // should be three messages outputted
  
  cout << TEST_PASS << endl;
}
