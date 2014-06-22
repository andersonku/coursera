#include "gtest/gtest.h"
#include "graph.h"
#include <unordered_set>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm> // for std::copy
#include <set>

using namespace std;

TEST(ReadFromFile, 1) {
  Heap h(100);
  EXPECT_EQ(h.toString(), "");
  h.insert(100);
  EXPECT_EQ(h.toString(), "100 ");
  h.insert(20);
  EXPECT_EQ(h.toString(), "20 100 ");
  h.insert(10);
  EXPECT_EQ(h.toString(), "10 100 20 ");
  h.insert(5);
  EXPECT_EQ(h.toString(), "5 10 20 100 ");
}

TEST(TWOSUM, 0) {
  ifstream is("2sum.txt");
  string line;
  vector<long> numbers;
  numbers.reserve(1000000);

  while(getline(is, line)) {
    istringstream iss(line);
    //long num;
    long num;
    iss >> num;
    numbers.push_back(num);
  }
  sort(numbers.begin(), numbers.end());
  unordered_set<long> ts;
  for ( auto x : numbers ) {
    vector<long>::iterator start = lower_bound( numbers.begin(), numbers.end(), -10000 - x );
    vector<long>::iterator end   = upper_bound( numbers.begin(), numbers.end(), 10000 - x );
    for ( ; start != end; ++start ) {
      if ( *start != x ) {
        ts.insert(*start + x);
      }
    }
  }
  cout << "Count = " << ts.size() << " " << numbers.size() << endl;
}

TEST(TWOSUM, 1) {
  return;
  int count = 0;
  ifstream is("2sum.txt");
  string line;
  //unordered_set<long> numbers;
  set<long> numbers;
  //numbers.reserve(1000000);
  //numbers.rehash(1000);

  while(getline(is, line)) {
    istringstream iss(line);
    //long num;
    long num;
    iss >> num;
    numbers.insert(num);
  }

  //  numbers.rehash(1000000);

  //return;
  for (int sum = -10000; sum <= 10000; ++sum) {
    for (auto x : numbers) {
      //unordered_set<long>::iterator it = numbers.find(sum-x);
      set<long>::iterator it = numbers.find(sum-x);

      if ( it != numbers.end() && *it != x ) {
        ++count;
        break;
      }
    }
  }
  cout << "Size = " << numbers.size() << " count = " << count << endl;
  // 359
}

TEST(MEAN, 1) {
  int count = 0;
  ifstream is("Median.txt");
  string line;
  set<int> numbers;
  int mediumSum = 0;

  while(getline(is, line)) {
    istringstream iss(line);
    int num;
    iss >> num;
    numbers.insert(num);
    set<int>::iterator it = numbers.begin();
    if(numbers.size() % 2 == 1) {
      advance( it, numbers.size()/2 );
    } else {
      advance( it, numbers.size()/2 - 1 );
    }
    mediumSum += *it;
  }
  cout << "Size = " << numbers.size() << " mediumSum = " << mediumSum << endl;

}
