#ifndef AAL_SRC_MACROS_FEATURE_TEST_HPP
#define AAL_SRC_MACROS_FEATURE_TEST_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros/feature_test.hpp */

// see https://en.cppreference.com/w/cpp/feature_test.html for more details

#include "cpp_version_test.hpp"

#if AAL_CPP20
#include <version>

#if __cpp_lib_format >= 201907L
#define AAL_CPP20_FORMAT 1
#endif // test if C++20 <format> is available

#if __cpp_lib_print >= 202207L
#define AAL_CPP23_PRINT 1
#endif // test if C++23 <print> is available
#endif // C++20

#endif // AAL_SRC_MACROS_FEATURE_TEST_HPP
