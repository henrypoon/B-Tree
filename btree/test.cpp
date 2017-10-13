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
  btree<int> *t = new btree<int>(1);
  pair<btree<int>::iterator, bool> result = t->insert(1);
  result = t->insert(3);



  result = t->insert(5);
  result = t->insert(6);
  result = t->insert(6);

  result = t->insert(7);

  result = t->insert(9);

  result = t->insert(10);

  std::cout << *(t->find(1)) << std::endl;

  // result = t->insert(6);

  // std::cout << &t << std::endl;
  t->printAll();


  // btree<int>::iterator a = t->end();
  //   cout << *a << " fuck you" << endl;

  // btree<int>::reverse_iterator b = t->rbegin();
  //   cout << *b << " fuck me" << endl;

  // for (; riter != t->rend(); ++riter) {
  // }
  // result = t->insert('i');
  // result = t->insert('l');
  // result = t->insert('h');
  // result = t->insert('b');
  // result = t->insert('x');
  // result = t->insert('r');
  // result = t->insert('C');
  
  // btree<char> cp;
  // cp = *t;
  // t->printAll();
  
  // ofstream ofs1("out1");

  // for(btree<char>::reverse_iterator riter = t->rbegin(); riter != t->rend(); ++riter)
    // cout << *riter << endl;
  // ofs1 << endl;
  // ofs1 << *t << endl;

  // btree<char>::reverse_iterator rite = t ->rbegin();
  // cout << *rite << endl;


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
  std::cout << "\n\n\n\n" << result.second << "\n\n";
  return 0;	
}

