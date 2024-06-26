#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <bitset/bitset.hpp>
#include <fstream>
#include <filesystem>

#define ROOT std::filesystem::current_path().parent_path().parent_path().parent_path().parent_path().parent_path().string() + '/'

TEST_CASE("ctor") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, true));
  CHECK_NOTHROW(bitset.Set(1, false));
  CHECK_NOTHROW(bitset.Set(2, true));
  CHECK_NOTHROW(bitset.Set(3, false));
  CHECK_NOTHROW(bitset.Set(4, true));
  CHECK_NOTHROW(bitset.Set(5, false));
  CHECK_NOTHROW(bitset.Set(6, true));
  CHECK_NOTHROW(bitset.Set(7, false));
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
  CHECK_NOTHROW(bitset.Set(0, true));
  CHECK_NOTHROW(bitset.Set(1, false));
  CHECK_NOTHROW(bitset.Set(2, true));
  CHECK_NOTHROW(bitset.Set(3, false));
  CHECK_NOTHROW(bitset.Set(4, true));
  CHECK_NOTHROW(bitset.Set(5, false));
  CHECK_NOTHROW(bitset.Set(6, true));
  CHECK_NOTHROW(bitset.Set(7, false));
  
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
  CHECK_NOTHROW(bitset.Set(0, true));
  CHECK_NOTHROW(bitset.Set(1, false));
  CHECK_NOTHROW(bitset.Set(2, true));
  CHECK_NOTHROW(bitset.Set(3, false));
  CHECK_NOTHROW(bitset.Set(4, true));
  CHECK_NOTHROW(bitset.Set(5, false));
  CHECK_NOTHROW(bitset.Set(6, true));
  CHECK_NOTHROW(bitset.Set(7, false));

  bitset.Clear();
  CHECK_THROWS_AS(bitset.Get(0), std::out_of_range);
}

TEST_CASE("out of range test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, true));
  CHECK_NOTHROW(bitset.Set(1, false));
  CHECK_NOTHROW(bitset.Set(2, true));
  CHECK_NOTHROW(bitset.Set(3, false));
  CHECK_NOTHROW(bitset.Set(4, true));
  CHECK_NOTHROW(bitset.Set(5, false));
  CHECK_NOTHROW(bitset.Set(6, true));
  CHECK_NOTHROW(bitset.Set(7, false));

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
  CHECK_NOTHROW(bitset.Set(0, true));
  CHECK_NOTHROW(bitset.Set(1, false));
  CHECK_NOTHROW(bitset.Set(2, true));
  CHECK_NOTHROW(bitset.Set(3, false));
  CHECK_NOTHROW(bitset.Set(4, true));
  CHECK_NOTHROW(bitset.Set(5, false));
  CHECK_NOTHROW(bitset.Set(6, true));
  CHECK_NOTHROW(bitset.Set(7, false));

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

  BitSet bitset2(8);
  CHECK_EQ(bitset2.Size(), 8);
  CHECK_NOTHROW(bitset2.Set(0, true));
  CHECK_NOTHROW(bitset2.Set(1, true));
  CHECK_NOTHROW(bitset2.Set(2, true));
  CHECK_NOTHROW(bitset2.Set(3, true));
  CHECK_NOTHROW(bitset2.Set(4, true));
  CHECK_NOTHROW(bitset2.Set(5, true));
  CHECK_NOTHROW(bitset2.Set(6, true));
  CHECK_NOTHROW(bitset2.Set(7, true));

  BitSet bitset3(8);
  CHECK_EQ(bitset3.Size(), 8);
  bitset3 = bitset & bitset2;
  CHECK_EQ(bitset3.Get(0), bitset.Get(0));
  CHECK_EQ(bitset3.Get(1), bitset.Get(1));
  CHECK_EQ(bitset3.Get(2), bitset.Get(2));
  CHECK_EQ(bitset3.Get(3), bitset.Get(3));
  CHECK_EQ(bitset3.Get(4), bitset.Get(4));
  CHECK_EQ(bitset3.Get(5), bitset.Get(5));
  CHECK_EQ(bitset3.Get(6), bitset.Get(6));
  CHECK_EQ(bitset3.Get(7), bitset.Get(7));

  BitSet bitset4(8);
  CHECK_EQ(bitset4.Size(), 8);
  bitset4 = bitset | bitset2;
  CHECK_EQ(bitset4.Get(0), 1);
  CHECK_EQ(bitset4.Get(1), 1);
  CHECK_EQ(bitset4.Get(2), 1);
  CHECK_EQ(bitset4.Get(3), 1);
  CHECK_EQ(bitset4.Get(4), 1);
  CHECK_EQ(bitset4.Get(5), 1);
  CHECK_EQ(bitset4.Get(6), 1);
  CHECK_EQ(bitset4.Get(7), 1);

  BitSet bitset5(8);
  CHECK_EQ(bitset5.Size(), 8);
  bitset5 = bitset ^ bitset1;
  CHECK_EQ(bitset5.Get(0), 1);
  CHECK_EQ(bitset5.Get(1), 1);
  CHECK_EQ(bitset5.Get(2), 1);
  CHECK_EQ(bitset5.Get(3), 1);
  CHECK_EQ(bitset5.Get(4), 1);
  CHECK_EQ(bitset5.Get(5), 1);
  CHECK_EQ(bitset5.Get(6), 1);
  CHECK_EQ(bitset5.Get(7), 1);

  bitset2.Resize(7);
  CHECK_THROWS_AS(bitset2.Set(7, 1), std::out_of_range);
  CHECK_THROWS(bitset2 & bitset);
  CHECK_THROWS(bitset2 | bitset);
  CHECK_THROWS(bitset2 ^ bitset);
  CHECK_FALSE(bitset2 == bitset);
  CHECK(bitset2 != bitset);
}

