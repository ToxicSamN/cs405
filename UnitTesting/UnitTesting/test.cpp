// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    
    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());

    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());

    // if not empty, size must be 5
    ASSERT_EQ(collection->size(), 5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, IsMaxSizeEqualToSize) 
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
    
    // if empty, max size must be >=0
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // add 1 entry
    add_entries(1);
    // max size must be greater than or equal to size==1
    ASSERT_TRUE(collection->max_size() >= collection->size());

    add_entries(5);
    // max size must be greater than or equal to size==5
    ASSERT_TRUE(collection->max_size() >= collection->size());

    add_entries(10);
    // max size must be greater than or equal to size==1
    ASSERT_TRUE(collection->max_size() >= collection->size());
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, IsCapacityEqualToSize)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // if empty, capacity size must be >=0
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // add 1 entry
    add_entries(1);
    // capacity size must be greater than or equal to size==1
    ASSERT_TRUE(collection->capacity() >= collection->size());

    add_entries(5);
    // capacity size must be greater than or equal to size==5
    ASSERT_TRUE(collection->capacity() >= collection->size());

    add_entries(10);
    // capacity size must be greater than or equal to size==1
    ASSERT_TRUE(collection->capacity() >= collection->size());
}

// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, CanResizeIncrease)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // get current size
    auto start_size = collection->size();
    // increase size by 1
    collection->resize(start_size + 1); // size should be 1

    // size should be greater than starting size
    ASSERT_EQ(collection->size(), start_size + 1);
}

// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, CanResizeDecrease)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // increase collection size by adding entries
    add_entries(2);

    // collection should not be empty
    ASSERT_FALSE(collection->empty());

    // if not empty, size should be 1
    ASSERT_EQ(collection->size(), 2);
    
    // get starting size
    auto start_size = collection->size();

    // decrease size with resize
    collection->resize(start_size - 1); // should be 1 now

    // size should be greater than starting size
    ASSERT_TRUE(start_size > collection->size());
}

// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, CanResizeDecreaseToZero)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // increase collection size by adding entries
    add_entries(2);

    // collection should not be empty
    ASSERT_FALSE(collection->empty());

    // if not empty, size should be 1
    ASSERT_EQ(collection->size(), 2);

    // get starting size
    auto start_size = collection->size();

    // decrease size with resize
    collection->resize(start_size - start_size); // should be 0 now

    // size should be greater than starting size
    ASSERT_TRUE(collection->size() == 0);
}

// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, CanClearCollection)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // add entries to be cleared
    add_entries(1);

    // collection should not be empty
    ASSERT_FALSE(collection->empty());

    // if not empty, size should be 1
    ASSERT_EQ(collection->size(), 1);

    // clear the entries
    collection->clear();

    // collection should be empty
    ASSERT_TRUE(collection->empty());
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, CanEraseBeginToEnd)
{

    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // increase collection size by adding entries
    add_entries(2);

    // collection should not be empty
    ASSERT_FALSE(collection->empty());

    // if not empty, size should be 1
    ASSERT_EQ(collection->size(), 2);

    // erase collection from begin to end
    collection->erase(collection->begin(), collection->end());

    // the collection should be empty
    ASSERT_TRUE(collection->empty());
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, CanReserveCapacityNotSize)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // reserve capacity
    collection->reserve(2);

    // capacity must be 2
    ASSERT_EQ(collection->capacity(), 2);

    // size must be 0
    ASSERT_EQ(collection->size(), 0);
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
// NOTE: This is a negative test
TEST_F(CollectionTest, AlwaysFailIndexOutOfRange)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // wrap in try/catch block to verify excpetion
    try {
        // collection size is 0, so no index of 1 exists
        // this should trhwo an exception
        collection->at(1);
    }
    catch (std::out_of_range) {
        FAIL() << "Out Of Range exception thrown";
    }

    // if excpetion not thrown, then fail the test with a "positive" test result
    ASSERT_TRUE(true);
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
TEST_F(CollectionTest, CanShrinkToFitCapcityWithSize)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // reserve capacity
    collection->reserve(2);

    // capacity must be 2
    ASSERT_EQ(collection->capacity(), 2);

    // size must be 0
    ASSERT_EQ(collection->size(), 0);

    // Shrink to fit capcity to size
    collection->shrink_to_fit();

    // capcity and size should be equal now
    ASSERT_EQ(collection->capacity(), collection->size());
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
// NOTE: This is a negative test
TEST_F(CollectionTest, AlwaysFailResizeToNegativeSize)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    // get starting size
    auto start_size = collection->size(); // is 0

    // decrease size with resize to -1
    // negative test should throw exception, wrap in try/catch
    // to verify exception thrown
    try {
        collection->resize(start_size - 1);
    }
    catch (std::length_error) {
        FAIL() << "exception 'vector too long', cannot allocate a negative vector size";
    }

    // if exception not thrown, then fail the test with a "positive" test result
    ASSERT_TRUE(true);
}