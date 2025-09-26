#ifndef AAL_SRC_MACROS_CPP_VERSION_TEST_HPP
#define AAL_SRC_MACROS_CPP_VERSION_TEST_HPP

/* https://github.com/atyxeut/algolib/blob/main/src/macros/cpp_version_test.hpp */

// see https://en.cppreference.com/w/cpp/preprocessor/replace#Predefined_macros for details

#if __cplusplus >= 201402L
#define AAL_CPP14 1
#endif // test if the current C++ version is C++14

#if __cplusplus >= 201703L
#define AAL_CPP17 1
#endif // test if the current C++ version is C++17

#if __cplusplus >= 202002L
#define AAL_CPP20 1
#endif // test if the current C++ version is C++20

#if __cplusplus >= 202302L
#define AAL_CPP23 1
#endif // test if the current C++ version is C++23

#endif // AAL_SRC_MACROS_CPP_VERSION_TEST_HPP