TEST_CASE("comparison test") {
  BitSet bitset(8);
  CHECK_EQ(bitset.Size(), 8);
  CHECK_NOTHROW(bitset.Set(0, true));
  CHECK_NOTHROW(bitset.Set(1, false));
  CHECK_NOTHROW(bitset.Set(2, true));
  CHECK_NOTHROW(bitset.Set(3, false));
  CHECK_NOTHROW(bitset.Set(4, true));
  CHECK_NOTHROW(bitset.Set(5, false));
  CHECK_NOTHROW(bitset.Set(6, true));
  CHECK_NOTHROW(bitset.Set(7, false));

  BitSet bitset1(8);
  CHECK_EQ(bitset1.Size(), 8);
  CHECK_NOTHROW(bitset1.Set(0, true));
  CHECK_NOTHROW(bitset1.Set(1, false));
  CHECK_NOTHROW(bitset1.Set(2, true));
  CHECK_NOTHROW(bitset1.Set(3, false));
  CHECK_NOTHROW(bitset1.Set(4, true));
  CHECK_NOTHROW(bitset1.Set(5, false));
  CHECK_NOTHROW(bitset1.Set(6, true));
  CHECK_NOTHROW(bitset1.Set(7, false));

  CHECK(bitset == bitset1);
  
  CHECK_NOTHROW(bitset1.Set(0, false));

  CHECK(bitset != bitset1);

  BitSet bitset2(8);
  CHECK_EQ(bitset2.Size(), 8);
  CHECK_NOTHROW(bitset2.Set(0, true));
  CHECK_NOTHROW(bitset2.Set(1, true));
  CHECK_NOTHROW(bitset2.Set(2, true));
  CHECK_NOTHROW(bitset2.Set(3, true));
  CHECK_NOTHROW(bitset2.Set(4, true));
  CHECK_NOTHROW(bitset2.Set(5, true));
  CHECK_NOTHROW(bitset2.Set(6, true));
  CHECK_NOTHROW(bitset2.Set(7, true));

  CHECK(bitset != bitset2);

  CHECK_NOTHROW(bitset2.Set(1, false));
  CHECK_NOTHROW(bitset2.Set(3, false));
  CHECK_NOTHROW(bitset2.Set(5, false));
  CHECK_NOTHROW(bitset2.Set(7, false));

  CHECK(bitset == bitset2);
}

TEST_CASE("bigger size") {
  BitSet bitset(38);
  CHECK_EQ(bitset.Size(), 38);
  CHECK_NOTHROW(bitset.Set(32, true));
  CHECK_NOTHROW(bitset.Set(33, false));
  CHECK_NOTHROW(bitset.Set(34, true));
  CHECK_NOTHROW(bitset.Set(35, false));
  CHECK_NOTHROW(bitset.Set(36, true));
  CHECK_NOTHROW(bitset.Set(37, false));
  CHECK_EQ(bitset.Get(32), 1);
  CHECK_EQ(bitset.Get(33), 0);
  CHECK_EQ(bitset.Get(34), 1);
  CHECK_EQ(bitset.Get(35), 0);
  CHECK_EQ(bitset.Get(36), 1);
  CHECK_EQ(bitset.Get(37), 0);
}

