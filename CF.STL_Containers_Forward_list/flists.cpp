//
//  flists.cpp
//  CF.STL_Containers_Forward_list
//
//  Created by Alan Sampson on 3/24/21.
//  MARK: - Reference.
//  @see: https://en.cppreference.com/w/cpp/container
//  @see: https://en.cppreference.com/w/cpp/container/forward_list
//

#include <iostream>
#include <iomanip>
#include <string>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <compare>
#include <memory>
#include <type_traits>
#include <forward_list>
#include <span>
#include <array>
#include <vector>
#include <cassert>
#include <cstddef>

using namespace std::literals::string_literals;

//  MARK: - Definitions

//  MARK: - Local Constants.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  MARK: namespace konst
namespace konst {

auto delimiter(char const dc = '-', size_t sl = 80) -> std::string const {
  auto const dlm = std::string(sl, dc);
  return dlm;
}

static
auto const dlm = delimiter();

static
auto const dot = delimiter('.');

} /* namespace konst */

#if (__cplusplus > 201707L)
#endif  /* (__cplusplus > 201707L) */

//  MARK: - Function Prototype.
auto C_forward_list(int argc, const char * argv[]) -> decltype(argc);
auto C_forward_list_deduction_guides(int argc, const char * argv[]) -> decltype(argc);

//  MARK: - Implementation.
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: main()
 */
int main(int argc, const char * argv[]) {
  std::cout << "CF.STL_Containers_Forward_list\n";
  std::cout << "C++ Version: "s << __cplusplus << std::endl;

  std::cout << '\n' << konst::dlm << std::endl;
  C_forward_list(argc, argv);
  C_forward_list_deduction_guides(argc, argv);

  return 0;
}

//  MARK: - C_forward_list
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  MARK: namespace cflc
namespace cflc {

template<typename T>
std::ostream& operator<<(std::ostream & os, const std::forward_list<T> & vlst) {
  os.put('[');
  char comma[3] = { '\0', ' ', '\0' };
  for (const auto & el : vlst) {
    os << comma << el;
    comma[0] = ',';
  }

  return os << ']';
}

} /* namespace cflc */

//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: C_forward_list()
 */
