#include <ATen/core/List.h>
#include <gtest/gtest.h>

using namespace c10;

static_assert(std::is_same<IValue, typename ListPtr<string>::internal_value_type_test_only>::value, "If this fails, then it seems we changed ListPtr<string> to store it as std::vector<string> instead of std::vector<IValue>. We need to change ListTest_IValueBasedList test cases to use a different type that is still based on IValue.");

TEST(ListTest_IValueBasedList, givenEmptyList_whenCallingEmpty_thenReturnsTrue) {
    ListPtr<string> list = make_list<string>();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest_IValueBasedList, givenNonemptyList_whenCallingEmpty_thenReturnsFalse) {
    ListPtr<string> list = make_list<string>({"3"});
    EXPECT_FALSE(list.empty());
}

TEST(ListTest_IValueBasedList, givenEmptyList_whenCallingSize_thenReturnsZero) {
    ListPtr<string> list = make_list<string>();
    EXPECT_EQ(0, list.size());
}

TEST(ListTest_IValueBasedList, givenNonemptyList_whenCallingSize_thenReturnsNumberOfElements) {
    ListPtr<string> list = make_list<string>({"3", "4"});
    EXPECT_EQ(2, list.size());
}

TEST(ListTest_IValueBasedList, givenNonemptyList_whenCallingClear_thenIsEmpty) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  list.clear();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest_IValueBasedList, whenCallingGetWithExistingPosition_thenReturnsElement) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  EXPECT_EQ("3", list.get(0));
  EXPECT_EQ("4", list.get(1));
}

TEST(ListTest_IValueBasedList, whenCallingGetWithNonExistingPosition_thenThrowsException) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  EXPECT_THROW(list.get(2), std::out_of_range);
}

TEST(ListTest_IValueBasedList, whenCallingCopyingSetWithExistingPosition_thenChangesElement) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  string value = "5";
  list.set(1, value);
  EXPECT_EQ("3", list.get(0));
  EXPECT_EQ("5", list.get(1));
}

TEST(ListTest_IValueBasedList, whenCallingMovingSetWithExistingPosition_thenChangesElement) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  string value = "5";
  list.set(1, std::move(value));
  EXPECT_EQ("3", list.get(0));
  EXPECT_EQ("5", list.get(1));
}

TEST(ListTest_IValueBasedList, whenCallingCopyingSetWithNonExistingPosition_thenThrowsException) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  string value = "5";
  EXPECT_THROW(list.set(2, value), std::out_of_range);
}

TEST(ListTest_IValueBasedList, whenCallingMovingSetWithNonExistingPosition_thenThrowsException) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  string value = "5";
  EXPECT_THROW(list.set(2, std::move(value)), std::out_of_range);
}

TEST(ListTest_IValueBasedList, whenCallingAccessOperatorWithExistingPosition_thenReturnsElement) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  EXPECT_EQ("3", list[0]);
  EXPECT_EQ("4", list[1]);
}

TEST(ListTest_IValueBasedList, whenCallingAccessOperatorWithNonExistingPosition_thenThrowsException) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  EXPECT_THROW(list[2], std::out_of_range);
}

TEST(ListTest_IValueBasedList, whenCallingInsertOnConstIteratorWithLValue_thenInsertsElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  string v = "5";
  list.insert(list.cbegin() + 2, v);
  EXPECT_EQ(4, list.size());
  EXPECT_EQ("5", list[2]);
}

TEST(ListTest_IValueBasedList, whenCallingInsertOnMutableIteratorWithLValue_thenInsertsElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  string v = "5";
  list.insert(list.begin() + 2, v);
  EXPECT_EQ(4, list.size());
  EXPECT_EQ("5", list[2]);
}

TEST(ListTest_IValueBasedList, whenCallingInsertOnConstIteratorWithRValue_thenInsertsElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  string v = "5";
  list.insert(list.cbegin() + 2, std::move(v));
  EXPECT_EQ(4, list.size());
  EXPECT_EQ("5", list[2]);
}

TEST(ListTest_IValueBasedList, whenCallingInsertOnMutableIteratorWithRValue_thenInsertsElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  string v = "5";
  list.insert(list.begin() + 2, std::move(v));
  EXPECT_EQ(4, list.size());
  EXPECT_EQ("5", list[2]);
}

TEST(ListTest_IValueBasedList, whenCallingInsertWithLValue_thenReturnsIteratorToNewElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  string v = "5";
  ListPtr<string>::iterator result = list.insert(list.cbegin() + 2, v);
  EXPECT_EQ(list.begin() + 2, result);
}

TEST(ListTest_IValueBasedList, whenCallingInsertWithRValue_thenReturnsIteratorToNewElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  string v = "5";
  ListPtr<string>::iterator result = list.insert(list.cbegin() + 2, std::move(v));
  EXPECT_EQ(list.begin() + 2, result);
}

TEST(ListTest_IValueBasedList, whenCallingEmplaceWithLValue_thenInsertsElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  string v = "5";
  list.emplace(list.begin() + 2, v);
  EXPECT_EQ(4, list.size());
  EXPECT_EQ("5", list[2]);
}

TEST(ListTest_IValueBasedList, whenCallingEmplaceWithRValue_thenInsertsElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  string v = "5";
  list.emplace(list.begin() + 2, std::move(v));
  EXPECT_EQ(4, list.size());
  EXPECT_EQ("5", list[2]);
}

