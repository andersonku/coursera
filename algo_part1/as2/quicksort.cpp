#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm> // for std::copy

using namespace std;

int&  Median(int& a, int& b, int& c) {
  if (a < b) {
    if (b < c) {
      return b;
    } else {
      return (a > c) ? a : c;
    }
  } else {
    if (a < c) {
      return a;
    } else {
      return (b > c) ? b : c;
    }
  }
}

vector<int>::iterator Partition(vector<int>::iterator begin, vector<int>::iterator end) {
  int& median = Median(*begin, *(end-1), *(begin + (end - begin - 1)/2));
  swap(*begin, median);
  auto i = begin + 1;
  for (auto j = i; j < end; ++j) {
    if (*j < *begin) {
      swap(*i, *j);
      ++i;
    }
  }
  swap(*begin, *(i-1));
  return i-1;
}

vector<int>::size_type BubuSort(vector<int>::iterator begin, vector<int>::iterator end) {
  if ( (end == begin) || ( begin + 1 == end ) ) {
    return 0;
  }
  auto pivot = Partition(begin, end);
  return BubuSort(begin, pivot) + BubuSort(pivot + 1, end) + (end - begin -1);  
}

int main(int argc, char** argv) {
  std::ifstream is(argv[1]);
  std::istream_iterator<int> start(is), end;
  std::vector<int> numbers(start, end);
  std::cout << "Read " << numbers.size() << " numbers" << std::endl;

  auto count = BubuSort(numbers.begin(), numbers.end());

  std::cout << "numbers read in:\n";
  std::copy(numbers.begin(), numbers.end(), 
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  cout << "Count = " << count << endl;
}
