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

namespace {

const long kMinInteger = 1000000;
const long kMaxInteger = 100000000;

void initRandom(unsigned long);
long getRandom(long low, long high);
void insertRandomNumbers(btree<long>&, set<long>&, size_t);
bool confirmEverythingMatches(const btree<long>&, const set<long>&);

/**
 * Initialises random number generator.
 * The default argument uses a 'random' seed, but a specific
 * seed can be supplied to reproduce the random sequence for testing.
 **/
void initRandom(unsigned long seed = 0) {
  if (seed == 0) {
    srandom(time(NULL));
  } else {
    srandom(seed);
  }
}

/**
 * Produces a random number in the given range.
 * The random() function provides better quality random numbers
 * than the older rand() function.
 **/
long getRandom(long low, long high) {
  return (low + (random() % ((high - low) + 1)));
}

/**
 * Tries to insert numbers into the specified test container, and every time
 * the insertion succeeds (because the number wasn't previously in the btree),
 * the same number is inserted into the off-the-shelf set
 * class instance so we can later track the correctness of our btree.
 **/
void insertRandomNumbers(btree<long>& testContainer, set<long>& stableContainer, size_t size) {
  cout << "Let's insert up to " << size << " numbers." << endl;
  for (size_t i = 0; i < size; i++) {
    long rndNum = getRandom(kMinInteger, kMaxInteger);
    pair<btree<long>::iterator, bool> result = testContainer.insert(rndNum);
    if (result.second) stableContainer.insert(rndNum);
    if ((i + 1) % 100000 == 0)
      cout << "Inserted some " << (i + 1) << " numbers thus far." << endl;
  }
  cout << endl;
}

/**
 * Confirms that the specified btree and the specified
 * set contain exactly the same numbers.  This does so by
 * considering all numbers that could have been added, and
 * asserting that each of those numbers is either present
 * in or absent from both containers.  If all checks out,
 * we return 0 to signal success; if along the way we see
 * an integer in one container and not the other, then
 * we bail immediately and return one to express failure.
 **/
bool confirmEverythingMatches(const btree<long>& testContainer, const set<long>& stableContainer) {
  cout << "Confirms the btree and the set "
          "contain exactly the same values..." << endl;
  for (long i = kMinInteger; i <= kMaxInteger; i++) {
    bool foundInTree = (testContainer.find(i) != testContainer.end());
    bool foundInSet = (stableContainer.find(i) != stableContainer.end());
    if (foundInTree != foundInSet) {
      cout << "- btree and set don't contain the same data!" << endl;
      cout << "Mismatch at element: " << i << endl;
      return false;
    }
  }
  cout << "- btree checks out just fine." << endl;

  return true;
}





template <typename T>
void assertEqual(const btree<T>& tree, std::vector<T> expectedPrint) {
    auto expected_non_const = expectedPrint;

    // Testing with const btree
    {
        std::stringstream actual, expected;
        actual << tree;

        // Test printing is the same
        {
            for (auto it = expectedPrint.begin(); it != expectedPrint.end(); it++) {
                expected << *it;
                if (it != expectedPrint.end() - 1) {
                    expected << " ";
                }
            }

            if (expected.str() != actual.str()) {
                std::cout << "Expected:\n" << expected.str() << "\nGot:\n" << actual.str() << std::endl;
                assert(expected.str()+' ' == actual.str());
            }
        }

        std::sort(expectedPrint.begin(), expectedPrint.end());

        // Testing constant iterator same
        {
            auto t = tree.cbegin();
            for (auto v = expectedPrint.cbegin(); v != expectedPrint.cend(); ++v) {
                assert(*t == *v);
                ++t;
            }
        }

        // Testing const iterator with postfix increment
        {
            auto t = tree.cbegin();
            for (auto v = expectedPrint.cbegin(); v != expectedPrint.cend(); v++) {
                assert(*t == *v);
                t++;
            }
        }

        // Testing non const iterator (should be const override of begin)
        {
            auto t = tree.begin();
            for (auto v = expectedPrint.cbegin(); v != expectedPrint.cend(); ++v) {
                assert(*t == *v);
                ++t;
            }
        }

        // Testing reverse const iterator
        {
            auto iter = tree.crbegin();
            for (auto v = expectedPrint.crbegin(); v != expectedPrint.crend(); ++v) {
                assert(*iter == *v);
                ++iter;
            }
        }

        // Testing reverse iterator non const (should be rbgein const override)
        {
            auto iter = tree.rbegin();
            for (auto v = expectedPrint.crbegin(); v != expectedPrint.crend(); ++v) {
                assert(*iter == *v);
                ++iter;
            }
        }
    }

    // Testing with non_const btree
    {
        auto tree_nonconst = const_cast<btree<T>&>(tree);
        std::stringstream actual, expected;
        actual << tree_nonconst;

        // Test printing is the same
        {
            for (auto it = expected_non_const.begin(); it != expected_non_const.end(); it++) {
                expected << *it;
                if (it != expected_non_const.end() - 1) {
                    expected << " ";
                }
            }

            if (expected.str() != actual.str()) {
                std::cout << "Expected:\n" << expected.str() << "\nGot:\n" << actual.str()<< std::endl;;
                assert(expected.str()+' ' == actual.str());
            }
        }

        std::sort(expected_non_const.begin(), expected_non_const.end());

        // Testing constant iterator same
        {
            auto t = tree_nonconst.cbegin();
            for (auto v = expected_non_const.cbegin(); v != expected_non_const.cend(); ++v) {
                assert(*t == *v);
                ++t;
            }
        }

        // Testing const iterator with postfix increment
        {
            auto t = tree_nonconst.cbegin();
            for (auto v = expected_non_const.cbegin(); v != expected_non_const.cend(); v++) {
                assert(*t == *v);
                t++;
            }
        }

        // Testing non const iterator
        {
            auto t = tree_nonconst.begin();
            for (auto v = expected_non_const.cbegin(); v != expected_non_const.cend(); ++v) {
                assert(*t == *v);
                ++t;
            }
        }

        // Testing reverse const iterator
        {
            auto iter = tree_nonconst.crbegin();
            for (auto v = expected_non_const.crbegin(); v != expected_non_const.crend(); ++v) {
                assert(*iter == *v);
                ++iter;
            }
        }

        // Testing reverse iterator non const
        {
            auto iter = tree_nonconst.rbegin();
            for (auto v = expected_non_const.crbegin(); v != expected_non_const.crend(); ++v) {
                assert(*iter == *v);
                ++iter;
            }
        }
    }
}



}  // namespace close


