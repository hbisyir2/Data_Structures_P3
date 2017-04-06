#include <string>
#include <cxxtest/TestSuite.h>

#include "dynamic_array_list.h"

#include <cstdlib>
#include <stack>

template class DynamicArrayList<int>;

class ArrayListTests : public CxxTest::TestSuite
{
public:
   void testTODO( void )
   {
     // add tests, same as test_linked_list.h

	   // test constructor, insert, and is empty
	   DynamicArrayList<int> lst;
	   TS_ASSERT(lst.isEmpty() == true);
	   lst.insert(0, 5);
	   TS_ASSERT(lst.isEmpty() == false);

	   // test remove
	   lst.remove(0);
	   TS_ASSERT(lst.isEmpty() == true);

	   // test get entry
	   lst.insert(0, 6);
	   TS_ASSERT(lst.getEntry(0) == 6);

	   // test get entry with more than 1 value
	   lst.insert(1, 5);
	   TS_ASSERT(lst.getEntry(0) == 6);
	   TS_ASSERT(lst.getEntry(1) == 5);

	   // test insert with values already present
	   lst.insert(0, 3);
	   TS_ASSERT(lst.getEntry(0) == 3);
	   TS_ASSERT(lst.getEntry(1) == 6);
	   TS_ASSERT(lst.getEntry(2) == 5);

	   // test remove with multiple entries
	   lst.remove(1);
	   TS_ASSERT(lst.getEntry(0) == 3);
	   TS_ASSERT(lst.getEntry(1) == 5);

	   // test set entry
	   lst.setEntry(0, 1);
	   TS_ASSERT(lst.getEntry(0) == 1);

	   // test clear
	   lst.clear();
	   TS_ASSERT(lst.isEmpty() == true);

	   // test get length
	   TS_ASSERT(lst.getLength() == 0);
	   lst.insert(0, 1);
	   lst.insert(0, 3);
	   TS_ASSERT(lst.getLength() == 2);

	   // test copy constructor
	   DynamicArrayList<int> lst2(lst);
	   TS_ASSERT(lst.getLength() == 2);
	   TS_ASSERT(lst.getEntry(0) == 3);
	   TS_ASSERT(lst.getEntry(1) == 1);

	   // test copy operator
	   DynamicArrayList<int> lst3;
	   lst3 = lst;
	   TS_ASSERT(lst.getLength() == 2);
	   TS_ASSERT(lst.getEntry(0) == 3);
	   TS_ASSERT(lst.getEntry(1) == 1);

	   // test get entry errors
	   lst.clear();
	   TS_ASSERT_THROWS(lst.getEntry(0), std::range_error);
	   lst.insert(0, 8);
	   TS_ASSERT_THROWS(lst.getEntry(1), std::range_error);

	   // test set entry errors
	   TS_ASSERT_THROWS(lst.setEntry(1, 8), std::range_error);

	   // test insert error throws
	   TS_ASSERT_THROWS(lst.insert(2, 8), std::range_error);

	   // test remove error throws
	   TS_ASSERT_THROWS(lst.remove(1), std::range_error);
   }  
};
