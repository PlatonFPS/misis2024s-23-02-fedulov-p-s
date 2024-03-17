#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <dynarr/dynarr.hpp>

#include <iostream>

TEST_CASE("DynArr test") {
  DynArr arr;

  CHECK(arr.Size() == 0);
  CHECK_THROWS(arr[0]);
  arr.Resize(5);
  CHECK(arr.Size() == 5);
  

  CHECK_THROWS(arr.Resize(-1));

  CHECK_THROWS(arr[6]);

  arr[0] = 4;
  CHECK(arr[0] == doctest::Approx(4));

  arr[1] = 6;
  CHECK(arr[1] == doctest::Approx(6));
  CHECK(arr[0] == doctest::Approx(4));
  CHECK(arr[0] != doctest::Approx(arr[1]));

  arr.Resize(8);
  CHECK_NOTHROW(arr[7]);
  CHECK(arr[7] == doctest::Approx(0));

  arr.Resize(2);
  CHECK(arr[1] == doctest::Approx(6));
  
  arr.Resize(1);
  arr[0] = 0;
  arr.Resize(4);
  CHECK(arr[0] == doctest::Approx(0));
  arr[0] = 2.1;
  arr[1] = 2;
  arr[3] = 5;
  CHECK(arr[3] == doctest::Approx(5));
  arr.Resize(2);
  CHECK_THROWS(doctest::Approx(arr[3]));
  CHECK(arr[1] == doctest::Approx(2));
  CHECK(arr[0] == doctest::Approx(2.1));
  arr.Resize(4);
  CHECK(arr[3] == doctest::Approx(0));

  DynArr arr2(4);
  CHECK(arr2.Size() == 4);
  CHECK(arr2[0] == doctest::Approx(0));
  CHECK(arr2[3] == doctest::Approx(0));

  CHECK_NOTHROW(arr.Resize(10000));
  arr[9999] = 3.789;
  CHECK(arr[9999] == doctest::Approx(3.789));
  
  arr.Resize(2);
  arr[0] = 3.5;
  arr[1] = 3.5;
  CHECK(arr[0] == doctest::Approx(arr[1]));
  arr[1] += 2;
  CHECK(arr[0] != doctest::Approx(arr[1]));

  arr[0] = 4.567;
  arr[1] = 5.678;
  CHECK(arr[0] != arr[1]);

  DynArr arr3(arr);
  CHECK(arr3[0] == doctest::Approx(arr[0]));
  CHECK(arr3[1] == doctest::Approx(arr[1]));

  DynArr arr4;
  arr4 = arr;
  CHECK(arr4[0] == doctest::Approx(arr[0]));
  CHECK(arr4[1] == doctest::Approx(arr[1]));

  arr4[0] += 2;
  arr3[0] -= 2;
  arr4[1] += 1;
  arr3[1] -= 1;
  CHECK(arr[0] != doctest::Approx(arr4[0]));
  CHECK(arr[0] != doctest::Approx(arr3[0]));
  CHECK(arr4[0] != doctest::Approx(arr3[0]));
  CHECK(arr[1] != doctest::Approx(arr4[1]));
  CHECK(arr[1] != doctest::Approx(arr3[1]));
  CHECK(arr4[1] != doctest::Approx(arr3[1]));
}

TEST_CASE("time test") {
  DynArr arr1(10000);
  for (int i = 0; i < 10000; i++) {
    arr1[i] = 1;
  }
  auto start = std::chrono::steady_clock::now();
  DynArr arr2(arr1);
  auto end = std::chrono::steady_clock::now();
  CHECK_EQ(arr2[0], 1);
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  start = std::chrono::steady_clock::now();
  DynArr arr3(std::move(arr1));
  end = std::chrono::steady_clock::now();
  CHECK_EQ(arr3[0], 1);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  DynArr arr4(10000);
  for (int i = 0; i < 10000; i++) {
    arr4[0] = 1;
  }
  DynArr arr5;
  start = std::chrono::steady_clock::now();
  arr5 = arr4;
  end = std::chrono::steady_clock::now();
  CHECK_EQ(arr5[0], 1);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
  start = std::chrono::steady_clock::now();
  DynArr arr6 = std::move(arr4);
  end = std::chrono::steady_clock::now();
  CHECK_EQ(arr6[0], 1);
  duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
}