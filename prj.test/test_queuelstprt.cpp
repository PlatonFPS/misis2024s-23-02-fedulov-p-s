#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include<queuelstprt/queuelstprt.hpp>
#include<complex/complex.hpp>

#include <vector>
#include <algorithm>
#include <string>

TEST_CASE("ctor") {
  QueueLstPrT<double> queue;
}