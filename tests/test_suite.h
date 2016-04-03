#ifndef ICOMPILE_TEST_SUITE_H
#define ICOMPILE_TEST_SUITE_H

#include <stdio.h>
#include <stdbool.h>
#include "webProvider_test/webProvider_test.h"
#include "webProvider_test/htmlHeaderParser_test.h"

int run_test_suite();

#define FAIL(testS) printf("\nFallo {%s} en %s() line %d\n", testS, __func__, __LINE__)
#define PASS(testS) printf("\n %3d %s: Ok.", tests_corridos, testS)
#define _assert(test) { if (!(test)) { FAIL(#test); return 1; } }
#define _verify(test) { int r=test(); tests_corridos++; if(r) return r; PASS(#test); }

#endif //ICOMPILE_TEST_SUITE_H
