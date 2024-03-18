#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <bitset/bitset.hpp>

TEST_CASE("ctor") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));
  CHECK_EQ(bitset.Size(), 8);
  CHECK_EQ(bitset.Get(0), 1);
  CHECK_EQ(bitset.Get(1), 0);
  CHECK_EQ(bitset.Get(2), 1);
  CHECK_EQ(bitset.Get(3), 0);
  CHECK_EQ(bitset.Get(4), 1);
  CHECK_EQ(bitset.Get(5), 0);
  CHECK_EQ(bitset.Get(6), 1);
  CHECK_EQ(bitset.Get(7), 0);
}

TEST_CASE("resize test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));
  
  bitset.Resize(10);
  CHECK_EQ(bitset.Size(), 10);
  CHECK_EQ(bitset.Get(8), 0);
  CHECK_EQ(bitset.Get(9), 0);

  CHECK_EQ(bitset.Get(0), 1);
  CHECK_EQ(bitset.Get(1), 0);
  CHECK_EQ(bitset.Get(2), 1);
  CHECK_EQ(bitset.Get(3), 0);
  CHECK_EQ(bitset.Get(4), 1);
  CHECK_EQ(bitset.Get(5), 0);
  CHECK_EQ(bitset.Get(6), 1);
  CHECK_EQ(bitset.Get(7), 0);
}

TEST_CASE("clear test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));

  bitset.Clear();
  CHECK_THROWS_AS(bitset.Get(0), std::out_of_range);
}

TEST_CASE("out of range test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));

  CHECK_THROWS_AS(bitset.Get(8), std::out_of_range);
  CHECK_THROWS_AS(bitset.Get(-1), std::out_of_range);
  CHECK_THROWS_AS(bitset.Get(32), std::out_of_range);
  CHECK_THROWS_AS(bitset.Set(8, 1), std::out_of_range);
  CHECK_THROWS_AS(bitset.Set(-1, 1), std::out_of_range);
  CHECK_THROWS_AS(bitset.Get(-1), std::out_of_range);
}

TEST_CASE("bit operations test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, 1));
  CHECK_NOTHROW(bitset.Set(1, 0));
  CHECK_NOTHROW(bitset.Set(2, 1));
  CHECK_NOTHROW(bitset.Set(3, 0));
  CHECK_NOTHROW(bitset.Set(4, 1));
  CHECK_NOTHROW(bitset.Set(5, 0));
  CHECK_NOTHROW(bitset.Set(6, 1));
  CHECK_NOTHROW(bitset.Set(7, 0));

  BitSet bitset1(8);
  CHECK_EQ(bitset1.Size(), 8);
  bitset1 = ~bitset;
  CHECK_FALSE(bitset1.Get(0) == bitset.Get(0));
  CHECK_FALSE(bitset1.Get(1) == bitset.Get(1));
  CHECK_FALSE(bitset1.Get(2) == bitset.Get(2));
  CHECK_FALSE(bitset1.Get(3) == bitset.Get(3));
  CHECK_FALSE(bitset1.Get(4) == bitset.Get(4));
  CHECK_FALSE(bitset1.Get(5) == bitset.Get(5));
  CHECK_FALSE(bitset1.Get(6) == bitset.Get(6));
  CHECK_FALSE(bitset1.Get(7) == bitset.Get(7));
}