TEST(ListTest_IValueBasedList, whenCallingEmplaceWithConstructorArg_thenInsertsElement) {
  ListPtr<string> list = make_list<string>({"3", "4", "6"});
  list.emplace(list.begin() + 2, "5"); // const char* is a constructor arg to std::string
  EXPECT_EQ(4, list.size());
  EXPECT_EQ("5", list[2]);
}

TEST(ListTest_IValueBasedList, whenCallingPushBackWithLValue_ThenInsertsElement) {
  ListPtr<string> list = make_list<string>();
  string v = "5";
  list.push_back(v);
  EXPECT_EQ(1, list.size());
  EXPECT_EQ("5", list[0]);
}

TEST(ListTest_IValueBasedList, whenCallingPushBackWithRValue_ThenInsertsElement) {
  ListPtr<string> list = make_list<string>();
  string v = "5";
  list.push_back(std::move(v));
  EXPECT_EQ(1, list.size());
  EXPECT_EQ("5", list[0]);
}

TEST(ListTest_IValueBasedList, whenCallingEmplaceBackWithLValue_ThenInsertsElement) {
  ListPtr<string> list = make_list<string>();
  string v = "5";
  list.emplace_back(v);
  EXPECT_EQ(1, list.size());
  EXPECT_EQ("5", list[0]);
}

TEST(ListTest_IValueBasedList, whenCallingEmplaceBackWithRValue_ThenInsertsElement) {
  ListPtr<string> list = make_list<string>();
  string v = "5";
  list.emplace_back(std::move(v));
  EXPECT_EQ(1, list.size());
  EXPECT_EQ("5", list[0]);
}

TEST(ListTest_IValueBasedList, whenCallingEmplaceBackWithConstructorArg_ThenInsertsElement) {
  ListPtr<string> list = make_list<string>();
  list.emplace_back("5");  // const char* is a constructor arg to std::string
  EXPECT_EQ(1, list.size());
  EXPECT_EQ("5", list[0]);
}

TEST(ListTest_IValueBasedList, givenEmptyList_whenIterating_thenBeginIsEnd) {
  ListPtr<string> list = make_list<string>();
  const ListPtr<string> clist = make_list<string>();
  EXPECT_EQ(list.begin(), list.end());
  EXPECT_EQ(list.cbegin(), list.cend());
  EXPECT_EQ(clist.begin(), clist.end());
  EXPECT_EQ(clist.cbegin(), clist.cend());
}

