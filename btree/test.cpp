/**
 * THE CODE HEREIN IS PROVIDED AS IS, WITH NO EXPRESS, OR IMPLIED, WARRANTIES
 * OR SUITABILITY FOR PURPOSE! This means it is up to you to figure out how
 * it works, fix it if something is broken, and adapt it as appropriate for
 * your needs.
 *
 * It is supplied as a starting point for your testing. Of course, it is 
 * inadequate as your only test and you will be in trouble if you
 * do not write lots and lots of additional tests of your own!
 **/

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <utility>

#include "btree.h"

using std::copy;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::set;
using std::string;

long getRandom(long low, long high) {
  return (low + (random() % ((high - low) + 1)));
}


/**
 * Codes for testing various bits and pieces. Most of the code is commented out
 * you should uncomment it as appropriate.
 **/
int main(void) {
  // initialise random number generator with 'random' seed

  // insert lots of random numbers and compare with a known correct container
  btree<int> t;
  // pair<btree<int>::iterator, bool> result = t.insert(1);
  // result = t->insert();
  // result = t->insert(3);


  // std::vector<int> v;
  // v.push_back(1);
  // v.push_back(2);
  // v.push_back(4);
  // v.push_back(6);
  // v.push_back(8);
  // auto lower = std::lower_bound(v.begin(), v.end(), 9);
  // std::cout << "is f end " << (lower == v.end()) << std::endl;

  // std::cout << *lower << " hey" << std::endl;


  // result = t.insert(3);
  // result = t.insert(5);
  // result = t.insert(7);

  // result = t.insert(0);

  // auto i = t.rbegin();
  // std::cout << *i << std::endl;

  // result = t.insert(2);
  // result = t.insert(2);
  // t.printAll();

  std::stringstream actual;
  actual << t;
  std::cout << actual;
  // std::cout << *(t.rbegin()) << std::endl;

  // for (auto ite = t.rbegin(); ite != t.rend(); ++ite) {
  //   std::cout << *ite << std::endl;
  // }
  // auto tree_nonconst = const_cast<btree<int>&>(t);

	// actual << tree_nonconst;
	// std::cout << actual.str();

  // btree<int> copy;
  // auto copy = std::move(t);
  // t -> printAll();
  // copy -> printAll();
	std::cout << " hhh " << std::endl; 
  // t.insert(100);
  // t.insert(4);
  // std::cout << t << std::endl;

  // std::cout << copy << "\n";

  // t.printAll();
  // copy.printAll();

  // std::cout << "\n\n\n\n" << result.second << "\n\n";
  return 0;	
}

