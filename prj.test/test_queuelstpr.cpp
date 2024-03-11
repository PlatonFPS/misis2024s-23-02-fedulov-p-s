#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<queuelstpr/queuelstpr.hpp>
#include<complex/complex.hpp>

float a(1.0f);
float b(2.0f);
float c(3.0f);

TEST_CASE("Initialization") {
  QueueLstPr queue;
  CHECK_THROWS(queue.Top());
  CHECK(queue.IsEmpty());
  CHECK_NOTHROW(queue.Pop());
  queue.Push(a);
  CHECK_NOTHROW(queue.Top());
  queue.Push(b);

  QueueLstPr queue2(queue);
  CHECK_EQ(queue2.Top(), queue.Top());
  CHECK_EQ(queue2.Top(), a);
  CHECK_NOTHROW(queue2.Pop());
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue2.Top(), queue.Top());
  CHECK_EQ(queue2.Top(), b);
  CHECK_NOTHROW(queue2.Pop());
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue2.IsEmpty(), queue.IsEmpty());
  CHECK_EQ(queue2.IsEmpty(), true);

  QueueLstPr queue3;
  CHECK_THROWS(queue3.Top());
  CHECK(queue3.IsEmpty());
  CHECK_NOTHROW(queue3.Pop());
  queue3.Push(a);
  CHECK_NOTHROW(queue3.Top());
  queue3.Push(b);

  QueueLstPr queue4 = queue3;
  CHECK_EQ(queue4.Top(), queue3.Top());
  CHECK_EQ(queue4.Top(), a);
  CHECK_NOTHROW(queue4.Pop());
  CHECK_NOTHROW(queue3.Pop());
  CHECK_EQ(queue4.Top(), queue3.Top());
  CHECK_EQ(queue4.Top(), b);
  CHECK_NOTHROW(queue4.Pop());
  CHECK_NOTHROW(queue3.Pop());
  CHECK_EQ(queue4.IsEmpty(), queue3.IsEmpty());
  CHECK_EQ(queue4.IsEmpty(), true);
}

TEST_CASE("Push, Pop, Top, Clear") {
  QueueLstPr queue;
  CHECK_THROWS(queue.Top());
  CHECK(queue.IsEmpty());
  CHECK_NOTHROW(queue.Pop());

  queue.Push(a);
  CHECK_NOTHROW(queue.Top());
  CHECK_EQ(queue.Top(), a);

  queue.Push(b);
  CHECK_EQ(queue.Top(), a);
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue.Top(), b);
  CHECK_NOTHROW(queue.Pop());
  CHECK_EQ(queue.IsEmpty(), true);

  queue.Push(a);
  CHECK_NOTHROW(queue.Top());
  queue.Clear();
  CHECK_EQ(queue.IsEmpty(), true);
}

TEST_CASE("sort test") {
  QueueLstPr queue;
  queue.Push(b);
  queue.Push(a);
  queue.Push(c);
  CHECK_EQ(queue.Top(), a);
  queue.Pop();
  CHECK_EQ(queue.Top(), b);
  queue.Pop();
  CHECK_EQ(queue.Top(), c);
  queue.Pop();
  CHECK_EQ(queue.IsEmpty(), true);
}