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


/**
 * Codes for testing various bits and pieces. Most of the code is commented out
 * you should uncomment it as appropriate.
 **/
int main(void) {
  // initialise random number generator with 'random' seed

  // insert lots of random numbers and compare with a known correct container
  btree<long> t(99);

  return 0;	
}

