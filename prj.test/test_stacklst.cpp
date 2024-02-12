#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<stacklst/stacklst.hpp>
#include<complex/complex.hpp>

static const Complex a(1, 2);
static const Complex b(1, 3);
static const Complex c(2, 3);

TEST_CASE("Initialization") {
  StackLst stack;
  CHECK_THROWS(stack.Top());
  CHECK(stack.IsEmpty());
  CHECK_NOTHROW(stack.Pop());
  stack.Push(a);
  CHECK_NOTHROW(stack.Top());
}

TEST_CASE("Copy") {
  StackLst stack;
  stack.Push(a);
  stack.Push(b);

  StackLst stack2(stack);
  CHECK_EQ(stack2.Top(), stack.Top());
  CHECK_EQ(stack2.Top(), b);
  stack2.Pop();
  CHECK_FALSE(stack2.Top() == stack.Top());
  CHECK_EQ(stack2.Top(), a);
  stack.Pop();
  CHECK_EQ(stack2.Top(), stack.Top());
  
  stack.Push(b);
  stack2 = stack;
  CHECK_EQ(stack2.Top(), stack.Top());
  CHECK_EQ(stack2.Top(), b);
  stack2.Pop();
  CHECK_FALSE(stack2.Top() == stack.Top());
  CHECK_EQ(stack2.Top(), a);
  stack.Pop();
  CHECK_EQ(stack2.Top(), stack.Top());
}