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
  btree<char> *t = new btree<char>(40);
  pair<btree<char>::iterator, bool> result = t->insert('A');
  result = t->insert('Z');
  // result = t->insert('C');
  
  btree<char> cp;
  cp = *t;
  // t->printAll();
  
  ofstream ofs1("out1");

  std::copy(t->begin(), t->end(), ostream_iterator<string>(ofs1, " "));
  ofs1 << endl;
  ofs1 << *t << endl;




  // 
  // 
  // std::cout << ('A' > 'c') << std::endl;

  // btree<char> astring;
  // cout << "\nInserting these random chars into the tree...\n";
  // for(int i = 0; i < 10; i++) {
  // 	pair<btree<char>::iterator, bool> result = 
  //   // astring.insert('A');
  //   astring.insert(static_cast<char>(getRandom('A', 'z')));
  //   // astring.insert('c');


  //   std::cout << *(result.first) << std::endl;
  // }
  // // cout << endl << endl;
  // // btree<char> t1(t);
  // astring.printAll();
  // std::cout << *(t.find(8)) << " result" << std::endl;
  // t.printAll();
  std::cout << "\n\n\n\n" << *(result.first) << "\n\n";
  return 0;	
}