TEST(ListTest_IValueBasedList, givenMutableList_whenIterating_thenFindsElements) {
  ListPtr<string> list = make_list<string>({"3", "5"});
  bool found_first = false;
  bool found_second = false;
  for (ListPtr<string>::iterator iter = list.begin(); iter != list.end(); ++iter) {
    if (*iter == "3") {
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (*iter == "5") {
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(ListTest_IValueBasedList, givenMutableList_whenIteratingWithForeach_thenFindsElements) {
  ListPtr<string> list = make_list<string>({"3", "5"});
  bool found_first = false;
  bool found_second = false;
  for (const auto& elem : list) {
    if (elem == "3") {
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (elem == "5") {
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(ListTest_IValueBasedList, givenConstList_whenIterating_thenFindsElements) {
  const ListPtr<string> list = make_list<string>({"3", "5"});
  bool found_first = false;
  bool found_second = false;
  for (ListPtr<string>::const_iterator iter = list.begin(); iter != list.end(); ++iter) {
    if (*iter == "3") {
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (*iter == "5") {
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(ListTest_IValueBasedList, givenConstList_whenIteratingWithForeach_thenFindsElements) {
  const ListPtr<string> list = make_list<string>({"3", "5"});
  bool found_first = false;
  bool found_second = false;
  for (const auto& elem : list) {
    if (elem == "3") {
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (elem == "5") {
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(ListTest_IValueBasedList, givenOneElementList_whenErasing_thenListIsEmpty) {
  ListPtr<string> list = make_list<string>({"3"});
  list.erase(list.cbegin());
  EXPECT_TRUE(list.empty());
}

TEST(ListTest_IValueBasedList, givenList_whenErasing_thenReturnsIterator) {
  ListPtr<string> list = make_list<string>({"1", "2", "3"});
  ListPtr<string>::iterator iter = list.erase(list.begin() + 1);
  EXPECT_EQ(list.begin() + 1, iter);
}

TEST(ListTest_IValueBasedList, givenList_whenErasingFullRange_thenIsEmpty) {
  ListPtr<string> list = make_list<string>({"1", "2", "3"});
  list.erase(list.cbegin(), list.cend());
  EXPECT_TRUE(list.empty());
}

TEST(ListTest_IValueBasedList, whenCallingReserve_thenDoesntCrash) {
  ListPtr<string> list = make_list<string>();
  list.reserve(100);
}

TEST(ListTest_IValueBasedList, whenCopyConstructingList_thenAreEqual) {
  ListPtr<string> list1 = make_list<string>({"3", "4"});

  ListPtr<string> list2(list1);

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ("3", list2.get(0));
  EXPECT_EQ("4", list2.get(1));
}

TEST(ListTest_IValueBasedList, whenCopyAssigningList_thenAreEqual) {
  ListPtr<string> list1 = make_list<string>({"3", "4"});

  ListPtr<string> list2 = make_list<string>();
  list2 = list1;

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ("3", list2.get(0));
  EXPECT_EQ("4", list2.get(1));
}

TEST(ListTest_IValueBasedList, whenCopyingList_thenAreEqual) {
  ListPtr<string> list1 = make_list<string>({"3", "4"});

  ListPtr<string> list2 = list1.copy();

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ("3", list2.get(0));
  EXPECT_EQ("4", list2.get(1));
}

TEST(ListTest_IValueBasedList, whenMoveConstructingList_thenNewIsCorrect) {
  ListPtr<string> list1 = make_list<string>({"3", "4"});

  ListPtr<string> list2(std::move(list1));

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ("3", list2.get(0));
  EXPECT_EQ("4", list2.get(1));
}

TEST(ListTest_IValueBasedList, whenMoveAssigningList_thenNewIsCorrect) {
  ListPtr<string> list1 = make_list<string>({"3", "4"});

  ListPtr<string> list2 = make_list<string>();
  list2 = std::move(list1);

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ("3", list2.get(0));
  EXPECT_EQ("4", list2.get(1));
}

TEST(ListTest_IValueBasedList, whenMoveConstructingList_thenOldIsEmpty) {
  ListPtr<string> list1 = make_list<string>({"3", "4"});

  ListPtr<string> list2(std::move(list1));
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest_IValueBasedList, whenMoveAssigningList_thenOldIsEmpty) {
  ListPtr<string> list1 = make_list<string>({"3", "4"});

  ListPtr<string> list2 = make_list<string>();
  list2 = std::move(list1);
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenAssigningToConstIterator_thenWorks) {
  ListPtr<string> list = make_list<string>({"3"});
  ListPtr<string>::iterator iter = list.begin();
  ListPtr<string>::const_iterator const_iter = iter;
  EXPECT_EQ("3", *const_iter);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenPostfixIncrementing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::iterator iter1 = list.begin();
  ListPtr<string>::iterator iter2 = iter1++;
  EXPECT_NE("3", *iter1);
  EXPECT_EQ("3", *iter2);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenPostfixIncrementing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::const_iterator iter1 = list.cbegin();
  ListPtr<string>::const_iterator iter2 = iter1++;
  EXPECT_NE("3", *iter1);
  EXPECT_EQ("3", *iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenPrefixIncrementing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::iterator iter1 = list.begin();
  ListPtr<string>::iterator iter2 = ++iter1;
  EXPECT_NE("3", *iter1);
  EXPECT_NE("3", *iter2);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenPrefixIncrementing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::const_iterator iter1 = list.cbegin();
  ListPtr<string>::const_iterator iter2 = ++iter1;
  EXPECT_NE("3", *iter1);
  EXPECT_NE("3", *iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenPostfixDecrementing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::iterator iter1 = list.end() - 1;
  ListPtr<string>::iterator iter2 = iter1--;
  EXPECT_NE("4", *iter1);
  EXPECT_EQ("4", *iter2);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenPostfixDecrementing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::const_iterator iter1 = list.cend() - 1;
  ListPtr<string>::const_iterator iter2 = iter1--;
  EXPECT_NE("4", *iter1);
  EXPECT_EQ("4", *iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenPrefixDecrementing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::iterator iter1 = list.end() - 1;
  ListPtr<string>::iterator iter2 = --iter1;
  EXPECT_NE("4", *iter1);
  EXPECT_NE("4", *iter2);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenPrefixDecrementing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::const_iterator iter1 = list.cend() - 1;
  ListPtr<string>::const_iterator iter2 = --iter1;
  EXPECT_NE("4", *iter1);
  EXPECT_NE("4", *iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenIncreasing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<string> list = make_list<string>({"3", "4", "5"});

  ListPtr<string>::iterator iter1 = list.begin();
  ListPtr<string>::iterator iter2 = iter1 += 2;
  EXPECT_EQ("5", *iter1);
  EXPECT_EQ("5", *iter2);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenIncreasing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<string> list = make_list<string>({"3", "4", "5"});

  ListPtr<string>::const_iterator iter1 = list.cbegin();
  ListPtr<string>::const_iterator iter2 = iter1 += 2;
  EXPECT_EQ("5", *iter1);
  EXPECT_EQ("5", *iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenDecreasing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<string> list = make_list<string>({"3", "4", "5"});

  ListPtr<string>::iterator iter1 = list.end();
  ListPtr<string>::iterator iter2 = iter1 -= 2;
  EXPECT_EQ("4", *iter1);
  EXPECT_EQ("4", *iter2);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenDecreasing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<string> list = make_list<string>({"3", "4", "5"});

  ListPtr<string>::const_iterator iter1 = list.cend();
  ListPtr<string>::const_iterator iter2 = iter1 -= 2;
  EXPECT_EQ("4", *iter1);
  EXPECT_EQ("4", *iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenAdding_thenReturnsNewIterator) {
  ListPtr<string> list = make_list<string>({"3", "4", "5"});

  ListPtr<string>::iterator iter1 = list.begin();
  ListPtr<string>::iterator iter2 = iter1 + 2;
  EXPECT_EQ("3", *iter1);
  EXPECT_EQ("5", *iter2);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenAdding_thenReturnsNewIterator) {
  ListPtr<string> list = make_list<string>({"3", "4", "5"});

  ListPtr<string>::const_iterator iter1 = list.cbegin();
  ListPtr<string>::const_iterator iter2 = iter1 + 2;
  EXPECT_EQ("3", *iter1);
  EXPECT_EQ("5", *iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenSubtracting_thenReturnsNewIterator) {
  ListPtr<string> list = make_list<string>({"3", "4", "5"});

  ListPtr<string>::iterator iter1 = list.end() - 1;
  ListPtr<string>::iterator iter2 = iter1 - 2;
  EXPECT_EQ("5", *iter1);
  EXPECT_EQ("3", *iter2);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenSubtracting_thenReturnsNewIterator) {
  ListPtr<string> list = make_list<string>({"3", "4", "5"});

  ListPtr<string>::const_iterator iter1 = list.cend() - 1;
  ListPtr<string>::const_iterator iter2 = iter1 - 2;
  EXPECT_EQ("5", *iter1);
  EXPECT_EQ("3", *iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenCalculatingDifference_thenReturnsCorrectNumber) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  EXPECT_EQ(2, list.end() - list.begin());
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenCalculatingDifference_thenReturnsCorrectNumber) {
  ListPtr<string> list = make_list<string>({"3", "4"});
  EXPECT_EQ(2, list.cend() - list.cbegin());
}

TEST(ListTest_IValueBasedList, givenEqualMutableIterators_thenAreEqual) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::iterator iter1 = list.begin();
  ListPtr<string>::iterator iter2 = list.begin();
  EXPECT_TRUE(iter1 == iter2);
  EXPECT_FALSE(iter1 != iter2);
}

TEST(ListTest_IValueBasedList, givenDifferentMutableIterators_thenAreNotEqual) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::iterator iter1 = list.begin();
  ListPtr<string>::iterator iter2 = list.begin();
  iter2++;

  EXPECT_FALSE(iter1 == iter2);
  EXPECT_TRUE(iter1 != iter2);
}

TEST(ListTest_IValueBasedList, givenEqualConstIterators_thenAreEqual) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::const_iterator iter1 = list.cbegin();
  ListPtr<string>::const_iterator iter2 = list.cbegin();
  EXPECT_TRUE(iter1 == iter2);
  EXPECT_FALSE(iter1 != iter2);
}

TEST(ListTest_IValueBasedList, givenDifferentConstIterators_thenAreNotEqual) {
  ListPtr<string> list = make_list<string>({"3", "4"});

  ListPtr<string>::const_iterator iter1 = list.cbegin();
  ListPtr<string>::const_iterator iter2 = list.cbegin();
  iter2++;

  EXPECT_FALSE(iter1 == iter2);
  EXPECT_TRUE(iter1 != iter2);
}

TEST(ListTest_IValueBasedList, givenMutableIterator_whenDereferencing_thenPointsToCorrectElement) {
  ListPtr<string> list = make_list<string>({"3"});

  ListPtr<string>::iterator iter = list.begin();
  EXPECT_EQ("3", *iter);
}

TEST(ListTest_IValueBasedList, givenConstIterator_whenDereferencing_thenPointsToCorrectElement) {
  ListPtr<string> list = make_list<string>({"3"});

  ListPtr<string>::const_iterator iter = list.cbegin();
  EXPECT_EQ("3", *iter);
}

TEST(ListTest_IValueBasedList, givenOneElementList_whenCallingPopBack_thenIsEmpty) {
  ListPtr<string> list = make_list<string>({"3"});
  list.pop_back();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest_IValueBasedList, givenEmptyList_whenCallingResize_thenResizesAndSetsEmptyValue) {
  ListPtr<string> list = make_list<string>();
  list.resize(2);
  EXPECT_EQ(2, list.size());
  EXPECT_EQ("", list[0]);
  EXPECT_EQ("", list[1]);
}

TEST(ListTest_IValueBasedList, givenEmptyList_whenCallingResizeWithValue_thenResizesAndSetsValue) {
  ListPtr<string> list = make_list<string>();
  list.resize(2, "value");
  EXPECT_EQ(2, list.size());
  EXPECT_EQ("value", list[0]);
  EXPECT_EQ("value", list[1]);
}

TEST(ListTest_IValueBasedList, isReferenceType) {
  ListPtr<string> list1 = make_list<string>();
  ListPtr<string> list2(list1);
  ListPtr<string> list3 = make_list<string>();
  list3 = list1;

  list1.push_back("three");
  EXPECT_EQ(1, list1.size());
  EXPECT_EQ(1, list2.size());
  EXPECT_EQ(1, list3.size());
}

TEST(ListTest_IValueBasedList, copyHasSeparateStorage) {
  ListPtr<string> list1 = make_list<string>();
  ListPtr<string> list2(list1.copy());
  ListPtr<string> list3 = make_list<string>();
  list3 = list1.copy();

  list1.push_back("three");
  EXPECT_EQ(1, list1.size());
  EXPECT_EQ(0, list2.size());
  EXPECT_EQ(0, list3.size());
}


static_assert(std::is_same<int64_t, typename ListPtr<int64_t>::internal_value_type_test_only>::value, "If this fails, then it seems we changed ListPtr<int64_t> to store it as std::vector<IValue> instead of std::vector<int64_t>. We need to change ListTest_NonIValueBasedList test cases to use a different type that is still not based on IValue.");

TEST(ListTest_NonIValueBasedList, givenEmptyList_whenCallingEmpty_thenReturnsTrue) {
    ListPtr<int64_t> list = make_list<int64_t>();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest_NonIValueBasedList, givenNonemptyList_whenCallingEmpty_thenReturnsFalse) {
    ListPtr<int64_t> list = make_list<int64_t>({3});
    EXPECT_FALSE(list.empty());
}

TEST(ListTest_NonIValueBasedList, givenEmptyList_whenCallingSize_thenReturnsZero) {
    ListPtr<int64_t> list = make_list<int64_t>();
    EXPECT_EQ(0, list.size());
}

TEST(ListTest_NonIValueBasedList, givenNonemptyList_whenCallingSize_thenReturnsNumberOfElements) {
    ListPtr<int64_t> list = make_list<int64_t>({3, 4});
    EXPECT_EQ(2, list.size());
}

TEST(ListTest_NonIValueBasedList, givenNonemptyList_whenCallingClear_thenIsEmpty) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  list.clear();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest_NonIValueBasedList, whenCallingGetWithExistingPosition_thenReturnsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  EXPECT_EQ(3, list.get(0));
  EXPECT_EQ(4, list.get(1));
}

TEST(ListTest_NonIValueBasedList, whenCallingGetWithNonExistingPosition_thenThrowsException) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  EXPECT_THROW(list.get(2), std::out_of_range);
}

TEST(ListTest_NonIValueBasedList, whenCallingCopyingSetWithExistingPosition_thenChangesElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  int64_t value = 5;
  list.set(1, value);
  EXPECT_EQ(3, list.get(0));
  EXPECT_EQ(5, list.get(1));
}

TEST(ListTest_NonIValueBasedList, whenCallingMovingSetWithExistingPosition_thenChangesElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  int64_t value = 5;
  list.set(1, std::move(value));
  EXPECT_EQ(3, list.get(0));
  EXPECT_EQ(5, list.get(1));
}

TEST(ListTest_NonIValueBasedList, whenCallingCopyingSetWithNonExistingPosition_thenThrowsException) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  int64_t value = 5;
  EXPECT_THROW(list.set(2, value), std::out_of_range);
}

TEST(ListTest_NonIValueBasedList, whenCallingMovingSetWithNonExistingPosition_thenThrowsException) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  int64_t value = 5;
  EXPECT_THROW(list.set(2, std::move(value)), std::out_of_range);
}

TEST(ListTest_NonIValueBasedList, whenCallingAccessOperatorWithExistingPosition_thenReturnsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  EXPECT_EQ(3, list[0]);
  EXPECT_EQ(4, list[1]);
}

TEST(ListTest_NonIValueBasedList, whenCallingAccessOperatorWithNonExistingPosition_thenThrowsException) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  EXPECT_THROW(list[2], std::out_of_range);
}

TEST(ListTest_NonIValueBasedList, whenCallingInsertOnConstIteratorWithLValue_thenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  int64_t v = 5;
  list.insert(list.cbegin() + 2, v);
  EXPECT_EQ(4, list.size());
  EXPECT_EQ(5, list[2]);
}

TEST(ListTest_NonIValueBasedList, whenCallingInsertOnMutableIteratorWithLValue_thenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  int64_t v = 5;
  list.insert(list.begin() + 2, v);
  EXPECT_EQ(4, list.size());
  EXPECT_EQ(5, list[2]);
}

TEST(ListTest_NonIValueBasedList, whenCallingInsertOnConstIteratorWithRValue_thenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  int64_t v = 5;
  list.insert(list.cbegin() + 2, std::move(v));
  EXPECT_EQ(4, list.size());
  EXPECT_EQ(5, list[2]);
}

TEST(ListTest_NonIValueBasedList, whenCallingInsertOnMutableIteratorWithRValue_thenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  int64_t v = 5;
  list.insert(list.begin() + 2, std::move(v));
  EXPECT_EQ(4, list.size());
  EXPECT_EQ(5, list[2]);
}

TEST(ListTest_NonIValueBasedList, whenCallingInsertWithLValue_thenReturnsIteratorToNewElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  int64_t v = 5;
  ListPtr<int64_t>::iterator result = list.insert(list.cbegin() + 2, v);
  EXPECT_EQ(list.begin() + 2, result);
}

TEST(ListTest_NonIValueBasedList, whenCallingInsertWithRValue_thenReturnsIteratorToNewElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  int64_t v = 5;
  ListPtr<int64_t>::iterator result = list.insert(list.cbegin() + 2, std::move(v));
  EXPECT_EQ(list.begin() + 2, result);
}

TEST(ListTest_NonIValueBasedList, whenCallingEmplaceWithLValue_thenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  int64_t v = 5;
  list.emplace(list.begin() + 2, v);
  EXPECT_EQ(4, list.size());
  EXPECT_EQ(5, list[2]);
}

TEST(ListTest_NonIValueBasedList, whenCallingEmplaceWithRValue_thenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  int64_t v = 5;
  list.emplace(list.begin() + 2, std::move(v));
  EXPECT_EQ(4, list.size());
  EXPECT_EQ(5, list[2]);
}

TEST(ListTest_NonIValueBasedList, whenCallingEmplaceWithConstructorArg_thenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 6});
  list.emplace(list.begin() + 2, 5); // const char* is a constructor arg to std::int64_t
  EXPECT_EQ(4, list.size());
  EXPECT_EQ(5, list[2]);
}

TEST(ListTest_NonIValueBasedList, whenCallingPushBackWithLValue_ThenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>();
  int64_t v = 5;
  list.push_back(v);
  EXPECT_EQ(1, list.size());
  EXPECT_EQ(5, list[0]);
}

TEST(ListTest_NonIValueBasedList, whenCallingPushBackWithRValue_ThenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>();
  int64_t v = 5;
  list.push_back(std::move(v));
  EXPECT_EQ(1, list.size());
  EXPECT_EQ(5, list[0]);
}

TEST(ListTest_NonIValueBasedList, whenCallingEmplaceBackWithLValue_ThenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>();
  int64_t v = 5;
  list.emplace_back(v);
  EXPECT_EQ(1, list.size());
  EXPECT_EQ(5, list[0]);
}

TEST(ListTest_NonIValueBasedList, whenCallingEmplaceBackWithRValue_ThenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>();
  int64_t v = 5;
  list.emplace_back(std::move(v));
  EXPECT_EQ(1, list.size());
  EXPECT_EQ(5, list[0]);
}

TEST(ListTest_NonIValueBasedList, whenCallingEmplaceBackWithConstructorArg_ThenInsertsElement) {
  ListPtr<int64_t> list = make_list<int64_t>();
  list.emplace_back(5);  // const char* is a constructor arg to std::int64_t
  EXPECT_EQ(1, list.size());
  EXPECT_EQ(5, list[0]);
}

TEST(ListTest_NonIValueBasedList, givenEmptyList_whenIterating_thenBeginIsEnd) {
  ListPtr<int64_t> list = make_list<int64_t>();
  const ListPtr<int64_t> clist = make_list<int64_t>();
  EXPECT_EQ(list.begin(), list.end());
  EXPECT_EQ(list.cbegin(), list.cend());
  EXPECT_EQ(clist.begin(), clist.end());
  EXPECT_EQ(clist.cbegin(), clist.cend());
}

TEST(ListTest_NonIValueBasedList, givenMutableList_whenIterating_thenFindsElements) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 5});
  bool found_first = false;
  bool found_second = false;
  for (ListPtr<int64_t>::iterator iter = list.begin(); iter != list.end(); ++iter) {
    if (*iter == 3) {
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (*iter == 5) {
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(ListTest_NonIValueBasedList, givenMutableList_whenIteratingWithForeach_thenFindsElements) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 5});
  bool found_first = false;
  bool found_second = false;
  for (const auto& elem : list) {
    if (elem == 3) {
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (elem == 5) {
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(ListTest_NonIValueBasedList, givenConstList_whenIterating_thenFindsElements) {
  const ListPtr<int64_t> list = make_list<int64_t>({3, 5});
  bool found_first = false;
  bool found_second = false;
  for (ListPtr<int64_t>::const_iterator iter = list.begin(); iter != list.end(); ++iter) {
    if (*iter == 3) {
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (*iter == 5) {
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(ListTest_NonIValueBasedList, givenConstList_whenIteratingWithForeach_thenFindsElements) {
  const ListPtr<int64_t> list = make_list<int64_t>({3, 5});
  bool found_first = false;
  bool found_second = false;
  for (const auto& elem : list) {
    if (elem == 3) {
      EXPECT_FALSE(found_first);
      found_first = true;
    } else if (elem == 5) {
      EXPECT_FALSE(found_second);
      found_second = true;
    } else {
      ADD_FAILURE();
    }
  }
  EXPECT_TRUE(found_first);
  EXPECT_TRUE(found_second);
}

TEST(ListTest_NonIValueBasedList, givenOneElementList_whenErasing_thenListIsEmpty) {
  ListPtr<int64_t> list = make_list<int64_t>({3});
  list.erase(list.cbegin());
  EXPECT_TRUE(list.empty());
}

TEST(ListTest_NonIValueBasedList, givenList_whenErasing_thenReturnsIterator) {
  ListPtr<int64_t> list = make_list<int64_t>({1, 2, 3});
  ListPtr<int64_t>::iterator iter = list.erase(list.begin() + 1);
  EXPECT_EQ(list.begin() + 1, iter);
}

TEST(ListTest_NonIValueBasedList, givenList_whenErasingFullRange_thenIsEmpty) {
  ListPtr<int64_t> list = make_list<int64_t>({1, 2, 3});
  list.erase(list.cbegin(), list.cend());
  EXPECT_TRUE(list.empty());
}

TEST(ListTest_NonIValueBasedList, whenCallingReserve_thenDoesntCrash) {
  ListPtr<int64_t> list = make_list<int64_t>();
  list.reserve(100);
}

TEST(ListTest_NonIValueBasedList, whenCopyConstructingList_thenAreEqual) {
  ListPtr<int64_t> list1 = make_list<int64_t>({3, 4});

  ListPtr<int64_t> list2(list1);

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ(3, list2.get(0));
  EXPECT_EQ(4, list2.get(1));
}

TEST(ListTest_NonIValueBasedList, whenCopyAssigningList_thenAreEqual) {
  ListPtr<int64_t> list1 = make_list<int64_t>({3, 4});

  ListPtr<int64_t> list2 = make_list<int64_t>();
  list2 = list1;

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ(3, list2.get(0));
  EXPECT_EQ(4, list2.get(1));
}

TEST(ListTest_NonIValueBasedList, whenCopyingList_thenAreEqual) {
  ListPtr<int64_t> list1 = make_list<int64_t>({3, 4});

  ListPtr<int64_t> list2 = list1.copy();

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ(3, list2.get(0));
  EXPECT_EQ(4, list2.get(1));
}

TEST(ListTest_NonIValueBasedList, whenMoveConstructingList_thenNewIsCorrect) {
  ListPtr<int64_t> list1 = make_list<int64_t>({3, 4});

  ListPtr<int64_t> list2(std::move(list1));

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ(3, list2.get(0));
  EXPECT_EQ(4, list2.get(1));
}

TEST(ListTest_NonIValueBasedList, whenMoveAssigningList_thenNewIsCorrect) {
  ListPtr<int64_t> list1 = make_list<int64_t>({3, 4});

  ListPtr<int64_t> list2 = make_list<int64_t>();
  list2 = std::move(list1);

  EXPECT_EQ(2, list2.size());
  EXPECT_EQ(3, list2.get(0));
  EXPECT_EQ(4, list2.get(1));
}

TEST(ListTest_NonIValueBasedList, whenMoveConstructingList_thenOldIsEmpty) {
  ListPtr<int64_t> list1 = make_list<int64_t>({3, 4});

  ListPtr<int64_t> list2(std::move(list1));
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest_NonIValueBasedList, whenMoveAssigningList_thenOldIsEmpty) {
  ListPtr<int64_t> list1 = make_list<int64_t>({3, 4});

  ListPtr<int64_t> list2 = make_list<int64_t>();
  list2 = std::move(list1);
  EXPECT_TRUE(list1.empty());
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenAssigningToConstIterator_thenWorks) {
  ListPtr<int64_t> list = make_list<int64_t>({3});
  ListPtr<int64_t>::iterator iter = list.begin();
  ListPtr<int64_t>::const_iterator const_iter = iter;
  EXPECT_EQ(3, *const_iter);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenPostfixIncrementing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::iterator iter1 = list.begin();
  ListPtr<int64_t>::iterator iter2 = iter1++;
  EXPECT_NE(3, *iter1);
  EXPECT_EQ(3, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenPostfixIncrementing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::const_iterator iter1 = list.cbegin();
  ListPtr<int64_t>::const_iterator iter2 = iter1++;
  EXPECT_NE(3, *iter1);
  EXPECT_EQ(3, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenPrefixIncrementing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::iterator iter1 = list.begin();
  ListPtr<int64_t>::iterator iter2 = ++iter1;
  EXPECT_NE(3, *iter1);
  EXPECT_NE(3, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenPrefixIncrementing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::const_iterator iter1 = list.cbegin();
  ListPtr<int64_t>::const_iterator iter2 = ++iter1;
  EXPECT_NE(3, *iter1);
  EXPECT_NE(3, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenPostfixDecrementing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::iterator iter1 = list.end() - 1;
  ListPtr<int64_t>::iterator iter2 = iter1--;
  EXPECT_NE(4, *iter1);
  EXPECT_EQ(4, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenPostfixDecrementing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::const_iterator iter1 = list.cend() - 1;
  ListPtr<int64_t>::const_iterator iter2 = iter1--;
  EXPECT_NE(4, *iter1);
  EXPECT_EQ(4, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenPrefixDecrementing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::iterator iter1 = list.end() - 1;
  ListPtr<int64_t>::iterator iter2 = --iter1;
  EXPECT_NE(4, *iter1);
  EXPECT_NE(4, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenPrefixDecrementing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::const_iterator iter1 = list.cend() - 1;
  ListPtr<int64_t>::const_iterator iter2 = --iter1;
  EXPECT_NE(4, *iter1);
  EXPECT_NE(4, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenIncreasing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 5});

  ListPtr<int64_t>::iterator iter1 = list.begin();
  ListPtr<int64_t>::iterator iter2 = iter1 += 2;
  EXPECT_EQ(5, *iter1);
  EXPECT_EQ(5, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenIncreasing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 5});

  ListPtr<int64_t>::const_iterator iter1 = list.cbegin();
  ListPtr<int64_t>::const_iterator iter2 = iter1 += 2;
  EXPECT_EQ(5, *iter1);
  EXPECT_EQ(5, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenDecreasing_thenMovesToNextAndReturnsNewPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 5});

  ListPtr<int64_t>::iterator iter1 = list.end();
  ListPtr<int64_t>::iterator iter2 = iter1 -= 2;
  EXPECT_EQ(4, *iter1);
  EXPECT_EQ(4, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenDecreasing_thenMovesToNextAndReturnsOldPosition) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 5});

  ListPtr<int64_t>::const_iterator iter1 = list.cend();
  ListPtr<int64_t>::const_iterator iter2 = iter1 -= 2;
  EXPECT_EQ(4, *iter1);
  EXPECT_EQ(4, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenAdding_thenReturnsNewIterator) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 5});

  ListPtr<int64_t>::iterator iter1 = list.begin();
  ListPtr<int64_t>::iterator iter2 = iter1 + 2;
  EXPECT_EQ(3, *iter1);
  EXPECT_EQ(5, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenAdding_thenReturnsNewIterator) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 5});

  ListPtr<int64_t>::const_iterator iter1 = list.cbegin();
  ListPtr<int64_t>::const_iterator iter2 = iter1 + 2;
  EXPECT_EQ(3, *iter1);
  EXPECT_EQ(5, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenSubtracting_thenReturnsNewIterator) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 5});

  ListPtr<int64_t>::iterator iter1 = list.end() - 1;
  ListPtr<int64_t>::iterator iter2 = iter1 - 2;
  EXPECT_EQ(5, *iter1);
  EXPECT_EQ(3, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenSubtracting_thenReturnsNewIterator) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4, 5});

  ListPtr<int64_t>::const_iterator iter1 = list.cend() - 1;
  ListPtr<int64_t>::const_iterator iter2 = iter1 - 2;
  EXPECT_EQ(5, *iter1);
  EXPECT_EQ(3, *iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenCalculatingDifference_thenReturnsCorrectNumber) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  EXPECT_EQ(2, list.end() - list.begin());
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenCalculatingDifference_thenReturnsCorrectNumber) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});
  EXPECT_EQ(2, list.cend() - list.cbegin());
}

TEST(ListTest_NonIValueBasedList, givenEqualMutableIterators_thenAreEqual) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::iterator iter1 = list.begin();
  ListPtr<int64_t>::iterator iter2 = list.begin();
  EXPECT_TRUE(iter1 == iter2);
  EXPECT_FALSE(iter1 != iter2);
}

TEST(ListTest_NonIValueBasedList, givenDifferentMutableIterators_thenAreNotEqual) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::iterator iter1 = list.begin();
  ListPtr<int64_t>::iterator iter2 = list.begin();
  iter2++;

  EXPECT_FALSE(iter1 == iter2);
  EXPECT_TRUE(iter1 != iter2);
}

TEST(ListTest_NonIValueBasedList, givenEqualConstIterators_thenAreEqual) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::const_iterator iter1 = list.cbegin();
  ListPtr<int64_t>::const_iterator iter2 = list.cbegin();
  EXPECT_TRUE(iter1 == iter2);
  EXPECT_FALSE(iter1 != iter2);
}

TEST(ListTest_NonIValueBasedList, givenDifferentConstIterators_thenAreNotEqual) {
  ListPtr<int64_t> list = make_list<int64_t>({3, 4});

  ListPtr<int64_t>::const_iterator iter1 = list.cbegin();
  ListPtr<int64_t>::const_iterator iter2 = list.cbegin();
  iter2++;

  EXPECT_FALSE(iter1 == iter2);
  EXPECT_TRUE(iter1 != iter2);
}

TEST(ListTest_NonIValueBasedList, givenMutableIterator_whenDereferencing_thenPointsToCorrectElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3});

  ListPtr<int64_t>::iterator iter = list.begin();
  EXPECT_EQ(3, *iter);
}

TEST(ListTest_NonIValueBasedList, givenConstIterator_whenDereferencing_thenPointsToCorrectElement) {
  ListPtr<int64_t> list = make_list<int64_t>({3});

  ListPtr<int64_t>::const_iterator iter = list.cbegin();
  EXPECT_EQ(3, *iter);
}

TEST(ListTest_NonIValueBasedList, givenOneElementList_whenCallingPopBack_thenIsEmpty) {
  ListPtr<int64_t> list = make_list<int64_t>({3});
  list.pop_back();
  EXPECT_TRUE(list.empty());
}

TEST(ListTest_NonIValueBasedList, givenEmptyList_whenCallingResize_thenResizesAndSetsEmptyValue) {
  ListPtr<int64_t> list = make_list<int64_t>();
  list.resize(2);
  EXPECT_EQ(2, list.size());
  EXPECT_EQ(0, list[0]);
  EXPECT_EQ(0, list[1]);
}

TEST(ListTest_NonIValueBasedList, givenEmptyList_whenCallingResizeWithValue_thenResizesAndSetsValue) {
  ListPtr<int64_t> list = make_list<int64_t>();
  list.resize(2, 5);
  EXPECT_EQ(2, list.size());
  EXPECT_EQ(5, list[0]);
  EXPECT_EQ(5, list[1]);
}

TEST(ListTest_NonIValueBasedList, isReferenceType) {
  ListPtr<int64_t> list1 = make_list<int64_t>();
  ListPtr<int64_t> list2(list1);
  ListPtr<int64_t> list3 = make_list<int64_t>();
  list3 = list1;

  list1.push_back(3);
  EXPECT_EQ(1, list1.size());
  EXPECT_EQ(1, list2.size());
  EXPECT_EQ(1, list3.size());
}

TEST(ListTest_NonIValueBasedList, copyHasSeparateStorage) {
  ListPtr<int64_t> list1 = make_list<int64_t>();
  ListPtr<int64_t> list2(list1.copy());
  ListPtr<int64_t> list3 = make_list<int64_t>();
  list3 = list1.copy();

  list1.push_back(3);
  EXPECT_EQ(1, list1.size());
  EXPECT_EQ(0, list2.size());
  EXPECT_EQ(0, list3.size());
}