TEST_CASE("time test") {
  long long diff = 0;

  BitSet bit1(100000);
  for (int i = 0; i < 100000; i++) {
    bit1.Set(i, 1);
  }
  auto start = std::chrono::steady_clock::now();
  BitSet bit2(bit1);
  auto end = std::chrono::steady_clock::now();
  CHECK_EQ(bit2.Get(0), 1);
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff = duration.count();

  start = std::chrono::steady_clock::now();
  BitSet bit3(std::move(bit1));
  end = std::chrono::steady_clock::now();
  CHECK_EQ(bit3.Get(0), 1);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff -= duration.count();

  CHECK(diff > duration.count() * 10);

  BitSet bit4(100000);
  for (int i = 0; i < 100000; i++) {
    bit4.Set(i, 1);
  }
  BitSet bit5;
  start = std::chrono::steady_clock::now();
  bit5 = bit4;
  end = std::chrono::steady_clock::now();
  CHECK_EQ(bit5.Get(0), 1);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff = duration.count();

  start = std::chrono::steady_clock::now();
  BitSet bit6 = std::move(bit4);
  end = std::chrono::steady_clock::now();
  CHECK_EQ(bit6.Get(0), 1);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  diff -= duration.count();

  CHECK(diff > duration.count() * 10);
}

TEST_CASE("operator[] test") {
  BitSet bitset(8);
  CHECK_NOTHROW(bitset.Set(0, true));
  CHECK_NOTHROW(bitset.Set(1, false));
  CHECK_NOTHROW(bitset.Set(2, true));
  CHECK_NOTHROW(bitset.Set(3, false));
  CHECK_NOTHROW(bitset.Set(4, true));
  CHECK_NOTHROW(bitset.Set(5, false));
  CHECK_NOTHROW(bitset.Set(6, true));
  CHECK_NOTHROW(bitset.Set(7, false));

  CHECK_EQ(bitset[0], true);
  CHECK_EQ(bitset[1], false);
  CHECK_EQ(bitset[2], true);
  CHECK_EQ(bitset[3], false);
  CHECK_EQ(bitset[4], true);
  CHECK_EQ(bitset[5], false);
  CHECK_EQ(bitset[6], true);
  CHECK_EQ(bitset[7], false);

  bool temp = false;
  for (int i = 0; i < 8; i++) {
    temp = bitset[i];
    CHECK_EQ(temp, bitset[i]);
  }

  CHECK_NOTHROW(bitset.Resize(40));
  CHECK_EQ(bitset.Size(), 40);
  CHECK_NOTHROW(bitset.Set(32, true));
  CHECK_NOTHROW(bitset.Set(33, false));
  CHECK_NOTHROW(bitset.Set(34, true));
  CHECK_NOTHROW(bitset.Set(35, false));
  CHECK_NOTHROW(bitset.Set(36, true));
  CHECK_NOTHROW(bitset.Set(37, false));
  CHECK_NOTHROW(bitset.Set(38, true));
  CHECK_NOTHROW(bitset.Set(39, false));

  CHECK_EQ(bitset[32], true);
  CHECK_EQ(bitset[33], false);
  CHECK_EQ(bitset[34], true);
  CHECK_EQ(bitset[35], false);
  CHECK_EQ(bitset[36], true);
  CHECK_EQ(bitset[37], false);
  CHECK_EQ(bitset[38], true);
  CHECK_EQ(bitset[39], false);

  temp = false;
  for (int i = 0; i < 40; i++) {
    temp = bitset[i];
    CHECK_EQ(temp, bitset[i]);
  }

  BitSet bitset2(32);
  for (int i = 0; i < bitset.Size(); i++) {
    bitset[i] = i % 32;
  }

  for (int i = 0; i < bitset.Size() - bitset.Size() % 3; i+=3) {
    bitset[i] = bitset[i + 1] = bitset[i + 2];
    CHECK((bitset[i] == bitset[i + 1] && bitset[i + 1] == bitset[i + 2]));
  }
}