auto C_forward_list(int argc, const char * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;

  /// Member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::forward_list - constructor"s << '\n';
  {
    using namespace cflc;

    // c++11 initializer list syntax:
    std::forward_list<std::string> words1 {"the"s, "frogurt"s, "is"s, "also"s, "cursed"s};
    std::cout << "words1: "s << words1 << '\n';

    // words2 == words1
    std::forward_list<std::string> words2(words1.begin(), words1.end());
    std::cout << "words2: "s << words2 << '\n';

    // words3 == words1
    std::forward_list<std::string> words3(words1);
    std::cout << "words3: "s << words3 << '\n';

    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    std::forward_list<std::string> words4(5, "Mo"s);
    std::cout << "words4: "s << words4 << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - operator="s << '\n';
  {
    auto display_sizes = [](std::forward_list<int> const & nums1,
                            std::forward_list<int> const & nums2,
                            std::forward_list<int> const & nums3) {
        std::cout << "nums1: "s << std::distance(nums1.begin(), nums1.end())
                  << " nums2: "s << std::distance(nums2.begin(), nums2.end())
                  << " nums3: "s << std::distance(nums3.begin(), nums3.end()) << '\n';
    };

    std::forward_list<int> nums1 { 3, 1, 4, 6, 5, 9, };
    std::forward_list<int> nums2;
    std::forward_list<int> nums3;

    std::cout << "Initially:\n";
    display_sizes(nums1, nums2, nums3);

    // copy assignment copies data from nums1 to nums2
    nums2 = nums1;

    std::cout << "After assigment:\n";
    display_sizes(nums1, nums2, nums3);

    // move assignment moves data from nums1 to nums3,
    // modifying both nums1 and nums3
    nums3 = std::move(nums1);

    std::cout << "After move assigment:\n";
    display_sizes(nums1, nums2, nums3);

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - assign"s << '\n';
  {
    std::forward_list<char> characters;

    auto print_forward_list = [&](){
      for (char chr : characters) {
        std::cout << chr << ' ';
      }
      std::cout << '\n';
    };

    characters.assign(5, 'a');
    print_forward_list();

    std::string const extra(6, 'b');
    characters.assign(extra.begin(), extra.end());
    print_forward_list();

    characters.assign({ 'C', '+', '+', '1', '1', });
    print_forward_list();

    std::cout << '\n';
  }

  /// Element access
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - front"s << '\n';
  {
    std::forward_list<char> letters { 'o', 'm', 'g', 'w', 't', 'f' };

    if (!letters.empty()) {
      std::cout << "The first character is '"s << letters.front() << "'.\n"s;
    }

    std::cout << '\n';
  }

  /// Iterators
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - before_begin, cbefore_begin"s << '\n';
  {
    auto prlist = [](auto ln) {
      std::cout << ln << '\n';
    };

    std::forward_list slist {
      "O for a Muse of fire, that would ascend"s,
      "The brightest heaven of invention,"s,
      "A kingdom for a stage, princes to act"s,
      "And monarchs to behold the swelling scene!"s,
    };
    std::for_each(slist.cbegin(), slist.cend(), prlist);
    std::cout << '\n';

    auto toinsert = std::vector {
      "The Life of King Henry the Fifth."s,
      "Act I."s,
      "Prolog.\n"s
    };

    auto it = slist.before_begin();
    std::for_each(toinsert.crbegin(), toinsert.crend(), [&](auto ln) {
      slist.insert_after(it, ln);
    });

    std::for_each(slist.cbegin(), slist.cend(), prlist);
    std::cout << '\n';

    std::cout << '\n';
  }

  /// Iterators
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - begin, cbegin"s << '\n';
  {
    std::forward_list<int> nums { 1, 2, 4, 8, 16, };
    std::forward_list<std::string> fruits {"orange"s, "apple"s, "raspberry"s};
    std::forward_list<char> empty;

    // Print forward_list.
    std::for_each(nums.begin(), nums.end(), [](const int nr) { std::cout << nr << ' '; });
    std::cout << '\n';

    // Sums all integers in the forward_list nums (if any), printing only the result.
    std::cout << "Sum of nums: "s
              << std::accumulate(nums.begin(), nums.end(), 0) << '\n';

    // Prints the first fruit in the forward_list fruits, checking if there is any.
    if (!fruits.empty()) {
      std::cout << "First fruit: "s << *fruits.begin() << '\n';
    }

    if (empty.begin() == empty.end()) {
      std::cout << "forward_list 'empty' is indeed empty.\n"s;
    }

    std::cout << '\n';
  }

  /// Capacity
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - empty"s << '\n';
  {
    std::forward_list<int> numbers;
    std::cout << std::boolalpha;
    std::cout << "Initially, numbers.empty(): "s << numbers.empty() << '\n';

    numbers.push_front(42);
    numbers.push_front(13'317);
    std::cout << "After adding elements, numbers.empty(): "s << numbers.empty() << '\n';
    std::cout << std::noboolalpha;

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - max_size"s << '\n';
  {
    std::forward_list<char> s;
    std::cout << "Maximum size of a 'forward_list' is "s << s.max_size() << "\n"s;

    std::cout << '\n';
  }

  /// Modifiers
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - clear"s << '\n';
  {
    std::forward_list<int> container{ 1, 2, 3, };

    auto print = [](int const & nr) { std::cout << " "s << nr; };

    std::cout << "Before clear:"s;
    std::for_each(container.begin(), container.end(), print);
    std::cout << '\n';

    std::cout << "Clear\n"s;
    container.clear();

    std::cout << "After clear:"s;
    std::for_each(container.begin(), container.end(), print);
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - insert_after"s << '\n';
  {
    using namespace cflc;

    std::forward_list<std::string> words {
      "the"s, "frogurt"s, "is"s, "also"s, "cursed"s,
    };

    std::cout << "words: "s << words << '\n';

    // insert_after (2)
    auto beginIt = words.begin();
    words.insert_after(beginIt, "strawberry"s);
    std::cout << "words: "s << words << '\n';

    // insert_after (3)
    auto anotherIt = beginIt;
    ++anotherIt;
    anotherIt = words.insert_after(anotherIt, 2, "strawberry"s);
    std::cout << "words: "s << words << '\n';

    // insert_after (4)
    std::vector<std::string> V = { "apple"s, "banana"s, "cherry"s, };
    anotherIt = words.insert_after(anotherIt, V.begin(), V.end());
    std::cout << "words: "s << words << '\n';

    // insert_after (5)
    words.insert_after(anotherIt, { "jackfruit"s, "kiwifruit"s, "lime"s, "mango"s, });
    std::cout << "words: "s << words << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - insert_after"s << '\n';
  {
    struct Sum {
      std::string remark;
      int sum;

      Sum(std::string remark, int sum)
        : remark{std::move(remark)}, sum{sum} {}

      void print() const {
        std::cout << remark << " = "s << sum << '\n';
      }
    };

    std::forward_list<Sum> list;

    auto iter = list.before_begin();
    std::string str { "1"s };
    for (int ix { 1 }, sum { 1 }; ix != 10; sum += ix) {
      iter = list.emplace_after(iter, str, sum);
      ++ix;
      str += " + "s + std::to_string(ix);
    }

    for (Sum const & s_ : list) {
      s_.print();
    }

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - erase_after"s << '\n';
  {
    std::forward_list<int> lnrs = { 1, 2, 3, 4, 5, 6, 7, 8, 9, };

//    l.erase( l.begin() ); // ERROR: No function erase

    lnrs.erase_after( lnrs.before_begin() ); // Removes first element

    for( auto n : lnrs ) std::cout << n << " "s;
    std::cout << '\n';

    auto fi = std::next( lnrs.begin() );
    auto la = std::next( fi, 3 );

    lnrs.erase_after( fi, la );

    for( auto n : lnrs ) std::cout << n << " "s;
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - push_front"s << '\n';
  {
    auto prlist = [](auto ln) {
      std::cout << ln << '\n';
    };

    std::forward_list slist {
      "O for a Muse of fire, that would ascend"s,
      "The brightest heaven of invention,"s,
      "A kingdom for a stage, princes to act"s,
      "And monarchs to behold the swelling scene!"s,
    };
    std::for_each(slist.cbegin(), slist.cend(), prlist);
    std::cout << '\n';

    auto toinsert = std::vector {
      "The Life of King Henry the Fifth."s,
      "Act I."s,
      "Prolog.\n"s
    };

    std::for_each(toinsert.crbegin(), toinsert.crend(), [&](auto ln) {
      slist.push_front(ln);
    });
    std::for_each(slist.cbegin(), slist.cend(), prlist);
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - emplace_front"s << '\n';
  {
    auto prlist = [](auto ln) {
      std::cout << ln << '\n';
    };

    std::forward_list slist {
      "O for a Muse of fire, that would ascend"s,
      "The brightest heaven of invention,"s,
      "A kingdom for a stage, princes to act"s,
      "And monarchs to behold the swelling scene!"s,
    };
    std::for_each(slist.cbegin(), slist.cend(), prlist);
    std::cout << '\n';

    auto toinsert = std::vector {
      "The Life of King Henry the Fifth."s,
      "Act I."s,
      "Prolog.\n"s
    };

    std::for_each(toinsert.crbegin(), toinsert.crend(), [&](auto ln) {
      slist.emplace_front(ln);
    });
    std::for_each(slist.cbegin(), slist.cend(), prlist);
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - pop_front"s << '\n';
  {
    auto prlist = [](auto ln) {
      std::cout << ln << '\n';
    };

    std::forward_list slist {
      "The Life of King Henry the Fifth."s,
      "Act I."s,
      "Prolog.\n"s,
      "O for a Muse of fire, that would ascend"s,
      "The brightest heaven of invention,"s,
      "A kingdom for a stage, princes to act"s,
      "And monarchs to behold the swelling scene!"s,
    };
    std::for_each(slist.cbegin(), slist.cend(), prlist);
    std::cout << '\n';

    for (auto ix(0u); ix < 3u; ++ix) {
      slist.pop_front();
    }

    std::for_each(slist.cbegin(), slist.cend(), prlist);
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - resize"s << '\n';
  {
    auto pc = [](auto el) {
      std::cout << el << ' ';
    };

    std::forward_list<int> container = { 1, 2, 3, };
    std::cout << "The forward_list holds: "s;
    std::for_each(container.cbegin(), container.cend(), pc);
    std::cout << '\n';

    container.resize(5);
    std::cout << "After resize up to 5: "s;
    std::for_each(container.cbegin(), container.cend(), pc);
    std::cout << '\n';

    container.resize(2);
    std::cout << "After resize down to 2: "s;
    std::for_each(container.cbegin(), container.cend(), pc);
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - swap"s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> a1 { 1, 2, 3, }, a2 { 4, 5, };

    auto it1 = std::next(a1.begin());
    auto it2 = std::next(a2.begin());

    int & ref1 = a1.front();
    int & ref2 = a2.front();

    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
    a1.swap(a2);
    std::cout << a1 << a2 << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';

    // Note that after swap the iterators and references stay associated with their
    // original elements, e.g. it1 that pointed to an element in 'a1' with value 2
    // still points to the same element, though this element was moved into 'a2'.

    std::cout << '\n';
  }

  /// Operations
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - merge"s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> list1 = { 5, 9, 0, 1, 3, };
    std::forward_list<int> list2 = { 8, 7, 2, 6, 4, };

    list1.sort();
    list2.sort();
    std::cout << "list1:  "s << list1 << '\n';
    std::cout << "list2:  "s << list2 << '\n';
    list1.merge(list2);
    std::cout << "merged: "s << list1 << '\n';

    std::cout << '\n';
  }

  /// Operations
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - splice_after"s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> l1 = { 1, 2, 3, 4, 5, };
    std::forward_list<int> l2 = { 10, 11, 12, };

    std::cout << l1 << '\n';
    std::cout << l2 << '\n';

    l2.splice_after(l2.cbegin(), l1, l1.cbegin(), l1.cend());
    // not equivalent to l2.splice_after(l2.cbegin(), l1);

    std::cout << l1 << '\n';
    std::cout << l2 << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - remove, remove_if"s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> lst = { 1, 100, 2, 3, 10, 1, 11, -1, 12, };
    std::cout << lst << '\n';

    lst.remove(1); // remove both elements equal to 1
    std::cout << lst << '\n';

    lst.remove_if([](int nr){ return nr > 10; }); // remove all elements greater than 10
    std::cout << lst << '\n';

//    for (int n_ : lst) {
//      std::cout << n_ << ' ';
//    }
//    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - reverse"s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> list = { 8, 7, 5, 9, 0, 1, 3, 2, 6, 4, };

    std::cout << "before:     "s << list << '\n';

    list.sort();
    std::cout << "ascending:  "s << list << '\n';

    list.reverse();
    std::cout << "descending: "s << list << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - unique"s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> l_nr = { 1, 2, 2, 3, 3, 2, 1, 1, 2, };

    std::cout << "contents before:         " << l_nr << '\n';
//    for (auto val : l_nr)
//      std::cout << ' ' << val;
//    std::cout << '\n';

    l_nr.unique();
    std::cout << "contents after unique(): " << l_nr << '\n';
//    for (auto val : l_nr)
//      std::cout << ' ' << val;
    std::cout << '\n';

    std::cout << '\n';
  }

  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - sort"s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> list = { 8, 7, 5, 9, 0, 1, 3, 2, 6, 4, };

    std::cout << "before:     "s << list << '\n';

    list.sort();
    std::cout << "ascending:  "s << list << '\n';

    list.sort(std::greater<int>());
    std::cout << "descending: "s << list << '\n';

    std::cout << '\n';
  }

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - std::operator==, etc."s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> alice{ 1, 2, 3, };
    std::forward_list<int> bob{ 7, 8, 9, 10, };
    std::forward_list<int> eve{ 1, 2, 3, };

    std::cout << std::boolalpha;

    // Compare non equal containers
    std::cout << "alice == bob returns "s << (alice == bob) << '\n';
    std::cout << "alice != bob returns "s << (alice != bob) << '\n';
    std::cout << "alice <  bob returns "s << (alice < bob) << '\n';
    std::cout << "alice <= bob returns "s << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns "s << (alice > bob) << '\n';
    std::cout << "alice >= bob returns "s << (alice >= bob) << '\n';

    std::cout << '\n';

    // Compare equal containers
    std::cout << "alice == eve returns " << (alice == eve) << '\n';
    std::cout << "alice != eve returns " << (alice != eve) << '\n';
    std::cout << "alice <  eve returns " << (alice < eve) << '\n';
    std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns " << (alice > eve) << '\n';
    std::cout << "alice >= eve returns " << (alice >= eve) << '\n';

    std::cout << '\n';

#if (__cplusplus > 201707L)
    //  TODO:  add spaceship operator tests
    auto eq = std::is_eq  (alice <=> eve);
    auto ne = std::is_neq (alice <=> eve);
    auto lt = std::is_lt  (alice <=> eve);
    auto le = std::is_lteq(alice <=> eve);
    auto gt = std::is_gt  (alice <=> eve);
    auto ge = std::is_gteq(alice <=> eve);
#endif  /* (__cplusplus > 201707L) */

    std::cout << std::boolalpha;

    std::cout << '\n';
  }

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - std::swap"s << '\n';
  {
    using namespace cflc;

    std::forward_list<int> alice { 1, 2, 3, };
    std::forward_list<int> bob   { 7, 8, 9, 10, };

    // Print state before swap
    std::cout << "before [alice]: "s << alice << '\n';
    std::cout << "       [bob]  : "s << bob << '\n';

    std::cout << "-- SWAP\n";
    std::swap(alice, bob);

    // Print state after swap
    std::cout << "after  [alice]: "s << alice << '\n';
    std::cout << "       [bob]  : "s << bob << '\n';

    std::cout << '\n';
  }

  /// Non-member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::C_forward_list - std::erase, std::erase_if"s << '\n';
  {
    auto print_container = [](std::string_view comment,
                              std::forward_list<char> const & chars) {
      std::cout << comment;
      for (auto cx : chars) {
        std::cout << cx << ' ';
      }
      std::cout << '\n';
    };

    std::forward_list<char> cnt(10);
    std::iota(cnt.begin(), cnt.end(), '0');
    print_container("Init:\n"s, cnt);

    std::erase(cnt, '3');
    print_container("Erase '3':\n"s, cnt);

#if (__cplusplus > 201707L)
  //`TODO:  add C++20 feature tests
    auto erased = std::erase_if(cnt, [](char x) { return (x - '0') % 2 == 0; });
    print_container("Erase all even numbers:\n"s, cnt);
    std::cout << "In all " << erased << " even numbers were erased.\n"s;
#endif  /* (__cplusplus > 201707L) */

    std::cout << '\n';
  }

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;
}

//  MARK: - C_forward_list
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
//  ================================================================================
//  ....+....!....+....!....+....!....+....!....+....!....+....!....+....!....+....!
/*
 *  MARK: C_forward_list()
 */
auto C_forward_list_deduction_guides(int argc, const char * argv[]) -> decltype(argc) {
  std::cout << "In "s << __func__ << std::endl;

  /// Member functions
  // ....+....!....+....!....+....!....+....!....+....!....+....!
  std::cout << konst::dot << '\n';
  std::cout << "std::forward_list - deduction guides"s << '\n';
  {
    std::vector<int> vec = { 1, 2, 3, 4, };

    // uses explicit deduction guide to deduce std::forward_list<int>
    std::forward_list xlst(vec.begin(), vec.end());
    std::for_each(xlst.cbegin(), xlst.cend(), [](auto x_) {
      std::cout << std::setw(4) << x_;
    });
    std::cout << '\n';

    // deduces std::forward_list<std::vector<int>::iterator>
    // first phase of overload resolution for list-initialization selects the candidate
    // synthesized from the initializer-list constructor; second phase is not performed
    // and deduction guide has no effect
    std::forward_list ylst { vec.begin(), vec.end() };
    auto i1 = ylst.front();
    ylst.reverse();
    auto i2 = ylst.front();
    auto acc = std::accumulate(i1, i2, 0, std::plus<>());
    std::cout << std::setw(4) << acc << '\n';

    std::cout << '\n';
  }

  std::cout << std::endl; //  make sure cout is flushed.

  return 0;

}