/**
 * Codes for testing various bits and pieces. Most of the code is commented out
 * you should uncomment it as appropriate.
 **/
int main(void) {
  // initialise random number generator with 'random' seed
  initRandom();

  // insert lots of random numbers and compare with a known correct container
  btree<long> testContainer(99);
  set<long> stableContainer;

  insertRandomNumbers(testContainer, stableContainer, 1000000);
  btree<long> btcpy = testContainer;
  confirmEverythingMatches(btcpy, stableContainer);



  // this next portion was something I used to sort a bunch of chars
  // this was what I used to debug my iterator and made it work
 	btree<char> astring;

	cout << "\nInserting these random chars into the tree...\n";
	for(int i = 0; i < 10; i++) {
	pair<btree<char>::iterator, bool> result =
    astring.insert(static_cast<char>(getRandom('A', 'z')));
    cout << *result.first;
	}
	cout << endl << endl;

	for(btree<char>::iterator iter = astring.begin(); iter != astring.end(); ++iter)
	cout << *iter;
	cout << endl;

  // const iterator test
  const btree<char>& refstring = astring;
    btree<char>::const_iterator iter;
	cout << "Voila!  Sorted!" << endl;
	for(iter = refstring.begin(); iter != refstring.end(); ++iter) {
		astring.insert(static_cast<char>(getRandom('A', 'z')));

		cout << *(iter) << " ";
	}

	for(btree<char>::const_iterator iter = refstring.begin(); !(iter == refstring.end()); ++iter)
		cout << *iter;
	cout << endl;

  // a full-scale string test of the tree using iterators
  btree<string> *strTable = new btree<string>(40);

  ifstream wordFile("twl.txt");
  if (!wordFile)
    return 1;  // file couldn't be opened for some reason, abort...

  while (wordFile.good()) {
    string word;
    getline(wordFile, word);
    strTable->insert(word);
  }
  wordFile.close();

  cout << "twl.txt sorted by our wonderful tree..." << endl;
  // Such beautiful code with iterators...
  for(btree<string>::const_iterator iter = strTable->begin(); iter != strTable->end(); ++iter)
    cout << *iter << endl;

  // reverse iterator
  btree<string>::reverse_iterator riter = strTable->rbegin();
  btree<string>::const_iterator citer = strTable->begin();

  if (*citer != *riter) {
    cout << "success!" << endl;
  }

  // try to create a copy
  btree<string> btcpy2;

  btcpy2 = *strTable;

  // ofstream ofs1("out1");
  // ofstream ofs2("out2");

  // copy(strTable->begin(), strTable->end(), ostream_iterator<string>(ofs1, " "));
  // ofs1 << endl;
  // ofs1 << *strTable << endl;

  delete strTable;

  // copy(btcpy2.begin(), btcpy2.end(), ostream_iterator<string>(ofs2, " "));
  // ofs2 << endl;
  // ofs2 << btcpy2 << endl;

  // ofs1.close();
  // ofs2.close();







  std::cout << "Testing basic insertion" << std::endl;
    {
        btree<int> testContainer(4);
        auto pair = testContainer.insert(5);
        assert(*(pair.first) == 5);
        assert(pair.second == true);
    }

    std::cout << "Testing repeated insertion fails" << std::endl;
    {
        btree<int> testContainer(4);
        auto pair = testContainer.insert(5);
        auto second_pair = testContainer.insert(5);
        assert(pair.first == second_pair.first);
        assert(second_pair.second == false);
    }

    std::cout << "Testing insertion creates child" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        auto pair = testContainer.insert(0);
        assert(*(pair.first) == 0);
        assert(pair.second == true);
    }

    std::cout << "Testing ++ on iterator returned by insert" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        auto pair = testContainer.insert(0);
        auto it = pair.first;
        assert(*it == 0);
        ++it;
        assert(*it == 1);
    }

    std::cout << "Testing print" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        assertEqual(testContainer, {1, 3, 5, 7});
    }

    std::cout << "Testing print on tree with children" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        auto pair = testContainer.insert(2);
        assert(*(pair.first) == 2);
        assert(pair.second == true);
        auto second_pair = testContainer.insert(2);
        assert(pair.first == second_pair.first);
        assert(second_pair.second == false);

        assertEqual(testContainer, {1, 3, 5, 7, 0, 2});
    }

    std::cout << "Testing const print" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        const auto copy = testContainer;
        assertEqual(testContainer, {1, 3, 5, 7, 0, 2});
        assertEqual(copy, {1, 3, 5, 7, 0, 2});
    }

    std::cout << "Testing print on empty tree" << std::endl;
    {
        btree<int> testContainer(4);
        assertEqual(testContainer, {});
    }

    std::cout << "Testing copy constructor" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        auto copy = testContainer;
        assertEqual(testContainer, {1, 3, 5, 7, 0, 2});
        assertEqual(copy, {1, 3, 5, 7, 0, 2});

        testContainer.insert(4);
        assertEqual(testContainer, {1, 3, 5, 7, 0, 2, 4});
        assertEqual(copy, {1, 3, 5, 7, 0, 2});
    }

    std::cout << "Testing copy assignment" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        btree<int> copy;
        copy = testContainer;
        assertEqual(testContainer, {1, 3, 5, 7, 0, 2});
        assertEqual(copy, {1, 3, 5, 7, 0, 2});

        testContainer.insert(4);
        assertEqual(testContainer, {1, 3, 5, 7, 0, 2, 4});
        assertEqual(copy, {1, 3, 5, 7, 0, 2});

        // Copying when already have data
        copy = testContainer;
        assertEqual(testContainer, {1, 3, 5, 7, 0, 2, 4});
        assertEqual(copy, {1, 3, 5, 7, 0, 2, 4});
    }

    std::cout << "Testing move constructor" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        auto copy = std::move(testContainer);
        assertEqual(testContainer, {});
        assertEqual(copy, {1, 3, 5, 7, 0, 2});

        // Should still function
        testContainer.insert(100);
        assertEqual(copy, {1, 3, 5, 7, 0, 2});
        assertEqual(testContainer, {100});
    }

    std::cout << "Testing move assignment" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        btree<int> copy;
        copy = std::move(testContainer);
        assertEqual(testContainer, {});
        assertEqual(copy, {1, 3, 5, 7, 0, 2});

        // Should still function
        testContainer.insert(100);
        assertEqual(copy, {1, 3, 5, 7, 0, 2});
        assertEqual(testContainer, {100});

        // Moving when already have data
        testContainer = copy;
        assertEqual(testContainer, {1, 3, 5, 7, 0, 2});
        assertEqual(copy, {1, 3, 5, 7, 0, 2});
        testContainer.insert(9);
        assertEqual(testContainer, {1, 3, 5, 7, 0, 2, 9});

        copy = std::move(testContainer);
        assertEqual(testContainer, {});
        assertEqual(copy, {1, 3, 5, 7, 0, 2, 9});

        // Should still function
        testContainer.insert(100);
        assertEqual(copy, {1, 3, 5, 7, 0, 2, 9});
        assertEqual(testContainer, {100});
    }

    std::cout << "Testing find non const" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        auto iter = testContainer.find(1);
        assert(*iter == 1);
        ++iter;
        assert(*iter == 2);

        iter = testContainer.find(0);
        assert(*iter == 0);
        ++iter;
        assert(*iter == 1);

        iter = testContainer.find(100);
        assert(iter == testContainer.end());

        typename btree<int>::const_iterator const_iter = testContainer.find(100);
        assert(const_iter == testContainer.end());
        assert(const_iter == testContainer.cend());
    }

    std::cout << "Testing find const" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        const auto const_tree = testContainer;
        auto iter = const_tree.find(1);
        assert(*iter == 1);
        ++iter;
        assert(*iter == 2);

        iter = const_tree.find(0);
        assert(*iter == 0);
        ++iter;
        assert(*iter == 1);

        iter = const_tree.find(100);
        assert(iter == const_tree.end());
        assert(iter == const_tree.cend());

        typename btree<int>::const_iterator const_iter = testContainer.find(100);
        assert(const_iter == testContainer.end());
        assert(const_iter == testContainer.cend());;
    }

    std::cout << "Testing for each loop compatability" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        std::vector<int> v{0, 1, 2, 3, 5, 7};
        auto iter = v.cbegin();
        for (auto elem : testContainer) {
            assert(elem == *iter);
            ++iter;
        }
    }

    std::cout << "Testing increasing each element by 1" << std::endl;
    {
        btree<int> testContainer(4);
        testContainer.insert(1);
        testContainer.insert(3);
        testContainer.insert(5);
        testContainer.insert(7);
        testContainer.insert(0);
        testContainer.insert(2);

        assertEqual(testContainer, {1, 3, 5, 7, 0, 2});

        for (auto it = testContainer.begin(); it != testContainer.end(); ++it) {
            (*it)++;
        }

        assertEqual(testContainer, {2, 4, 6, 8, 1, 3});
    }

    std::cout << "All tests passed, you are awesome!" << std::endl;



  return 0;
}
