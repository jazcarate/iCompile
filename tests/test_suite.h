#ifndef ICOMPILE_TEST_SUITE_H
#define ICOMPILE_TEST_SUITE_H

#include <stdio.h>
#include <stdbool.h>
#include "webProvider_test/webProvider_test.h"

int run_test_suite();

#define FAIL() printf("\nFallo en %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_corridos++; if(r) return r; } while(0)

#endif //ICOMPILE_TEST_SUITE_H