TEST_CASE("formated io") {
  BitSet bitset1(112);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_NOTHROW(bitset1.Set(i, i % 2 == 0));
  }
  CHECK_EQ(bitset1.Size(), 112);

  BitSet bitset2(234);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_NOTHROW(bitset2.Set(i, i % 2 == 1));
  }
  CHECK_EQ(bitset2.Size(), 234);

  std::ofstream out_file(ROOT + "prj.test/io/bitset_io.txt");
  out_file << bitset1 << bitset2;
  out_file.close();

  std::ifstream in_file(ROOT + "prj.test/io/bitset_io.txt");
  in_file >> bitset1 >> bitset2;
  in_file.close();

  CHECK_EQ(bitset1.Size(), 112);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_EQ(bitset1.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset2.Size(), 234);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_EQ(bitset2.Get(i), i % 2 == 1);
  }

  out_file.open(ROOT + "prj.test/io/bitset_io.txt");
  out_file << bitset2 << bitset1;
  out_file.close();

  in_file.open(ROOT + "prj.test/io/bitset_io.txt");
  in_file >> bitset2 >> bitset1;
  in_file.close();

  CHECK_EQ(bitset1.Size(), 112);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_EQ(bitset1.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset2.Size(), 234);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_EQ(bitset2.Get(i), i % 2 == 1);
  }

  out_file.open(ROOT + "prj.test/io/bitset_io.txt");
  out_file << bitset1 << bitset2;
  out_file.close();

  in_file.open(ROOT + "prj.test/io/bitset_io.txt");
  in_file >> bitset2 >> bitset1;
  in_file.close();

  CHECK_EQ(bitset1.Size(), 234);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_EQ(bitset1.Get(i), i % 2 == 1);
  }

  CHECK_EQ(bitset2.Size(), 112);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_EQ(bitset2.Get(i), i % 2 == 0);
  }

  out_file.open(ROOT + "prj.test/io/bitset_io.txt");
  out_file << bitset2 << bitset1;
  out_file.close();

  in_file.open(ROOT + "prj.test/io/bitset_io.txt");
  in_file >> bitset1 >> bitset2;
  in_file.close();

  CHECK_EQ(bitset1.Size(), 112);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_EQ(bitset1.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset2.Size(), 234);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_EQ(bitset2.Get(i), i % 2 == 1);
  }
}

TEST_CASE("multiple bitset formatted io") {
  BitSet bitset1(32);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_NOTHROW(bitset1.Set(i, i % 2 == 0));
  }
  CHECK_EQ(bitset1.Size(), 32);

  BitSet bitset2(64);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_NOTHROW(bitset2.Set(i, i % 2 == 1));
  }

  BitSet bitset3(85);
  for (int i = 0; i < bitset3.Size(); i += 1) {
    CHECK_NOTHROW(bitset3.Set(i, i % 2 == 0));
  }

  BitSet bitset4(43);
  for (int i = 0; i < bitset4.Size(); i += 1) {
    CHECK_NOTHROW(bitset4.Set(i, i % 2 == 1));
  }

  std::ofstream out_file(ROOT + "prj.test/io/bitset_io.txt");
  out_file << bitset1 << bitset2 << bitset3 << bitset4;
  out_file.close();

  std::ifstream in_file(ROOT + "prj.test/io/bitset_io.txt");
  in_file >> bitset4 >> bitset3 >> bitset2 >> bitset1;
  in_file.close();

  CHECK_EQ(bitset1.Size(), 43);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_EQ(bitset1.Get(i), i % 2 == 1);
  }

  CHECK_EQ(bitset2.Size(), 85);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_EQ(bitset2.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset3.Size(), 64);
  for (int i = 0; i < bitset3.Size(); i += 1) {
    CHECK_EQ(bitset3.Get(i), i % 2 == 1);
  }

  CHECK_EQ(bitset4.Size(), 32);
  for (int i = 0; i < bitset4.Size(); i += 1) {
    CHECK_EQ(bitset4.Get(i), i % 2 == 0);
  }
}

TEST_CASE("unformatted io") {
  BitSet bitset(8);
  for (int i = 0; i < bitset.Size(); i += 1) {
    CHECK_NOTHROW(bitset.Set(i, i % 2 == 0));
  }
  CHECK_EQ(bitset.Size(), 8);

  BitSet bitset2(10);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_NOTHROW(bitset2.Set(i, i % 2 == 1));
  }
  CHECK_EQ(bitset2.Size(), 10);

  std::ofstream out_file(ROOT + "prj.test/io/bitset_io");
  bitset2.Write(out_file);
  bitset.Write(out_file);
  out_file.close();

  std::ifstream in_file(ROOT + "prj.test/io/bitset_io");
  CHECK_NOTHROW(bitset2.Read(in_file));
  CHECK_NOTHROW(bitset.Read(in_file));
  in_file.close();

  CHECK_EQ(bitset.Size(), 8);
  for (int i = 0; i < bitset.Size(); i += 1) {
    CHECK_NOTHROW(bitset.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset2.Size(), 10);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_NOTHROW(bitset2.Get(i), i % 2 == 1);
  }

  out_file.open(ROOT + "prj.test/io/bitset_io");
  bitset.Write(out_file);
  bitset2.Write(out_file);
  out_file.close();

  in_file.open(ROOT + "prj.test/io/bitset_io");
  CHECK_NOTHROW(bitset.Read(in_file));
  CHECK_NOTHROW(bitset2.Read(in_file));
  in_file.close();

  CHECK_EQ(bitset.Size(), 8);
  for (int i = 0; i < bitset.Size(); i += 1) {
    CHECK_NOTHROW(bitset.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset2.Size(), 10);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_NOTHROW(bitset2.Get(i), i % 2 == 1);
  }

  out_file.open(ROOT + "prj.test/io/bitset_io");
  bitset.Write(out_file);
  bitset2.Write(out_file);
  out_file.close();

  in_file.open(ROOT + "prj.test/io/bitset_io");
  CHECK_NOTHROW(bitset2.Read(in_file));
  CHECK_NOTHROW(bitset.Read(in_file));
  in_file.close();

  CHECK_EQ(bitset2.Size(), 8);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_NOTHROW(bitset2.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset.Size(), 10);
  for (int i = 0; i < bitset.Size(); i += 1) {
    CHECK_NOTHROW(bitset.Get(i), i % 2 == 1);
  }

  out_file.open(ROOT + "prj.test/io/bitset_io");
  bitset2.Write(out_file);
  bitset.Write(out_file);
  out_file.close();

  in_file.open(ROOT + "prj.test/io/bitset_io");
  CHECK_NOTHROW(bitset.Read(in_file));
  CHECK_NOTHROW(bitset2.Read(in_file));
  in_file.close();

  CHECK_EQ(bitset.Size(), 8);
  for (int i = 0; i < bitset.Size(); i += 1) {
    CHECK_NOTHROW(bitset.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset2.Size(), 10);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_NOTHROW(bitset2.Get(i), i % 2 == 1);
  }
}


TEST_CASE("Multiple bitset unformated io") {
  BitSet bitset1(24);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_NOTHROW(bitset1.Set(i, i % 2 == 0));
  }
  CHECK_EQ(bitset1.Size(), 24);

  BitSet bitset2(32);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_NOTHROW(bitset2.Set(i, i % 2 == 1));
  }
  CHECK_EQ(bitset2.Size(), 32);

  BitSet bitset3(55);
  for (int i = 0; i < bitset3.Size(); i += 1) {
    CHECK_NOTHROW(bitset3.Set(i, i % 2 == 0));
  }
  CHECK_EQ(bitset3.Size(), 55);

  BitSet bitset4(64);
  for(int i = 0; i < bitset4.Size(); i += 1) {
    CHECK_NOTHROW(bitset4.Set(i, i % 2 == 1));
  }
  CHECK_EQ(bitset4.Size(), 64);

  std::ofstream out_file(ROOT + "prj.test/io/bitset_io", std::ios_base::binary);
  bitset1.Write(out_file);
  bitset2.Write(out_file);
  bitset3.Write(out_file);
  bitset4.Write(out_file);
  out_file.close();

  std::ifstream in_file(ROOT + "prj.test/io/bitset_io", std::ios_base::binary);
  bitset4.Read(in_file);
  bitset3.Read(in_file);
  bitset2.Read(in_file);
  bitset1.Read(in_file);
  in_file.close();


  CHECK_EQ(bitset4.Size(), 24);
  for (int i = 0; i < bitset4.Size(); i += 1) {
    CHECK_EQ(bitset4.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset3.Size(), 32);
  for (int i = 0; i < bitset3.Size(); i += 1) {
    CHECK_EQ(bitset3.Get(i), i % 2 == 1);
  }

  CHECK_EQ(bitset2.Size(), 55);
  for (int i = 0; i < bitset2.Size(); i += 1) {
    CHECK_EQ(bitset2.Get(i), i % 2 == 0);
  }

  CHECK_EQ(bitset1.Size(), 64);
  for (int i = 0; i < bitset1.Size(); i += 1) {
    CHECK_EQ(bitset1.Get(i), i % 2 == 1);
  }
}

TEST_CASE("BitAccessor test") {
  BitSet bitset(56);
  for (int i = 0; i < 56; ++i) {
    bitset.Set(i, i & 1);
  }
  
  for (int i = 0; i < 56; ++i) {
    CHECK_EQ(bitset.Get(i), bitset[i]);
  }
  
  for (int i = 0; i < 56; i += 2) {
    bool temp = bitset[i];
    bitset[i] = bitset[i + 1];
    bitset[i + 1] = temp;
  }

  for (int i = 0; i < 56; ++i) {
    CHECK_EQ(!(i & 1), bitset[i]);
  }
}